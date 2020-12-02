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
void *thread(void *cfd);
void *thread_send(void *cfd);
void *thread_recv(void *cfd);


void *thread(void *cfd){
	void* ret1;
	void* ret2;
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
	struct sockaddr_in serv; 
	int sfd=socket(AF_INET,SOCK_STREAM,0);//创建一个通讯端点
		if(sfd==-1){
			perror("socket");
			return -1;
		}
	//初始化结构体serv
		serv.sin_family=AF_INET;
		serv.sin_port=htons(12345);
		inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
	int ct=connect(sfd,(struct sockaddr *)&serv,sizeof(serv));
		if(ct==-1){
			perror("connect");
			return -1;
		}	
	while(1){
		//消息处理
		pthread_t tid;
		void* ret;
		pthread_create(&tid,NULL,thread,&sfd);	
		pthread_join(tid,&ret);
	}
	return 0;
}

