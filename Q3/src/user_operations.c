#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/user_operations.h"

 #define MAX_USER_DATA_LENGTH 100

void read_backup_file(char ***stored_data, int *size, const char *backup_file_name) {
	FILE* file = fopen(backup_file_name, "r");
	if (file==NULL)
	{
		fprintf (stderr , "Error opening file: %s\n", backup_file_name);
		exit(EXIT_FAILURE);
	}
	
	int lines=0;
	char buffer[MAX_USER_DATA_LENGTH];
	
	while (fgets(buffer, MAX_USER_DATA_LENGTH , file) != NULL) 
	{
        lines++;
    }
    
    rewind(file);
	
	*stored_data = (char **)malloc(lines * sizeof(char *));
    if (*stored_data == NULL)
	{
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
	
	for (int i = 0; i < lines; i++) 
	{
        (*stored_data)[i] = (char *)malloc( (MAX_USER_DATA_LENGTH+1) * sizeof(char));
        if ((*stored_data)[i] == NULL) 
		{
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        
        if (fgets((*stored_data)[i], MAX_USER_DATA_LENGTH , file) == NULL) 
		{
            fprintf(stderr, "Error reading from file\n");
            exit(EXIT_FAILURE);
        }
    }
	
	*size = lines;
	
	fclose(file);
}
void show_users(char **stored_data, int size) {
	for (int i=0 ; i<size ; i++)
	{
		int j=0;
		while (	stored_data[i][j]!=' ')
		{
			stored_data[i][j]=tolower(stored_data[i][j]);
			j++;
		}
		int s = strcspn (stored_data[i],"_");
		stored_data[i][0]  =toupper(stored_data[i][0]);
		stored_data[i][s+1]=toupper(stored_data[i][s+1]);
		
		printf ("%s",stored_data[i]);
	}
}

void new_user(char ***stored_data, int *size, const char *user_name, const char *email, const char *password) {
	int flag=1;
	for (int i=0 ; i<*size ; i++)
	{
		char* buffer = (char*)malloc(30*sizeof(char));
		int s = strcspn((*stored_data)[i]," ");
		strncpy(buffer,(*stored_data)[i],s);
		buffer[s]='\0';
		if (strncmp(buffer,user_name,s) == 0)
		{
			printf ("User already exists!\n",buffer);
			flag=0;
			break;
		}
		free(buffer);
	}
	
	if(flag)
	{
	*size += 1;
	
	*stored_data = (char**)realloc(*stored_data,*size * sizeof(char *));
    if (*stored_data == NULL)
	{
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }	
    
	(*stored_data)[(*size)-1] = (char*)malloc( (MAX_USER_DATA_LENGTH+1) * sizeof(char));
	strcpy((*stored_data)[(*size)-1],user_name);
	strcat((*stored_data)[(*size)-1],"   ");
	strcat((*stored_data)[(*size)-1],email);
	strcat((*stored_data)[(*size)-1],"   ");
	strcat((*stored_data)[(*size)-1],password);
	
	printf("New user added!\n",user_name);
	}
}

void delete_user(char ***stored_data, int *size, const char *user_name) {
	int flag=1,i;
	for (i=0 ; i<*size ; i++)
	{
		char* buffer = (char*)malloc(30*sizeof(char));
		int s = strcspn((*stored_data)[i]," ");
		strncpy(buffer,(*stored_data)[i],s);
		buffer[s]='\0';
		if (strncmp(buffer,user_name,s) == 0)
		{
			printf("User deleted!\n",buffer);
			flag=0;
			break;
		}
		free(buffer);
	}
	if(flag)
	{
		printf("User not found!\n",user_name);
	}
	
	for (int j=i ; j<*size ; j++)
	{
		strcpy((*stored_data)[j],(*stored_data)[j+1]);
	}
	
	free((*stored_data)[*size-1]);
	
	*size-=1;
}

void email_cnt(char **stored_data, int size) {
	int gmail=0,aut=0,yahoo=0,other=0,hotmail=0;
	for(int i=0 ; i<size ; i++)
	{
		int start = strcspn(stored_data[i],"@");
		int end   = strcspn(stored_data[i],".");
		
		char* buffer=(char*)malloc((end-start+1)*sizeof(char));
		
		strncpy(buffer,stored_data[i]+start,end-start+1);
		buffer[end-start+1]='\0';
		
		if (strcmp(buffer,"@gmail.")==0)
		{
			gmail++;
		}
		else if (strcmp(buffer,"@aut.")==0)
		{
			aut++;
		}
		else if (strcmp(buffer,"@yahoo.")==0)
		{
			yahoo++;
		}
		else if (strcmp(buffer,"@hotmail.")==0)
		{
			hotmail++;
		}
		else
		{
			other++;
		}
		
		free(buffer);
	}
	printf ("Yahoo: %d\nGmail: %d\nAUT: %d\nHotmail: %d\nOthers: %d\n",yahoo,gmail,aut,hotmail,other);
}


void end_program(char ***stored_data, int size) {
	for (int i=0 ; i<size ; i++)
	{
		free((*stored_data)[i]);
	}
	free(*stored_data);
}