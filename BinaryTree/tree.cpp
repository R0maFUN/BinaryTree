#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include "Mystring.h"
#include "tree.h"
#include <string.h>
#include <stdio.h>



TREE* AddElement(TREE* root, string_r val)
{
	if (root && root->value && isNum(root->value))
			return root;
	if (!root)
	{
		TREE* pnew = (TREE*)malloc(sizeof(TREE));
		if (pnew == NULL)
			puts("ERROR");
		pnew->left = NULL;
		pnew->right = NULL;
		pnew->isComplete = false;
		pnew->value = (string_r)malloc(30);
		strcpy(pnew->value, val);
		root = pnew;
	}
	else
	{
		if ((!root->right && !isNum(val)) || (root->right && !isNum(val) && !root->right->isComplete) )
			root->right = AddElement(root->right, val);
		else if (!root->left && !isNum(val))
			root->left = AddElement(root->left, val);
		else if ( (root->right && !root->right->isComplete) || !root->right)
			root->right = AddElement(root->right, val);
		else
			root->left = AddElement(root->left, val);
	}
	if (root->right && root->left && isNum(root->right->value) && isNum(root->left->value))
		root->isComplete = true;
	if (root->right && root->left && root->right->isComplete && root->left->isComplete)
		root->isComplete = true;
	if (isNum(root->value))
		root->isComplete = true;
	return root;

}


TREE* CreateTree(string_r expression)
{
	string_r* parsed = Parsestring_r(expression);

	int firstNumID;

	for (int i = 0; parsed[i] != NULL; ++i)
		if (parsed[i][0] >= '0' && parsed[i][0] <= '9')
		{
			firstNumID = i;
			break;
		}
	int firstNumID2 = firstNumID;
	for (int i = 0; i < firstNumID2; ++i)
		if (isNum(parsed[i]))
		{
			parsed[i] = parsed[firstNumID];
			firstNumID++;
		}

	int size = 0;
	while (parsed[size] != NULL)
		size++;

	while (parsed[firstNumID2] != NULL)
		DelElem(parsed, firstNumID2, &size);

	string_r* Sorted = SortStation(parsed);

	int i = 0;
	TREE* root = NULL;

	size = 0;
	while (Sorted[i])
		++i;
	size = i;
	for (i = size - 1; i >= 0; --i)
		root = AddElement(root, Sorted[i]);

	return root;
}

void PrintTree(TREE* root, int level)
{
	if (root)
		PrintTree(root->right, level + 1);
	for (int i = 0; i < level; ++i)
		printf("\t");
	if (root)
		printf("%s   %d", root->value, level);
	else
		printf("#\n");
	if (root)
		PrintTree(root->left, level + 1);
}

double Calculate(TREE* root)
{
	if (isNum(root->value))
		return StrToInt(root->value);
	if (root->value[0] == '+')
		return Calculate(root->left) + Calculate(root->right);
	else if (root->value[0] == '-')
		return Calculate(root->left) - Calculate(root->right);
	else if (root->value[0] == '*')
		return Calculate(root->left) * Calculate(root->right);
	else if (root->value[0] == '/' || root->value[0] == '//')
		return (double)Calculate(root->left) / Calculate(root->right);
}

