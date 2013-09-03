#pragma once
#include "Buffer.h"
class Protocol;
class Packet
{
public:
	Packet(Buffer& buf);
	
	~Packet(void);

	void SetBuffer(Buffer& buf);
	Buffer GetBuffer();
	Buffer GetData();

	void GetEtherPacket();
	void GetIpNet();
	void GetUdpNet();
	void GetTcpNet();

	void Parse();
private:
	Buffer* buffer; 
	Buffer data;

	Protocol* protoStack;
};

