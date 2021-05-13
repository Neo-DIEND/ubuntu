#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define BACKLOG 2
extern void process_conn_server(int s);
int main(int argc,char*argv[])
{
	int ss;
	int sc;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int err;
	pid_t pid;

	//建立流式套接字
	ss = socket(AF_INET,SOCK_STREAM,0);
	if(ss < 0)
	{
		printf("Socket error\n");
		return -1;
	}
	
	//设置服务器地址
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	
	printf("socket ss == [ %d ]\n",ss);

	err = bind(ss,(struct sockaddr*)&server_addr,sizeof(server_addr));
	printf("bind err == [ %d ]\n",err);
	if(err < 0)
	{
		printf("bind error\n");
		return -1;
	}


	while(1)
	{
		err = listen(ss,BACKLOG);
		if(err < 0)
		{
			printf("listen erroe\n");
			return -1;
		}

		printf("listen success*************\n");

		socklen_t addrlen = sizeof(struct sockaddr);

	      	sc = accept(ss,(struct sockaddr*)&client_addr,&addrlen);

		printf("accept success **********\n");
		if(sc < 0)
		{
			continue;
		}

		pid = fork();
		printf("pid == [ %d ]\n",pid);
		if(pid == 0)
		{
			close(ss);
			printf("***********client already connection***********\n");
			process_conn_server(sc);
			printf("***********client quit connection**********\n");
		}
		else
		{
			close(sc);
		}
	}


	return 0;
}
