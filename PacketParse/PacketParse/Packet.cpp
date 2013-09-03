#include "stdafx.h"
#include "Packet.h"
#include "Buffer.h"
#include "Protocol.h"
Packet::Packet(Buffer& buf)
{
	SetBuffer(buf);
}

void Packet::SetBuffer(Buffer& buf)
{
	/*byte* pstBuf;
	uint32 len;
	buffer = &buf;
	pstBuf = buffer->GetBuffer(&len);
	pstBuf = pstBuf + sizeof(packet_hdr);
	len -= sizeof(packet_hdr);
	data = new Buffer(pstBuf, len);*/
	data = buf.GetBufferByOffSet(sizeof(packet_hdr));
}
void Packet::Parse()
{
	protoStack = new Protocol(*this);
	Protocol* temp = protoStack;
	while(temp->Parse())
	{
		temp = temp->GetUpperProtocol();
	}
}
Buffer Packet::GetBuffer()
{
	return *buffer;
}
Buffer Packet::GetData()
{
	return data;
}

Packet::~Packet(void)
{
}
