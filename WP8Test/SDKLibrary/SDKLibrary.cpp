// SDKLibrary.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "SDKLibrary.h"


// ���ǵ���������һ��ʾ��
SDKLIBRARY_API int nSDKLibrary=0;

// ���ǵ���������һ��ʾ����
SDKLIBRARY_API int fnSDKLibrary(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� SDKLibrary.h
CSDKLibrary::CSDKLibrary()
{
	return;
}
