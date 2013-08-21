#include "commontype.h"
typedef struct _list
{
	int32 data;
	struct _list *next;
	struct _list *pre;
}ListType;

void ListType_New(ListType *list);
void ListType_Free(ListType *list);
void ListType_Add(int32 data,ListType *list);
void ListType_Remove(ListType *element, ListType *list);

