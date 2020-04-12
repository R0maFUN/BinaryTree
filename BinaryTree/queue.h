#pragma once

#include "MyString.h"
#include <malloc.h>
#include <string.h>

typedef struct queue_h
{
	string_r value;
	struct queue_h* next;
}QUEUE;

QUEUE* Push(QUEUE* head, string_r val);

QUEUE* Pop(QUEUE* head);