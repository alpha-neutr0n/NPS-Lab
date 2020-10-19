#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
	int serv_socket, newconn, status,n;
	char buffer[1024];
	struct sockaddr_in servAddr,cliAddr;
	int servlen;
	
	serv_socket = socket(AF_INET,SOCK_STREAM, 0);
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(6323);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	status = bind(serv_socket,(struct sockaddr *)&servAddr,sizeof(servAddr));
	if(status==-1){
	printf("Bind failed\n");
	return 0; 
	}
	
	listen(serv_socket,5);
	printf("Server is listening\n");
	
	servlen=sizeof(cliAddr);
	newconn=accept(serv_socket, (struct sockaddr *)&cliAddr, &servlen);
	
	n=read(newconn,buffer,1024);
	buffer[n+1]='\0';
	printf("Recieved from client %s\n",buffer);
	strcpy(buffer,"Hi client\n");
	write(newconn,buffer,strlen(buffer));
	close(newconn);
	close(serv_socket);
	
}
	
