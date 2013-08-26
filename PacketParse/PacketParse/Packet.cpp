#include "stdafx.h"
#include "Packet.h"


Packet::Packet(Buffer& buf)
{
	SetBuffer(buf);
}

void Packet::SetBuffer(Buffer& buf)
{
	byte* pstBuf;
	uint32 len;
	buffer = &buf;
	pstBuf = buffer->GetBuffer(&len);
	pstBuf = pstBuf + sizeof(packet_hdr);
	len -= sizeof(packet_hdr);
	data = new Buffer(pstBuf, len);
}

Buffer Packet::GetBuffer()
{
	return *buffer;
}
Buffer Packet::GetData()
{
	return *data;
}

Packet::~Packet(void)
{
	delete data;
}
