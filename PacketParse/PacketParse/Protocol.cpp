#include "stdafx.h"
#include "Protocol.h"
#include <stdio.h>
#include "Packet.h"

#include "EtherNet.h"
Protocol::Protocol(Protocol* obj)
	:euProto(UNKOWN),uiOffset(0),uiHeaderLen(0),pstPreProtcol(obj),pstPostProtcol(NULL)
{
	pstPacket = obj->pstPacket;
	pstPayload = obj->GetBuffer().GetBufferByOffSet(uiHeaderLen);
}

Protocol::Protocol(Packet& pack)
	:euProto(UNKOWN),uiOffset(0),uiHeaderLen(0),pstPreProtcol(NULL),pstPostProtcol(NULL)
{
	pstPacket = &pack;
	pstPayload = pack.GetData().GetBufferByOffSet(uiHeaderLen);
}

uint32 Protocol::GetOffSet()
{
	return uiOffset;
}
uint32 Protocol::GetHeaderLen()
{
	return uiHeaderLen;
}
Buffer Protocol::GetBuffer()
{
	return pstPacket->GetBuffer();
}
Buffer Protocol::GetPayload()
{
	return pstPayload;
}
//解析上层协议，构建协议栈
bool Protocol::Parse()
{
	pstPostProtcol = new EtherNet(this);
	pstPostProtcol->SetOffSet(uiOffset + uiHeaderLen);
	//pstPostProtcol->SetLowerProtocol(this);
}
Protocol* Protocol::GetUpperProtocol()
{
	return pstPreProtcol;
}
Protocol* Protocol::GetLowerProtocol()
{
	return pstPostProtcol;
}

void Protocol::SetLowerProtocol(Protocol* pre)
{
	pstPreProtcol = pre;
}

//void SetBuf(byte* buffer, uint32 len)
//{
//
//}
//void SetOffSet(uint32 uiOffset)
//{
//
//}


Protocol::~Protocol(void)
{
}
