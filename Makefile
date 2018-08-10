CC = c++

CFLAGS = -c -Wall

all: client server

client: client-src/client.o src/TCPClient.o src/TCPServer.o
	$(CC) -lpthread client-src/client.o src/TCPClient.o src/TCPServer.o -o client

server: server-src/server.o src/TCPClient.o src/TCPServer.o
	$(CC) -lpthread server-src/server.o src/TCPClient.o src/TCPServer.o -o server

client-src/client.o: client-src/client.cpp
	$(CC) $(CFLAGS) client-src/client.cpp -o client-src/client.o

server-src/server.o: server-src/server.cpp
	$(CC) $(CFLAGS) server-src/server.cpp -o server-src/server.o

src/TCPClient.o: src/TCPClient.cpp
	$(CC) $(CFLAGS) src/TCPClient.cpp -o src/TCPClient.o

src/TCPServer.o: src/TCPServer.cpp
	$(CC) $(CFLAGS) src/TCPServer.cpp -o src/TCPServer.o

clean:
	rm -rf server-src/*.o client-src/*.o src/*.o server client