#include "queue.h"

QUEUE* Push(QUEUE* head, string_r val)
{
	QUEUE* pnew = (QUEUE*)malloc(sizeof(QUEUE));
	QUEUE* p = head;
	while (p && p->next)
		p = p->next;
	pnew->value = (string_r)malloc(sizeof(val) + 1);
	pnew->next = NULL;
	strcpy(pnew->value, val);
	if (p)
		p->next = pnew;
	if (head)
		return head;
	return pnew;
}

QUEUE* Pop(QUEUE* head)
{
	QUEUE* p = NULL;
	if (head)
		p = head->next;
	return p;
}
