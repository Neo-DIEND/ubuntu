//服务器端处理a
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
void process_conn_server(int s)
{
	ssize_t size = 0;
	char buffer[1024];
	printf("*********************");
	while(1)
	{
		size = read(s,buffer,1024);
		if(size == 0)
		{
			return ;
		}

		//响应处理
		sprintf(buffer,"%ld byte altogether\n",size);

		//发送到客户端
		write(s,buffer,strlen(buffer)+1);
	}
	
}
void process_conn_client(int s)
{
	ssize_t size = 0;
	char buffer[1024];
	printf("buffer == [ %s ]\n",buffer);
	printf("process_conn_client\n");
	for(;;)
	{
		//从标准输入获取数据
		printf("please input data:\n");
		size = read(0,buffer,1024);
		printf("size == [ %ld ]\n",size);
	//	printf("buffer == [ %s ]\n",buffer);
		if(size > 0)
		{
//			printf("hello");
			write(s,buffer,size);
			size = read(s,buffer,1024);
			write(1,buffer,size);
		}
//		printf("input end\n");
	}
}
