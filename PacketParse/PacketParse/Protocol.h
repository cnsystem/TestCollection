#pragma once
#include "types.h"
#include "Buffer.h"
class Buffer;
class EtherNet;
class Packet;
class Protocol
{
public:
	Protocol(Protocol* obj);
	Protocol(Packet& pack);
	
	uint32 GetOffSet();
	uint32 GetHeaderLen();
	Buffer GetBuffer();
	Buffer GetPayload();

	virtual bool Parse();
	Protocol* GetUpperProtocol();
	Protocol* GetLowerProtocol();
	void SetLowerProtocol(Protocol* pre);

	Packet* pstPacket;
	

	~Protocol(void);
protected:

	//void SetBuf(Buffer buf);
	void SetOffSet(uint32 uiOffset);
	proto_type euProto;

	uint32	uiOffset;
	uint32	uiHeaderLen;
private:
	Buffer pstPayload;	
	Protocol* pstPreProtcol;
	Protocol* pstPostProtcol;
};

