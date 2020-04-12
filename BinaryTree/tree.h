#pragma once
#include "Mystring.h"

typedef struct tree_t {
	string_r value = NULL;
	bool isComplete = false;
	struct tree_t* left = NULL;
	struct tree_t* right = NULL;
}TREE;

TREE* AddElement(TREE* root, string_r val);
int FindLastOpId(string_r* operators, int size);
void CreateBracketsTree(TREE* root, string_r* operands, string_r* operators, int* operandsSize, int* operatorsSize);
TREE* CreateTree(string_r expression);
void PrintTree(TREE* root, int level);
double Calculate(TREE* root);