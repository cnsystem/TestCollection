
#include <stdio.h>
#include <stdlib.h>
#include "ListType.h"

void ListType_New(ListType *list)
{
	list = (ListType*)malloc(sizeof(ListType));
	list->data= 0;
	list->next = NULL;
}
void ListType_Free(ListType *list)
{
	ListType* tail;
	tail = list;
	while(tail->next)
	{
		tail = tail->next;
	}
	while(tail->pre)
	{
		tail = tail->pre;
		free(tail->next);
	}
	free(tail);
	list = 0;
}
void ListType_Add(int32 data,ListType *list)
{
	ListType *element;
	ListType *tail;
	element = (ListType *)malloc(sizeof(ListType));
	tail = list;
	while(tail->next)
	{
		tail = tail->next;
	}
	tail->next = element;
	element->pre = tail;
	element->next = 0;
	element->data = data;
}
void ListType_Remove(ListType *element, ListType *list)
{
	ListType *element;
	ListType *p;
	p = list;
	while(p->next==element)
	{
		p = p->next;
	}
	p->next = element->next;
	p = p->next;
	p->pre = element->pre;
	element->next = 0;
	element->pre = 0;
}
