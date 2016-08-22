#include "stdafx.h"
/*
Load all the regex from a file,
and return the total number of regex strings.
*/
int regex_loader(_token token[], char *file)
{
	FILE *fp = NULL;
	int file_line = 0;
	char single_line[512];
	int i = 0, j = 0;
	if ((fp = fopen(file, "r")) == NULL)
	{
		printf("Open file failed.\n");
		return 0;
	}
	while ((fgets(single_line, sizeof(single_line), fp) != NULL))
	{
		for (i = 0; single_line[i] != ':'; i++)
		{
			token[file_line].token_name[i] = single_line[i];
		}
		token[file_line].token_name[i] = 0;
		i++;
		for (j = 0; single_line[i] && single_line[i] != '\n'; i++, j++)
		{
			token[file_line].regex[j] = single_line[i];
		}
		token[file_line].regex[j] = 0;
		file_line++;
	}
	fclose(fp);
	return file_line;
}