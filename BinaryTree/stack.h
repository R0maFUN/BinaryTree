#pragma once

#include "MyString.h"
#include <malloc.h>

typedef struct stack_h {
	string_r value;
	struct stack_h* next;
}STACK;

STACK* Push(STACK* head, string_r value);
string_r GetTop(STACK* head);
STACK* Pop(STACK* head);
int isEmpty(STACK* head);



