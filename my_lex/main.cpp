// Regular_Expression_Implementation.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

extern int lines;
int main()
{
	lexeme lex;
	lex_ini("D:/Personal/Desktop/regex.txt", "D:/Personal/Desktop/code.txt");

	while (get_next_token(&lex))
	{
		printf("Match:<%s,%s>\n", lex.lexeme_name, lex.token_name);
	}
	printf("Match:<%s,%s>\n", lex.lexeme_name, lex.token_name);
	printf("lines:%d\n", lines);
	getchar();
}

