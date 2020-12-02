#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
void *thread(void* cfd);
void *thread_send(void* cfd);
void *thread_recv(void* cfd);

void *thread(void* cfd){
	void *ret1;
 	void *ret2;
	//创建两个线程用于接收和发送消息
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread_send,cfd);
	pthread_create(&tid2,NULL,thread_recv,cfd);	
	pthread_join(tid1,&ret1);
	pthread_join(tid2,&ret2);
}
void *thread_send(void* cfd){
	char tmp[516];
	int c=*((int *)cfd);
	while(1){
		fgets(tmp,516,stdin);
		send(c,tmp,516,0);
		printf("        send ok\n");
	}
}
void *thread_recv(void* cfd){
	char tmp[516];
	int d=*((int *)cfd);
	while(1){
		int idata=0;
		idata=recv(d,tmp,516,0);
		if(idata>0){
			printf("        recv ok\n");
			printf("%s",tmp);
		}
	}
}


int main(){
	struct sockaddr_in serv,cli; 
	int sfd=socket(AF_INET,SOCK_STREAM,0);//创建一个通讯端点
		if(sfd==-1){
			perror("socket");
			return -1;
		}
	//初始化结构体serv
	serv.sin_family=AF_INET;
	serv.sin_port=htons(12345);
	serv.sin_addr.s_addr=htonl(INADDR_ANY);
	int bd=bind(sfd,(struct sockaddr *)&serv,sizeof(serv));//与通讯端点绑定
		if(bd==-1){
			perror("bind");
			return -1;
		}
	int ln=listen(sfd,2);//监听
		if(ln==-1){
			perror("listen");
			return -1;
		}
	socklen_t cli_len;
	cli_len=sizeof(cli);
		while(1){
			int cfd=accept(sfd,(struct sockaddr *)&cli,&cli_len);//连接
			if(cfd==-1){
				perror("accept");
				return -1;
			}
		//创建线程处理数据
		pthread_t tid;
		void* ret;
		pthread_create(&tid,NULL,thread,&cfd);
		pthread_join(tid,&ret);
		}
	return 0;
}
