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
	int cli_socket, status,n;
	char buffer[1024];
	struct sockaddr_in servAddr;
	
	cli_socket = socket(AF_INET,SOCK_STREAM, 0);
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(6323);
	servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	status = connect(cli_socket,(struct sockaddr *)&servAddr,sizeof(servAddr));
	if(status){
	printf("Connection failed\n");
	return 0; 
	}
	else
	printf("Connection Succesful\n");
	
	strcpy(buffer,"Hello server\n");
	write(cli_socket,buffer,strlen(buffer));
	
	n=read(cli_socket,buffer,1024);
	buffer[n+1]='\0';
	printf("%s",buffer);
	close(cli_socket);
}
