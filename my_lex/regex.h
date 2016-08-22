#pragma once

typedef struct _state
{
	int c;
	_state ****out1 ;
	_state ****out2 ;
	int id;
}state;

/*
A struct that stored the states that nfa is in,
and the nfa will be in.
*/
typedef struct _list
{
	state **s;
	int states_num;
}list;




int match(char);
void start_list(state *, list *);
char* re2post(char *);
state* post2nfa(char*, int);
void add_state(list *, state *);


