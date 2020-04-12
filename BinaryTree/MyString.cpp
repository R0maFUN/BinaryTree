#include "Mystring.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "queue.h"
#include "stack.h"
#include <math.h>

typedef char* string_r;

bool isNum(string_r str)
{
	if ( str && ( (str[0] >= '0' && str[0] <= '9') || (str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')))
		return true;
	return false;
}

void DoubleMemory(string_r* str , int * size)
{
	string_r tmp = (string_r)malloc(*size);
	strcpy(tmp, *str);
	free(*str);
	*str = (string_r)malloc(*size * 2);
	if (*str == NULL)
		puts("ERROR");
	strcpy(*str, tmp);
	free(tmp);
	*size *= 2;
}

int PushBack(string_r* str , int * bufSize, char val)
{
	int i = 0;
	while ((*str)[i] != '\0')
	{
		if (*bufSize <= i + 2)
			DoubleMemory(str , bufSize);
		++i;
	}
	(*str)[i] = val;

	(*str)[i + 1] = '\0';
	return 1;
}

string_r* ParseOperators(string_r* parsed, int* size)
{
	int i = 0;
	int resultSize = 40;
	char** result = (char**)malloc(sizeof(char*) * resultSize);
	while (parsed[i] != NULL && !isNum(parsed[i]))
	{
		result[i] = (char*)malloc(sizeof(char) * 20);
		result[i] = parsed[i];
		++i;
	}
	result[i] = NULL;
	*size = i;
	return result;
}

string_r* ParseOperands(string_r* parsed, int* size)
{
	int i = 0;
	int resultSize = 40;
	char** result = (char**)malloc(sizeof(char*) * resultSize);
	int j = 0;
	while (parsed[i] != NULL)
	{
		if (isNum(parsed[i]))
		{
			result[j] = (char*)malloc(sizeof(char) * 20);
			result[j] = parsed[i];
			++j;
		}
		++i;
	}
	result[j] = NULL;
	*size = j;
	return result;
}

void CopyArray(string_r* dest, string_r* source, int begin, int end)
{
	int i = 0;
	while (begin <= end)
	{
		dest[i] = source[begin];
		i++;
		begin++;
	}
}

void DelElem(string_r* array, int id , int * size)
{
	(*size)--;
	while (array[id] != NULL)
	{
		array[id] = array[id + 1];
		if (array[id] == NULL) return;
		id++;
	}
}

string_r* Parsestring_r(string_r str)
{
	int resultSize = 40;
	char** result = (char**)malloc(sizeof(char*)*resultSize);
	for (int i = 0; i < resultSize; ++i)
		result[i] = (char*)malloc(sizeof(char)*20);
	int resIndex = 0;
	int i = 0;
	int bufSize = 5;
	string_r buf = (string_r)malloc(sizeof(char) * bufSize);
	
	buf[0] = '\0';
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			PushBack(&buf, &bufSize , str[i]);
		else if (str[i] != ' ')
		{
			if (buf[0]!='\0')
			{
				strcpy(result[resIndex], buf);
				buf[0] = '\0';
				resIndex++;
			}
			result[resIndex][0] = str[i];
			result[resIndex][1] = '\0';
			resIndex++;
		}
		else {
			if (buf[0] != '\0')
			{
				strcpy(result[resIndex], buf);
				buf[0] = '\0';
				resIndex++;
			}
		}
		i++;
	}

	if (buf[0] != '\0')
	{
		strcpy(result[resIndex], buf);
		buf[0] = '\0';
		resIndex++;
	}
	puts("here");
	result[resIndex] = NULL;

	free(buf);
	return result;

}

int GetPriority(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/' || op == '//')
		return 2;
	if (op == '(' || op == ')')
		return 0;
}

bool isOperator(string_r str)
{
	if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '//')
		return true;
	return false;
}


string_r* SortStation(string_r* parsed)
{
	int i = 0;
	QUEUE * outputQ = NULL;
	STACK * stack = NULL;
	while (parsed[i] != NULL)
	{
		if (isNum(parsed[i]))
			outputQ = Push(outputQ , parsed[i]);
		if (isOperator(parsed[i]))
		{
			if (stack)
			{
				string_r top = GetTop(stack);
				while (GetPriority(top[0]) >= GetPriority(parsed[i][0]))
				{
					outputQ = Push(outputQ, top);
					stack = Pop(stack);
					if(stack)
						top = GetTop(stack);
					else
						break;
				}
			}
			
			stack = Push(stack, parsed[i]);
		}
		if (parsed[i][0] == '(')
			stack = Push(stack, parsed[i]);
		if (parsed[i][0] == ')')
		{
			string_r top = GetTop(stack);
			while (top[0] != '(')
			{
				outputQ = Push(outputQ, top);
				stack = Pop(stack);
				top = GetTop(stack);
			}
			stack = Pop(stack);
		}
		++i;
	}
	string_r top = GetTop(stack);
	while (stack)
	{
		outputQ = Push(outputQ, top);
		stack = Pop(stack);
		top = GetTop(stack);
	}

	int resultSize = 40;
	char** result = (char**)malloc(sizeof(char*) * resultSize);

	i = 0;
	while (outputQ)
	{
		result[i] = (char*)malloc(sizeof(char) * 20);
		result[i] = outputQ->value;
		outputQ = Pop(outputQ);
		++i;
	}
	result[i] = NULL;

	return result;

}

int StrToInt(string_r str)
{
	int i = 0;
	while (str[i] && str[i] != '\0')
		++i;
	int result = 0;
	int exp = 0;
	i--;
	while (i >= 0)
	{
		result += (str[i] - '0') * pow(10, exp);
		exp++;
		i--;
	}

	return result;
}