struct bash_result {
    int status;
    string stdOut<>;
};

program RemoteBash {
	version VERSIO {
		bash_result rpcbash(string command)=1;
	}=1;
}=0x23451111;
