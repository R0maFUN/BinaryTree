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
	{
		if (parsed[i][0] >= '0' && parsed[i][0] <= '9')
		{
			firstNumID = i;
			break;
		}
	}
	int firstNumID2 = firstNumID;
	for (int i = 0; i < firstNumID2; ++i)
	{
		if (isNum(parsed[i]))
		{
			parsed[i] = parsed[firstNumID];
			firstNumID++;
		}
	}

	int size = 0;
	while (parsed[size] != NULL)
		size++;

	while (parsed[firstNumID2] != NULL)
		DelElem(parsed, firstNumID2, &size);

	string_r* Sorted = SortStation(parsed);
	int operandsSize, operatorsSize;
	//string_r* operands = ParseOperands(opers , &operandsSize);
	//string_r* operators = ParseOperators(opers , &operatorsSize);
	int i = 0;
	puts("OK1");
	TREE* root = NULL;
	//root = AddElement(root, );
	//puts("ok2");
	//int start = FindLastOpId(operators, operatorsSize);
	//if (start == -1)
	//{
	//	printf("[ERROR]: did not found the last operator on the inizialization step");
	//	return NULL;
	//}
	
	//CreateBracketsTree(&root, operands, operators, &operandsSize, &operatorsSize);
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
	{
		printf("%s   %d", root->value, level);
		/*printf("%d\r", level);
		for (int i = 0; i < 5 - strlen(root->value); ++i)
			printf(" ");
		printf("\r%s", root->value);*/
	}
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
	{
		int left = Calculate(root->left);
		int right = Calculate(root->right);
		return Calculate(root->left) + Calculate(root->right);
	}
	else if (root->value[0] == '-')
	{
		int left = Calculate(root->left);
		int right = Calculate(root->right);
		return Calculate(root->left) - Calculate(root->right);
	}
	else if (root->value[0] == '*')
	{
		int left = Calculate(root->left);
		int right = Calculate(root->right);
		return Calculate(root->left) * Calculate(root->right);
	}
	else if (root->value[0] == '/' || root->value[0] == '//')
	{
		int left = Calculate(root->left);
		int right = Calculate(root->right);
		return (double)Calculate(root->left) / Calculate(root->right);
	}
}



//TREE* AddElement(TREE* root , string_r val)
//{
//	if (root && root->value && isNum(root->value))
//		return root;
//	if (!root)
//	{
//		TREE * pnew = (TREE*)malloc(sizeof(TREE));
//		if (pnew == NULL)
//			puts("ERROR");
//		pnew->left = NULL;
//		pnew->right = NULL;
//		pnew->value = (string_r)malloc(30);
//		strcpy(pnew->value, val);
//		root = pnew;
//	}
//	else if (isNum(val) && !root->right)
//		root->right = AddElement(root->right, val);
//	else if(isNum(val) && !root->left)
//		root->left = AddElement(root->left, val);
//	else if (isNum(val))
//	{
//		TREE* test = root->right;
//		root->right = AddElement(root->right, val);
//		if (test == root->right)
//			root->left = AddElement(root->left, val);
//	}
//	else if(!root->left && !root->right || !root->left)
//		root->left = AddElement(root->left, val);
//	else if(!root->right)
//		root->right = AddElement(root->right, val);
//	else
//	{
//		TREE* test = root->right;
//		root->right = AddElement(root->right, val);
//		if (test == root->right)
//			root->left = AddElement(root->left, val);
//	}
//
//	return root;
//}

//int FindLastOpId(string_r* operators , int size)
//{
//	int i = size - 1;
//	int result = -1;
//	while (i >= 0)
//	{
//		printf("%s\n", operators[i]);
//		if (operators[i][0] == ')')
//		{
//			int bracketsCount = 1;
//			i--;
//			while (bracketsCount > 0)
//			{
//				if (operators[i][0] == ')')
//					bracketsCount++;
//				else if (operators[i][0] == '(')
//					bracketsCount--;
//				i--;
//			}
//		}
//		if ( i>=0 && ((operators[i][0] == '+') || (operators[i][0] == '-')) )
//			return i;
//		if (result == -1) // if * or /
//			result = i;
//		i--;
//	}
//	return result;
//}

//void CreateBracketsTree(TREE ** root, string_r* operands, string_r* operators, int* operandsSize, int* operatorsSize)
//{
//	int i = 0;
//	while (i < *operandsSize + *operatorsSize && *operatorsSize > 0 && operands && operators)
//	{
//		int operatorID = FindLastOpId(operators, *operatorsSize);
//		if (operatorID == -1) // если нашли только скобки, строим для них дерево
//		{
//			int bracketsCount = 1;
//			int j = 1;
//
//			while (bracketsCount > 0)
//			{
//				if (operators[j][0] == ')')
//					bracketsCount--;
//				else if (operators[j][0] == '(')
//					bracketsCount++;
//				j++;
//			}
//
//			int resultSize = 40;
//			char** result = (char**)malloc(sizeof(char*) * resultSize);
//			for (int i = 0; i < resultSize; ++i)
//				result[i] = (char*)malloc(sizeof(char) * 20);
//			CopyArray(result, operators, 1, j - 2);
//			DelElem(operators, 0, operatorsSize);
//			DelElem(operators, j - 1, operatorsSize);
//			CreateBracketsTree(root, operands, result, operandsSize, operatorsSize);
//			if (!operators || !operands ||*operatorsSize == 0 || *operandsSize == 0)
//				break;
//		}
//		else // если нашли оператор, добавляем его в дерево
//		{
//			*root = AddElement(*root, operators[operatorID]);
//			
//			if (operatorID == *operatorsSize - 1) // если оператор последний, добавляем вправо последнее число
//			{
//				*root = AddElement(*root, operands[*operandsSize - 1]);
//				DelElem(operands, *operandsSize - 1, operandsSize);
//			}
//			else if (operators[operatorID + 1][0] != '(') // если справа * / добавляем в дерево
//			{
//				*root = AddElement(*root, operators[operatorID + 1]);
//				DelElem(operators, operatorID + 1, operatorsSize);
//			}
//			else // если справа скобки, строим дерево для этих скобок
//			{
//				int start = operatorID + 1;
//				int end = *operatorsSize - 3;
//				DelElem(operators, operatorID + 1, operatorsSize);
//				DelElem(operators, *operatorsSize - 1, operatorsSize);
//				int resultSize = 40;
//				char** result = (char**)malloc(sizeof(char*) * resultSize);
//				for (int i = 0; i < resultSize; ++i)
//					result[i] = (char*)malloc(sizeof(char) * 20);
//				CopyArray(result, operators, start, end);
//				int resSize = end - start + 1;
//				CreateBracketsTree(root, operands, result, operandsSize, &resSize);
//				if (!operators || !operands || *operatorsSize == 0 || *operandsSize == 0)
//					break;
//			}
//
//			DelElem(operators, operatorID, operatorsSize);
//
//		}
//		
//		if (operators[0][0] != '(')
//		{
//			*root = AddElement(*root, operators[0]);
//			DelElem(operators, 0, operatorsSize);
//		}
//		else
//		{
//			int bracketsCount = 1;
//			int j = 1;
//
//			while (bracketsCount > 0)
//			{
//				if (operators[j][0] == ')')
//					bracketsCount--;
//				else if (operators[j][0] == '(')
//					bracketsCount++;
//				j++;
//			}
//
//			int resultSize = 40;
//			char** result = (char**)malloc(sizeof(char*) * resultSize);
//			for (int i = 0; i < resultSize; ++i)
//				result[i] = (char*)malloc(sizeof(char) * 20);
//			CopyArray(result, operators, 1, j - 1);
//			DelElem(operators, 0, operatorsSize);
//			DelElem(operators, j - 1, operatorsSize);
//			CreateBracketsTree(root, operands, result, operandsSize, &j);
//			if (!operators || !operands || *operatorsSize == 0 || *operandsSize == 0)
//				break;
//		}
//		//root = AddElement(root, opers[i]);
//		++i;
//	}
//
//	while (*operandsSize > 0 && operands)
//	{
//		*root = AddElement(*root, operands[*operandsSize - 1]);
//		DelElem(operands, *operandsSize - 1, operandsSize);
//	}
//
//}