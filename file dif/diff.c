#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200

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
	int count = 0;
	while (strcmp(fp1line, "") != 0 && strcmp(fp2line, "") != 0 && count < 5) {
		getline(fp1line, MAXLINE, fp1);
		getline(fp2line, MAXLINE, fp2);
		if (strcmp(fp1line, fp2line) != 0)
			printf("%d: %s%d: %s",linenum,fp1line,linenum,fp2line);
		linenum++;
		count++;
	}
}

int version() {
	printf("diff (GNU duffutils) 1.0\nCopyright (c) 2017 LGHANSEN\n\n");
	printf("This program comes with NO WARRANTY, to the extent permitted by law.\nYou may redistribute copies of this program\n");
	printf("under the terms of the GNU General Public License.\n");
	printf(	"For more information about these matters, see the file named COPYING.\n\n");
	printf("Written by Lonnie Hansen");
	//Returns 0 because no differences were found because no comparison was made
	return 0;
}

int help() {
	printf("use google stupid");
	//Returns 0 because no differences were found because no comparison was made
	return 0;
}