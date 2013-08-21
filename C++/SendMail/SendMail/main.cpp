#include "SendMail.h"
#include "stdafx.h"

void main()
{
	CSendMail sender;
	sMailInfo info;
	info.m_pcBody = "";
	info.m_pcIPAddr ="";
	info.m_pcIPName ="smtp.163.com";
	info.m_pcReceiver = "yangxiaohai@huawei.com";
	info.m_pcSender = "cnsystem@163.com";
	info.m_pcSenderName = "cnsystem";
	info.m_pcTitle = "¹«²âÓÊ¼þ";
	info.m_pcUserName = "cnsystem";
	info.m_pcUserPassWord = "udbihc";
	if(sender.SendMail(info))
		printf("send success");
	else
	{
		printf("send failed");
	}
}
