#include "commontype.h"
#include "client.h"
#include "network.h"
#include "logger.h"
#include <stdio.h>
void client_main()
{
	Net_Socket_Stru send;
	Net_Socket_Stru recive;
	int8 buffer[1024];
	int32 length;
	int8 *localAddr = "192.168.1.155";			
	int32 localPort = 8080;
	int8 *remoteAddr = "192.168.1.155";
	int32 remotePort = 8852;
	length = 0;	
	Net_CreateSendSock(localAddr,localPort,TCPSocket,&send);
	Net_CreateRecieveSock(remoteAddr,remotePort,TCPSocket,&recive);

	
	printf("ÇëÊäÈë×Ö·û´®\n");
	length = scanf("%s",buffer);
	Net_SendTcpPacket(&send,buffer,length);
	Net_RecieveTcpPacket(&send,buffer,1024);
	printf("%s\n",buffer);
}