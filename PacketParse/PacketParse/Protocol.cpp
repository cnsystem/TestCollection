#include "stdafx.h"
#include "Protocol.h"
#include <stdio.h>

Protocol::Protocol(Protocol& obj)
	:euProto(UNKOWN),uiOffset(0),uiHeaderLen(0),pstPreProtcol(NULL),pstPostProtcol(NULL)
{
	
}

Protocol::Protocol(Packet& pack)
	:euProto(UNKOWN),uiOffset(0),uiHeaderLen(0),pstPreProtcol(NULL),pstPostProtcol(NULL)
{
	pstPacket = &pack;
	pstPayload = pack.GetData();
}

uint32 Protocol::GetOffSet()
{

}
uint32 Protocol::GetHeaderLen()
{

}
byte* Protocol::GetBuffer(uint32* uiLen)
{

}
byte* Protocol::GetPayload(uint32* uiLen)
{

}

bool Protocol::Parse()
{

}
Protocol Protocol::GetUpperProtocol()
{

}
Protocol Protocol::GetLowerProtocol()
{

}


void SetBuf(byte* buffer, uint32 len)
{

}
void SetOffSet(uint32 uiOffset)
{

}


Protocol::~Protocol(void)
{
}
