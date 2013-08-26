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
	byte* GetBuffer(uint32* uiLen);
	byte* GetPayload(uint32* uiLen);

	virtual bool Parse();
	virtual Protocol GetUpperProtocol();
	virtual Protocol GetLowerProtocol();

	~Protocol(void);
protected:
	bool bCreateBuf;

	void SetBuf(byte* buffer, uint32 len);
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

