#include "commontype.h"
typedef struct _LogModule
{
	int isinited;
	enum { L_CLOSED, L_OPENING, L_OPEN, L_ERROR } state;
}LogModule;


static LogModule logmodule={0};
static FILE *filelog;

int32 Log_IsInit();
int32 LogWrite(const char *fmt, ...);
int32 LOG_Modoule_Init();
int32 Log_Module_Free();