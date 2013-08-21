#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <io.h>
#include <time.h>
#include "logger.h"
#include "commontype.h"

int main(int argc,char* argv[])
{
	time_t	now;
	struct	tm	*tminfo;
	time(&now);
	tminfo = localtime(&now);
	
	printf("%d-%d-%d %d:%d:%d",tminfo->tm_year+1900,tminfo->tm_mon+1,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min,tminfo->tm_sec);
	system("pause");
	return 0;
}