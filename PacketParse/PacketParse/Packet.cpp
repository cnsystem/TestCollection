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
	buffer = &buf;
	data = buf.GetBufferByOffSet(sizeof(packet_hdr));
}
void Packet::Parse()
{
	protoStack = new Protocol(*this);
	Protocol* temp = protoStack;
	while(temp->Parse() && temp->GetUpperProtocol())
	{
		temp->GetUpperProtocol()->SetLowerProtocol(temp);
		temp = temp->GetUpperProtocol();
	}
}
Buffer* Packet::GetBuffer()
{
	return buffer;
}
Buffer* Packet::GetData()
{
	return data;
}

Packet::~Packet(void)
{
	delete data;
}
