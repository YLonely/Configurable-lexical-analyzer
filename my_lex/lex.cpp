#include "stdafx.h"
#include "regex.h"

FILE *code_file_p = NULL;
state **start = NULL;

int buff_p = 0;
short current_state = 0, next_state = 0;
char *current_buff = NULL, *next_buff = NULL, *temp = NULL;
int current_num, next_num;
int regex_num = 0;

int lines = 1;
//int ending = 0;

extern list current_list, next_list;
extern int g_state_num;

_token token[512];

void blank_skip();

void list_ini(state **start, list *l, int state_num)
{
	l->states_num = 0;
	for (int i = 0; i < state_num; i++)
	{
		add_state(l, *(start + i));
	}
}


int load(char *buff)
{
	return fread(buff, sizeof(char), 1024, code_file_p);
}

/*
The initialize of the lex, build the nfa of all the tokens in mem.
*/

void lex_ini(char *regex_file, char *code_file)
{
	regex_num = regex_loader(token, regex_file);
	if ((code_file_p = fopen(code_file, "r")) == NULL)
	{
		printf("Open failed.\n");
		return;
	}

	char **post = (char**)malloc(regex_num * sizeof(char*));
	for (int i = 0; i < regex_num; i++)
	{
		*(post + i) = re2post(token[i].regex);
	}

	start = (state**)malloc(regex_num*sizeof(state*));
	for (int i = 0; i < regex_num; i++)
	{
		*(start + i) = post2nfa(*(post + i), i);
	}

	current_list.s = (state**)malloc(g_state_num * sizeof(state*));
	next_list.s = (state**)malloc(g_state_num * sizeof(state*));

	list_ini(start, &current_list, regex_num);

	current_buff = (char*)calloc(1024, sizeof(char));
	next_buff = (char*)calloc(1024, sizeof(char));

	current_num = load(current_buff);
	current_state = 1;

	if (current_num >= 1024)
	{
		next_num = load(next_buff);
		next_state = 1;
	} else
		fclose(code_file_p);

}

/*
Get the next token which fits the regular expression.

*/

int get_next_token(lexeme *lex)
{
	int lex_length = 0;
	char lex_s[256];
	int mark;
	blank_skip();
	for (; ; buff_p++, lex_length++)
	{
		/*if (current_buff[buff_p] == 9 || current_buff[buff_p] == 10)
		{
			lex_length--;
			continue;
		}*/
		lex_s[lex_length] = current_buff[buff_p];
		mark = match(current_buff[buff_p]);
		if (mark == -1)
		{
			if (current_buff[buff_p] == '\0')
			{
				lex_s[0] = 0;
				strcpy(lex->lexeme_name, lex_s);
				strcpy(lex->token_name, "STRING_END");
				//ending = 1;
				return 0;
			}

			printf("No match error.\n");
			return 0;
		} else if (mark != -2)
		{
			blank_skip();
			lex_s[lex_length] = 0;
			strcpy(lex->lexeme_name, lex_s);
			strcpy(lex->token_name, token[mark].token_name);

			list_ini(start, &current_list, regex_num);
			return 1;
		}

		if (buff_p == 1023)
		{
			if (next_state == 1)
			{
				temp = current_buff;
				current_buff = next_buff;
				next_buff = temp;
				next_state = 0;
				buff_p = 0;
				if (load(next_buff))
				{
					next_state = 1;
				}
			} else
			{
				printf("End of the file.\n");
				fclose(code_file_p);
				return -1;
			}
		}
	}
}

void blank_skip()
{
	for (; current_buff[buff_p] == ' ' || current_buff[buff_p] == '\n' || current_buff[buff_p] == '\t' || current_buff[buff_p] == '\r'; buff_p++)
		if (current_buff[buff_p] == '\n')
			lines++;
}