#include "stdafx.h"
#include "UdpNet.h"


UdpNet::UdpNet(Packet& pack):Protocol(pack),header(NULL)
{
	eProto = UDP;
}
UdpNet::UdpNet(Protocol* obj):Protocol(obj),header(NULL)
{
	eProto = UDP;
}

uint32 UdpNet::GetSrcPort()
{
	uint32 src_port = (uint32)(header->src_port);
	return src_port;
}
uint32 UdpNet::GetDstPort()
{
	uint32 dst_port = (uint32)(header->dst_port);
	return dst_port;
}
uint32 UdpNet::GetLength()
{
	uint32 length = (uint32)(header->udp_len);
	return length;
}
uint32 UdpNet::GetCRC()
{
	uint32 crc = (uint32)(header->udp_crc);
	return crc;
}

bool UdpNet::Parse()
{
	uint32 length;
	if(!CheckBuff())
		return false;
	header = (udp_header*)pstBuffer->GetBuffer(&length);
}
Protocol* UdpNet::GetUpperProtocol()
{
	if(pstPostProtcol == NULL)
	{

	}
	return pstPostProtcol;
}
Protocol* UdpNet::GetLowerProtocol()
{
	return pstPreProtcol;
}

UdpNet::~UdpNet(void)
{
}
