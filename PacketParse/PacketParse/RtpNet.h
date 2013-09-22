#pragma once
#include "protocol.h"
class RtpNet
	:public Protocol
{
public:
	RtpNet(Packet& pack);
	RtpNet(Protocol* obj);

	uint32 GetVersion();
	bool IsPadding();
	bool IsExtend();
	uint32 GetCsrcCount();
	bool IsMark();
	uint32 GetPayloadType();
	uint32 GetSerialNumber;
	uint32 GetTimespan();
	uint32 GetSsrc();

	virtual bool Parse();
	virtual Protocol* GetUpperProtocol();
	virtual Protocol* GetLowerProtocol();
	~RtpNet(void);
protected:
	rtp_header* header;
};

