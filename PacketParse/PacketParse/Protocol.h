#pragma once
#include "types.h"
#include "Buffer.h"

class EtherNet;
class Packet;
class Protocol
{
public:
	Protocol(Protocol* obj);
	Protocol(Packet& pack);
	
	uint32 GetOffSet();	
	void SetOffSet(uint32 offset);
	uint32 GetHeaderLen();
	Buffer* GetBuffer();
	Buffer* GetPayload();
	bool CheckBuff();
	virtual bool Parse();
	Protocol* GetUpperProtocol();
	Protocol* GetLowerProtocol();
	void SetLowerProtocol(Protocol* pre);
	Packet* pstPacket;
	~Protocol(void);
protected:
	proto_type eProto;
	uint32	uiOffset;
	uint32	uiHeaderLen;
	Buffer* pstPayload;	
	Buffer* pstBuffer;	
	Protocol* pstPreProtcol;
	Protocol* pstPostProtcol;
private:

};

