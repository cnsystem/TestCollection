#pragma once
#include "types.h"
#include "Buffer.h"
#include "Packet.h"
class Protocol
{
public:
	Protocol(Protocol& obj);
	Protocol(Packet& pack);
	
	uint32 GetOffSet();
	uint32 GetHeaderLen();
	Buffer GetBuffer();
	Buffer GetPayload();

	virtual bool Parse();
	virtual Protocol GetUpperProtocol();
	virtual Protocol GetLowerProtocol();

	~Protocol(void);
protected:

	void SetBuf(Buffer buf);
	void SetOffSet(uint32 uiOffset);
	
private:
	proto_type euProto;

	Packet* pstPacket;
	Buffer pstPayload;

	uint32	uiOffset;
	uint32	uiHeaderLen;
	
	Protocol* pstPreProtcol;
	Protocol* pstPostProtcol;
};

