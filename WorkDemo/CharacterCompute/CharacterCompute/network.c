#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <ws2def.h>
#include "network.h"
#include "logger.h"
#include "ListType.h"
#define PortLength 20

ListType *SendCallBack;
ListType *RecieveCallBack;

LPTSTR PrintError(int ErrorCode)
{
    static TCHAR Message[1024];

    // If this program was multithreaded, we'd want to use
    // FORMAT_MESSAGE_ALLOCATE_BUFFER instead of a static buffer here.
    // (And of course, free the buffer when we were done with it)

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
                  FORMAT_MESSAGE_MAX_WIDTH_MASK,
                  NULL, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  Message, 1024, NULL);
    return Message;
}
int Net_ModuleInit()
{
	int RetVal;
	WSADATA wsaData;
	if ((RetVal = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        LogWrite("WSAStartup failed with error %d: %s\n",
                RetVal, PrintError(RetVal));
        WSACleanup();
        return Return_ERROR;
    }
	ListType_New(SendCallBack);
	ListType_New(RecieveCallBack);
	return Return_OK;
}
int32 Net_CreateSendSock(const int8* addr,const int32 port,int32 socktype,Net_Socket_Stru *netSock)
{
	SOCKET sock;
	struct addrinfo hints;
	struct addrinfo *addr_result;
	struct addrinfo *rp;
	int8 cPortBuff[PortLength];
	int32 retcode;
	netSock->sock = -1;
	memset(&cPortBuff, 0, PortLength);
	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
 	hints.ai_socktype = socktype; /* Datagram socket */
 	hints.ai_flags = 0;             /* For wildcard IP address */
 	hints.ai_protocol = 0;          /* Any protocol */
 	hints.ai_canonname = NULL;
 	hints.ai_addr = NULL;
 	hints.ai_next = NULL;
	sprintf(cPortBuff,"%u",port);
	if(0!=getaddrinfo(addr,cPortBuff,&hints,&addr_result))
	{
		LogWrite("getaddrinfo error");
		return -1;
	}
	for(rp=addr_result;rp!=NULL;rp=rp->ai_next)
	{
        //ai - family , res - > ai - socktype , res- > ai - protocol
		sock = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sock==-1)
		{
			continue;
		}
		if(socktype==SOCK_DGRAM)
		{
			retcode = sendto(sock,addr,strlen(addr),0,rp->ai_addr,rp->ai_addrlen);
			if(retcode != SOCKET_ERROR)
				break;
		}
		if(socktype==SOCK_STREAM)
		{
			retcode = connect(sock,rp->ai_addr,rp->ai_addrlen);
			if(retcode != SOCKET_ERROR)
				break;
		}
		LogWrite("******************************************");
		LogWrite("family:%d\n",rp->ai_family);
        LogWrite("socktype:%d\n",rp->ai_socktype);
        LogWrite("protocol:%d\n",rp->ai_protocol);
		LogWrite("create socket error with errorcode:%d\n",WSAGetLastError());
		closesocket(sock);
		sock = -1;
	}
	if(sock != -1)
	{
		LogWrite("******************************************");
		LogWrite("family:%d\n",rp->ai_family);
		LogWrite("socktype:%d\n",rp->ai_socktype);
		LogWrite("protocol:%d\n",rp->ai_protocol);
		LogWrite("create socket success\n");
		netSock->family = rp->ai_family;
		netSock->addr = (int8 *) malloc(sizeof(int8)*strlen(addr));
		memcpy(netSock->addr,addr,strlen(addr));
		netSock->port = port;
		netSock->local = (Address*) malloc(sizeof(Address));
		memset(netSock->local,0,sizeof(Address));
		netSock->remote = (Address*) malloc(sizeof(Address));
		memcpy(netSock->remote,rp->ai_addr,sizeof(Address));
	}
	netSock->sock = sock;
	freeaddrinfo(addr_result);
    return 0;
}
int32 Net_CreateRecieveSock(const int8* addr,const int32 port,int32 socktype,Net_Socket_Stru *netSock)
{
	SOCKET sock;
	struct addrinfo hints;
	struct addrinfo *addr_result;
	struct addrinfo *rp;
	int8 cPortBuff[PortLength];
	int32 retcode;	
	netSock->sock = -1;
	memset(&cPortBuff, 0, PortLength);
	memset(&hints, 0, sizeof(struct addrinfo));
 	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
 	hints.ai_socktype = socktype; /* Datagram socket */
 	hints.ai_flags = 0;             /* For wildcard IP address */
 	hints.ai_protocol = 0;          /* Any protocol */
 	hints.ai_canonname = NULL;
 	hints.ai_addr = NULL;
 	hints.ai_next = NULL;
	sprintf(cPortBuff,"%u",port);
	if(0!=getaddrinfo(addr,cPortBuff,&hints,&addr_result))
	{
		LogWrite("getaddrinfo error");
		retcode = -1;
		return retcode;
	}
	for(rp=addr_result;rp!=NULL;rp=rp->ai_next)
	{
        //ai - family , res - > ai - socktype , res- > ai - protocol
        printf("******************************************");
		printf("family:%d\n",rp->ai_family);
        printf("socktype:%d\n",rp->ai_socktype);
        printf("protocol:%d\n",rp->ai_protocol);

		sock = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(sock==-1)
		{
			continue;
		}
		
		retcode = bind(sock,rp->ai_addr,rp->ai_addrlen);
		if(retcode != SOCKET_ERROR)
			break;
		LogWrite("******************************************");
		LogWrite("family:%d\n",rp->ai_family);
        LogWrite("socktype:%d\n",rp->ai_socktype);
        LogWrite("protocol:%d\n",rp->ai_protocol);
		LogWrite("create socket error with errorcode:%d\n",WSAGetLastError());
		closesocket(sock);
		sock = -1;
		retcode = -1;
	}
	if(sock != -1)
	{
		LogWrite("******************************************");
		LogWrite("family:%d\n",rp->ai_family);
		LogWrite("socktype:%d\n",rp->ai_socktype);
		LogWrite("protocol:%d\n",rp->ai_protocol);
		LogWrite("create socket success\n");
		netSock->addr = (int8 *) malloc(sizeof(int8)*strlen(addr));
		memcpy(netSock->addr,addr,strlen(addr));
		netSock->port = port;
		netSock->local = (Address*) malloc(sizeof(Address));
		memcpy(netSock->local,rp->ai_addr,sizeof(Address));
		retcode = -1;
	}
	netSock->sock = sock;
	freeaddrinfo(addr_result);
    return retcode;
}
void Net_ReleaseSock(Net_Socket_Stru *netSock)
{
	
	closesocket(netSock->sock);
	netSock->sock = -1;
	free(netSock->local);
	netSock->local =(Address*)NULL;
	free(netSock->remote);
	netSock->remote =(Address*)NULL;
	free(netSock->addr);
	netSock->addr = (int8*)NULL;
}
int32 Net_SendUdpPacket(Net_Socket_Stru *netSock,const int8 *buffer,int32 length)
{
	int result;
	result = sendto(netSock->sock,buffer,length,0,(sockaddr*)netSock->remote,sizeof(Address));
	return result;
}
int32 Net_SendTcpPacket(Net_Socket_Stru *netSock,const int8 *buffer,int32 length)
{
	int result;
	result = send(netSock->sock,buffer,length,0);
	return result;
}

int32 Net_Add_SendBack(Net_CallBack *onSend)
{
	if(SendCallBack->next == 0)
	{
		SendCallBack->data = (int32) onSend;
	}
	else 
	{
		ListType_Add((int32)onSend,SendCallBack);
	}
}
int32 Net_Add_RecieveBack(Net_CallBack *onRecieve)
{
	if(RecieveCallBack->next == 0)
	{
		RecieveCallBack->data = (int32) onRecieve;
	}
	else 
	{
		ListType_Add((int32)onRecieve,RecieveCallBack);
	}
}

int32 Net_RecieveUdpPacket(Net_Socket_Stru *netSock,int8 *buffer,int32 length)
{
	int result;
	int addlen;
	ListType *temp;
	void (*func)(const void *data,void *out);
	void *parameter;
	memset(buffer,0,length);
	result = RecieveCallBack(netSock->sock,buffer,length,0,(sockaddr*)netSock->remote,&addlen);
	temp = SendCallBack;
	while(temp)
	{
		func = ((Net_CallBack*)(temp->data))->func;
		parameter = ((Net_CallBack*)(temp->data))->parameter;
		(*func)((void*)buffer,parameter);
	}
	return result;
}
int32 Net_RecieveTcpPacket(Net_Socket_Stru *netSock,int8 *buffer,int32 length)
{
	int result;
	ListType *temp;
	void (*func)(const void *data,void *out);
	void *parameter;
	memset(buffer,0,length);
	result = recv(netSock->sock,buffer,length,0);
	temp = RecieveCallBack;
	while(temp)
	{
		func = ((Net_CallBack*)(temp->data))->func;
		parameter = ((Net_CallBack*)(temp->data))->parameter;
		(*func)((void*)buffer,parameter);
	}
	return result;
}


