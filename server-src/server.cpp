#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include "../src/TCPServer.h"

TCPServer tcp;
string seperator = "::";

array<string, 10> splitString(string str);
string messageParse(string str);

void * loop(void * m)
{
    pthread_detach(pthread_self());
	while(1)
	{
		string str = tcp.getMessage();
		if( str != "" ) {
			cout << str << endl;
			tcp.Send(messageParse(str));
			tcp.clean();
			str = "";
		}
	}
	tcp.detach();
}

string messageParse(string str) {
	array<string,10> arr = splitString(str);
	if (arr.at(0) == "connect") {
		cout << arr.at(1) << " has connected to the server.\n";
		return "\e[1m[SERVER]\e[0m " + arr.at(1) + " has joined to the server.";
	}
}

array<string, 10> splitString(string str) {
	array<string,10> output;
	int i = 0;
	size_t pos = 0;
	string token;
	while ((pos = str.find(seperator)) != string::npos) {
    	token = str.substr(0, pos);
    	output.at(i) = token;
    	str.erase(0, pos + seperator.length());
		i++;
	}
	output.at(i) = str;
	return output;
}

int main()
{
	pthread_t msg;
	tcp.setup(11999);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}
