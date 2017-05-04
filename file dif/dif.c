#include "dif.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 500

int getline(char *line, int max, FILE *file) {
	if (fgets(line, max, file) == NULL)
		return 0;
	else
		return strlen(line);
}

void difroutine() {
	FILE *fp1, *fp2;
	fp1 = fopen("file1.txt", "r+");	//Temporary Files
	fp2 = fopen("file2.txt", "r+");	//Will add a way to choose files later
	if (fp1 == NULL)
		fprintf(stderr, "Error opening file\n");
	if (fp2 == NULL)
		fprintf(stderr, "Error opening file\n");

	int linenum = 0;
	char *fp1line = (char*)malloc(MAXLINE);
	char *fp2line = (char*)malloc(MAXLINE);
	while (strcmp(fp1line, EOF) != 0 && strcmp(fp2line, EOF) != 0) {
		getline(fp1line, MAXLINE, fp1);
		getline(fp2line, MAXLINE, fp2);
		if (strcmp(fp1line, fp2line) != 0)
			printf("%d: %s\n%d: %s",linenum,fp1line,linenum++,fp2line);
	}
}