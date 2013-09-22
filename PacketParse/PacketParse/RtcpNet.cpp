#include "stdafx.h"
#include "RtcpNet.h"

RtcpNet::RtcpNet(Packet& pack):Protocol(pack),rtcp_packet(NULL)
{
	eProto = RTCP;
}

RtcpNet::RtcpNet(Protocol* obj):Protocol(obj),rtcp_packet(NULL)
{
	eProto = RTCP;
}



RtcpNet::~RtcpNet(void)
{
}
