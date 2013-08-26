#include "stdafx.h"
#include "Buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Buffer::Buffer(uint32 length)
{
	pstBuffer = (byte*)malloc(length);
	uiLen = length;
	bCreate = true;
}
Buffer::Buffer(byte* buffer, uint32 len)
{
	pstBuffer = buffer;
	uiLen = len;
	bCreate = false;
}

void Buffer::ResetLen(uint32 len)
{
	if(len <= uiLen)
		return;
	byte* buf = (byte*)malloc(len);
	memset(buf, 0, len);
	memcpy(buf, pstBuffer, uiLen);
	if(bCreate)
		free(pstBuffer);
	pstBuffer = buf;
	uiLen = len;
}
byte* Buffer::GetBuffer(uint32* length)
{
	*length = uiLen;
	return pstBuffer;
}


Buffer::~Buffer(void)
{
	if(bCreate)
		free(pstBuffer);
}
