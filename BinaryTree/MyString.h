#pragma once
#define _CRT_SECURE_NO_WARNINGS
typedef char* string_r;

bool isNum(string_r str);

void DoubleMemory(string_r* str , int * size);
int PushBack(string_r* str,int * bufSize ,  char val);
string_r* ParseOperators(string_r* parsed, int* size);
string_r* ParseOperands(string_r* parsed, int* size);
void CopyArray(string_r* dest, string_r* source, int begin, int end);
string_r* SortStation(string_r* parsed);
void DelElem(string_r* array, int id , int * size);
string_r* Parsestring_r(string_r str);
int StrToInt(string_r str);
