#pragma once
typedef struct 
{
	char token_name[128];
	char regex[256];
}_token;

int regex_loader(_token token[], char *file);
