#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <io.h>
#include <time.h>
#include "logger.h"


int32 Log_IsInit()
{
	if(1==logmodule.isinited)
		return 1;
	return 0;
	
}
int32 LOG_Modoule_Init()
{	
	time_t	now;
	struct	tm	*tminfo;
	filelog=fopen("Character.log","a+");
	if(filelog==NULL)
	{
		logmodule.isinited = 0;
		return Return_OK;
	}
	logmodule.isinited = 1;
	time(&now);
	tminfo = localtime(&now);
	LogWrite("LogModule Init Success!");
	LogWrite("%d-%d-%d %d:%d:%d\n",tminfo->tm_year+1900,tminfo->tm_mon+1,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec);
	return Return_OK;
}
int32 LogWrite(const char *fmt, ...)
{
	int8	buffer[1024];
	va_list	argptr;
	va_start(argptr,fmt);
	vsprintf(buffer,fmt,argptr);
	fputs(buffer,filelog);
	va_end(argptr);
	return Return_OK;
}
int32 Log_Module_Free()
{
	LogWrite("Log Module Free!");
	free(filelog);
	filelog = NULL;
	if(1==logmodule.isinited)
	{
		logmodule.isinited = 0;
	}
	return Return_OK;
}