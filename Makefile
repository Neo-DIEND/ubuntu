all:client server
	
client:tcp_process.o tcp_client.o
	gcc -g -o client tcp_process.o tcp_client.o
server:tcp_process.o tcp_server.o
	gcc -g -o server tcp_process.o tcp_server.o
tcp_process.o:
	gcc -g -c tcp_process.c -o tcp_process.o
tcp_client.o:
	gcc -g -c tcp_client.c -o tcp_client.o
tcp_server.o:
	gcc -g -c tcp_server.c -o tcp_server.o
clean:
	rm -f client server *.o

