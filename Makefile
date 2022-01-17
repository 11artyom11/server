all: server client

server:
	g++ server.cpp -o server -w -g

client:
	g++ client.cpp -o client -w -g 

delbins:
	rm -rf server client
	