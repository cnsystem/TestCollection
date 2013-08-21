#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <ws2def.h>
#include "commontype.h"
#if (_WIN32_WINNT == 0x0500)
#include <tpipv6.h>
#endif	
#pragma comment(lib, "Ws2_32.lib")

#define TCPSocket 1
#define UDPSocket 2
#define RawSocket 3

typedef struct sockaddr_storage Address;
typedef struct _socket
{
	SOCKET sock;
	int32 family;
	int8 *addr;
	int32 port;
	Address *remote;
	Address *local;
	int32 state;
}Net_Socket_Stru;

typedef struct _callback
{
	void (*func)(const void *data,void *out);
	void *parameter;
}Net_CallBack;

int Net_ModuleInit();
int32 Net_CreateSendSock(const int8* addr,const int32 port,int32 socktype,Net_Socket_Stru *netSock);
int32 Net_CreateRecieveSock(const int8* addr,const int32 port,int32 socktype,Net_Socket_Stru *netSock);
void Net_ReleaseSock(Net_Socket_Stru *netSock);
int32 Net_SendUdpPacket(Net_Socket_Stru *netSock,const int8 *buffer,int32 length);
int32 Net_SendTcpPacket(Net_Socket_Stru *netSock,const int8 *buffer,int32 length);
int32 Net_RecieveUdpPacket(Net_Socket_Stru *netSock,int8 *buffer,int32 length);
int32 Net_RecieveTcpPacket(Net_Socket_Stru *netSock,int8 *buffer,int32 length);
int32 Net_Add_RecieveBack(Net_CallBack *onRecieve);
int32 Net_Add_SendBack(Net_CallBack *onSend);