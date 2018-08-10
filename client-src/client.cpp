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

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_exit);
	username = argv[1];
	tcp.setup("127.0.0.1",11999);
	tcp.Send("connect" + seperator + username);
	while(1)
	{
		string rec = tcp.receive();
		if( rec != "" )
		{
			cout << rec << endl;
		}
	}
	return 0;
}
