#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Mystring.h"
#include "tree.h"
#include <malloc.h>

int main()
{
	puts("enter the expression");
	string_r exp = (string_r)malloc(sizeof(char)*30);
	fgets(exp, 30, stdin);

	
	string_r* parsed = Parsestring_r(exp);
	puts("result of parsing:");
	for (int i = 0; parsed[i] != NULL; ++i)
		printf("%s ", parsed[i]);


	string_r * newP = SortStation(parsed);
	puts("result of sort satation:");
	for (int i = 0; newP[i] != NULL; ++i)
		printf("%s ", newP[i]);
	
	TREE* root = CreateTree(exp);
	PrintTree(root, 0);

	printf("Result = %f", Calculate(root));

	int j = 0;
	while (parsed[j])
	{
		free(parsed[j]);
		++j;
	}
	free(root);
	free(newP);
	free(exp);
	return 0;
}