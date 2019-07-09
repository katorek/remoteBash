#include "remoteBash.h"

bash_result execute_command(char *command) {
    bash_result result;

    FILE *fp;

    char buf[100];
    char *str = NULL;
    char *temp = NULL;
    unsigned int size = 1;  // start with size of 1 to make room for null terminator
    unsigned int strlength;

    fp = popen(command, "r"); //open pipe stream with our command and capture it stdout

    if (!fp) {
        printf("Command execution failed!\n");
        result.status = 1;
        result.stdOut = "Command execution failed!";
        return result;
    }

    printf("Reading ... \n");
    while(fgets(buf, sizeof(buf), fp) != NULL) {
        strlength = strlen(buf);
        temp = realloc(str, size + strlength);
        if(temp == NULL) {
            pclose(fp);
            printf("Allocation error!\n");
            result.status = 1;
            result.stdOut = "Allocation error!";
            return result;
        } else {
            str = temp;
        }
        strcpy(str+size -1, buf);
        size += strlength;
    }

    result.status = WEXITSTATUS(pclose(fp));
    result.stdOut = str ? str : "";
    return result;
}

bash_result *rpcbash_1_svc(char **argp, struct svc_req *rqstp) {
    static bash_result result;

    printf("%s\n", *argp); //print command from client

    result = execute_command(*argp); //call command exec
    printf("%s\n", result.stdOut);
    return &result; //return result or error
}
