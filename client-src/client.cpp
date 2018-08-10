#include <iostream>
#include <signal.h>
#include "../src/TCPClient.h"

TCPClient tcp;
string username;
string seperator = "::";

void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}

void *listener(void * m) {
	pthread_detach(pthread_self());
	string input = "";
	while(1) {
		if (input != "") {
			tcp.Send("message" + seperator + username + seperator + input);
		}
		getline(cin, input);
	}
}

int main(int argc, char *argv[])
{
	pthread_t listn;
	signal(SIGINT, sig_exit);
	username = argv[1];
	tcp.setup("127.0.0.1",11999);
	tcp.Send("connect" + seperator + username);
	pthread_create(&listn, NULL, listener, (void *)0);
	while(1) {
		string rec = tcp.receive();
		
		if( rec != "" ) {
			cout << rec << endl;
			rec = "";
		}
	}
	return 0;
}
