#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#define PORT 8888

extern void process_conn_client();

//void process_conn_client(int s)
//{
//	ssize_t size = 0;
//	char buffer[1024];
//
//
//	for(;;)
//	{
//		//从标准输入获取数据
//		printf("please input data:\n");
//		size = read(0,buffer,1024);
//		printf("size == [ %ld ]\n",size);
//		if(size > 0)
//		{
//			printf("size > 0\n");
//			write(s,buffer,size);
//		///	printf("write end\n");
//			size = read(s,buffer,1024);
//			write(1,buffer,size);
//		//	printf("read write end\n");
//		}
//		printf("input end\n");
//	}
//}
int main(int argc,char*argv[])
{

	int s;
	printf("client front\n");
	struct sockaddr_in server_addr;
	s = socket(AF_INET,SOCK_STREAM,0);
	printf("s == [ %d ]\n",s);
	if(s < 0)
	{
		printf("socket error\n");
		return -1;
	}
	//设置服务器地址
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],&server_addr.sin_addr);
	connect(s,(struct sockaddr*)&server_addr,sizeof(struct sockaddr));
	process_conn_client(s);
	printf("test*************");
	close(s);

	return 0;
}

