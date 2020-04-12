#include "stack.h"

STACK* Push(STACK* head, string_r value)
{
	STACK* p = (STACK*)malloc(sizeof(STACK));
	p->value = value;
	p->next = head;
	return p;
}

STACK* Pop(STACK* head)
{
	STACK* p = head->next;
	free(head);
	return p;
}

string_r GetTop(STACK* head)
{
	if(head)
	return head->value;
	return NULL;
}

int isEmpty(STACK* head)
{
	if (head)
		return 0;
	return 1;
}