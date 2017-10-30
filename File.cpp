#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <errno.h>
using namespace  std;

int isspaceline(char* test)
{
	int i = 1;
	while (*test != '\n')
	{
		if (*test != ' ')
		{
			i = 0;
			break;
		}
		test++;
	}
	return i;
}

int select(char* key,char* sel)
{
	char* find;
	find = strtok(sel, "\t ");
	if (strcmp(find, key) == 0)
		return 1;
	return 0;
}

void main() {
	FILE* fp;
	char cmd[50];
	char* str;
	char* buffer=NULL;
	while (gets_s(cmd) != NULL)
	{
		int point = 0;
		str = strtok(cmd, "\t ");
		if ((strcmp(str, "[insert]")) == 0)
		{
			char* p[6];
			time_t clock;
			fp = fopen("output.txt", "a");
			if (fp == NULL)
				return;
			while (1)
			{
				int i = 0;
				p[i] = strtok(NULL, "\t");
				if (p[i] == NULL)
					break;
				fprintf(fp, "%s\t", p[i]);
			}
			clock = time(0);
			fprintf(fp, "%s", ctime(&clock));
			fflush(fp);
			fclose(fp);
		}
		else if ((strcmp(str, "[select]")) == 0)
		{
			char file1[1024];
			char file2[1024];
			char* sel;
			char* p[3];
			int key = 0;
			fp = fopen("output.txt", "r+");
			sel = strtok(NULL, "\t ");
			fseek(fp, 0, SEEK_SET);
			fgets(file1, 1024, fp);
			strcpy(file2, file1);
			while (isspaceline(file1) == 0)
			{
				if (select(sel, file1) == 1)
				{
					puts(file2);
					key = 1;
					break;
				}
				fgets(file1, 1024, fp);
				strcpy(file2, file1);
			}
			if (!key)
				printf("no result");
			fclose(fp);
		}
		else if ((strcmp(str, "[delete]")) == 0)
		{
			FILE* fs;
			char file1[1024];
			char file2[1024];
			char* del;
			fp = fopen("output.txt", "r+");
			fs = fopen("mid.txt", "w+");
			fseek(fp, 0, SEEK_END);
			fprintf(fp, "\n ");
			del = strtok(NULL, "\t ");
			char filename[20];
			sprintf(filename, "output.txt");
			fseek(fp, 0, SEEK_SET);
			fgets(file1, 1024, fp);
			strcpy(file2, file1);
			while (isspaceline(file1) == 0)
			{
				if (select(del, file1) == 0)
					fputs(file2, fs);
				fgets(file1, 1024, fp);
				strcpy(file2, file1);
			}
			fclose(fp);
			remove(filename);
			fflush(fs);
			fclose(fs);
			rename("mid.txt", filename);
		}
		else if ((strcmp(str, "[leon]")) == 0)
			point = 1;
		else if ((strcmp(str, "[return]")) == 0)
			point = 2;
		if (point == 1 || point == 2)
		{
			FILE* fs;
			char file1[1024];
			char file2[1024];
			char* update;
			time_t clock;
			fp = fopen("output.txt", "r+");
			fs = fopen("mid.txt", "w+");
			fseek(fp, 0, SEEK_END);
			fprintf(fp, "\n ");
			update = strtok(NULL, "\t ");
			char filename[20];
			sprintf(filename, "output.txt");
			fseek(fp, 0, SEEK_SET);
			fgets(file1, 1024, fp);
			strcpy(file2, file1);
			while (isspaceline(file1) == 0)
			{
				if (select(update, file1) == 1)
				{
					clock = time(0);
					if (point == 1)
						fprintf(fs, "%s\tleon\t%s", update, ctime(&clock));
					else
						fprintf(fs, "%s\treturn\t%s", update, ctime(&clock));
				}
				else
					fputs(file2, fs);
				fgets(file1, 1024, fp);
				strcpy(file2, file1);
			}
			fclose(fp);
			remove(filename);
			fflush(fs);
			fclose(fs);
			rename("mid.txt", filename);
		}
	}
}

