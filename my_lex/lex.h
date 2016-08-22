#pragma once
typedef struct
{
	char lexeme_name[128];
	char token_name[128];
}lexeme;
void lex_ini(char *, char *);
int get_next_token(lexeme *);