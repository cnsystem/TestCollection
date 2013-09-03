#include "stdafx.h"
#include "EtherNet.h"


EtherNet::EtherNet(Packet& pack):Protocol(pack)
{
	euProto = ETHER_NET;
}

EtherNet::EtherNet(Protocol* obj):Protocol(obj)
{
	euProto = ETHER_NET;
	uiOffset = obj->GetOffSet() + obj->GetHeaderLen();
	uiHeaderLen = sizeof(eth_header);
}

EtherNet::~EtherNet(void)
{
}
