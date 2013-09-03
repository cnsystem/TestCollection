#pragma once
#include "protocol.h"
class EtherNet :
	public Protocol
{
public:
	EtherNet(Packet& pack);
	EtherNet(Protocol* obj);
	~EtherNet(void);
};

