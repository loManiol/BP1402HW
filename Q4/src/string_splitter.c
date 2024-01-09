#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

char** splitString(const char *input, char delimiter, int *substringCount) {
	int lengh = strlen(input);
	for (int i=0 ; i<lengh ; i++)
	{
		if (input[i]==delimiter)
			(*substringCount)++;
	}
	
	char** substrings = (char**)malloc(*substringCount * sizeof(char*));
	if (substrings == NULL)
	{
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

	const char* sub = input;
	int index = 0;
	
	for (const char* c = input ; ; c++)
	{
		if (*c == delimiter || *c == '\0')
		{
			substrings[index] = (char*)malloc((c - sub + 1) * sizeof(char));
			if (substrings[index] == NULL)
			{
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            
            strncpy(substrings[index], sub, c - sub);
            substrings[index][c - sub] = '\0';
			
			sub = c + 1;
            index++;

            if (*c == '\0') 
			{
                break;
            }
		}
	}
	return substrings;
}

void freeSubstrings(char **substrings, int count) {
    for (int i = 0; i < count; ++i) {
        free(substrings[i]);
    }
    free(substrings);
}


