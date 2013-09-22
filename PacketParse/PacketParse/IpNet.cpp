#include "stdafx.h"
#include "IpNet.h"
#include "StringHelper.h"
#include "UdpNet.h"

IpNet::IpNet(Packet& pack):Protocol(pack),header(NULL)
{
	eProto = IP_NET;
}
IpNet::IpNet(Protocol* obj):Protocol(obj),header(NULL)
{
	eProto = IP_NET;
	uiHeaderLen = sizeof(ip_header);
}
uint32 IpNet::IpNet::GetVersion()
{
	uint32 version= (uint32)(header->ver_ihl >> 4);
	return version;
}
uint32 IpNet::IpNet::GetTosValue()
{
	uint32 tos_value = (uint32)(header->tos);
	return tos_value;
}
uint32 IpNet::IpNet::GetTotalLength()
{
	uint32 total_length = (uint32)(header->tlen);
	return total_length;
}
uint32 IpNet::GetFlags()
{
	uint32 flags = (uint32)(header->flags_offset >> 8);
	return flags;
}
uint32 IpNet::GetSliceOffset()
{
	uint32 slice_offset = (uint32)(header->flags_offset & 0x00FF);
	return slice_offset;
}
uint32 IpNet::GetTtl()
{
	uint32 ttl = (uint32)(header->ttl);
	return ttl;
}
proto_type IpNet::GetProtoType()
{
	switch (header->proto)
	{
	case 17:
		return UDP;
	case 7:
		return TCP;
	default:
		return UNKOWN;
	}
}
uint32 IpNet::GetCRC()
{
	uint32 crc = (uint32)(header->ip_crc);
	return crc;
}

int8* IpNet::GetSrcIpAddr()
{
	return srcAddr;
}
int8* IpNet::GetDstIpAddr()
{
	return dstAddr;
}

bool IpNet::Parse()
{
	uint32 length;
	if(!CheckBuff())
		return false;
	header = (ip_header*)pstBuffer->GetBuffer(&length);
	uiHeaderLen = (header->ver_ihl & 0x0F) * 4;
	hex2str(srcAddr, (uint8*)header->src_addr, sizeof(header->src_addr));
	hex2str(dstAddr, (uint8*)header->dst_addr, sizeof(header->dst_addr));
	//对负载偏移从新计算
	pstPayload = pstBuffer->GetBufferByOffSet(uiHeaderLen);
	if(!pstPayload)
		return false;
}
Protocol* IpNet::GetUpperProtocol()
{
	if(pstPostProtcol == NULL)
	{
		pstPostProtcol = new UdpNet(this);
		pstPostProtcol->SetOffSet(uiOffset + uiHeaderLen);
	}
	return pstPostProtcol;
}
Protocol* IpNet::GetLowerProtocol()
{
	return pstPreProtcol;
}
void IpNet::hex2str(int8* str, uint8* buffer, uint32 len)
{
	int32 i;
	int32 offset = 0;
	for(i = 0; i<len; i++)
	{
		offset += StringHelper::int2str((uint32)buffer[i], str + offset);
		*(str + offset) = '.';
		offset++;
	}
	*(str + offset) = '.';
}

IpNet::~IpNet(void)
{
}
