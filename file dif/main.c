#include "diff.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 200

typedef struct line line;

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("Error: not enough arguments\n");
		return 2;
	}
	char* fname1, fname2;
	fname1 = strdup("");
	fname2 = strdup("");
	int numf = 0;

	int text = 0, ignorespacechange = 0, ignoreblanklines = 0, ignoretabexpansion = 0,
		ignorecase = 0, leftcolumn = 0, reportidenticalfiles = 0,
		suppresscommonlines = 0, width = 0, ignoreallspace = 0, sidebyside = 0;

	//Loops through arguments and set flags where needed.
	for (int a = 0; a < argc; a++) {
		char* temp = strdup(strstr(argv[a], "."));	//Filenames have periods
		if (temp != NULL) {
			printf("Hell yeah\n");
			if (numf == 0)
				fname1 = strdup(argv[a]);
			else
				fname2 = strdup(argv[a]);
		}
		if (strcmp(argv[a], "--text") == 0 || strcmp(argv[a], "-a") == 0)
			text = 1;
		else if (strcmp(argv[a], "--ignore-space-change") == 0 || strcmp(argv[a], "-b") == 0)
			ignorespacechange = 1;
		else if (strcmp(argv[a], "--ignore-blank-lines") == 0 || strcmp(argv[a], "-B") == 0)
			ignoreblanklines = 1;
		else if (strcmp(argv[a], "--ignore-tab-expansion") == 0 || strcmp(argv[a], "-E") == 0)
			ignoretabexpansion = 1;
		else if (strcmp(argv[a], "--ignore-case") == 0 || strcmp(argv[a], "-i") == 0)
			ignorecase = 1;
		else if (strcmp(argv[a], "--left-column") == 0)
			leftcolumn = 1;
		else if (strcmp(argv[a], "--recursive") == 0 || strcmp(argv[a], "-r") == 0) {
			printf("Error: --recursive flag (and comparing directories in general)"
				"is not supported in this version of diff.\n");
			return 0;
		}			
		else if (strcmp(argv[a], "--report-identical-files") == 0 || strcmp(argv[a], "-s") == 0)
			reportidenticalfiles = 1;
		else if (strcmp(argv[a], "--suppress-common-lines") == 0)
			suppresscommonlines = 1;
		else if (strcmp(argv[a], "-W") == 0) {
			temp = strdup(argv[a + 1]);
			if (isdigit(temp[0]))
				width = atoi(argv[a + 1]);
			else {
				printf("Error: missing argument -W");
				return 0;	//Breaks if missing arguments
			}
		}
		else if (strcmp(argv[a], "--ignore-all-space") == 0 || strcmp(argv[a], "-w") == 0)
			ignoreallspace = 1;
		else if (strcmp(argv[a], "--side-by-side") == 0 || strcmp(argv[a], "-y") == 0)
			sidebyside = 1;

	}

	//Open the files and check if they are null
	FILE* file1 = fopen(fname1, "r");
	FILE* file2 = fopen(fname2, "r");
	if (file1 == NULL) {
		printf("Error: %s: no such file");
		return 0;
	}
	if (file2 == NULL) {
		printf("Error: %s: no such file");
		return 0;
	}

	//If version, help, or brief are wanted, override normal utility and
	//execute which ever option comes first
	for (int a = 0; a < argc; a++) {
		if (strcmp(argv[a], "--version") == 0 || strcmp(argv[a], "-v") == 0)
			return version();
		else if (strcmp(argv[a], "--help") == 0)
			return help();
		else if (strcmp(argv[a], "--brief") == 0 || strcmp(argv[a], "-q" == 0)) {
			int b = brief(file1, file2, fname1, fname2);
			if (reportidenticalfiles == 1)
				if (b == 1)
					printf("Files %s and %s are identical",fname1,fname2);
		}			
	}

	//Add all lines from both files to hashtable
	int c, lineno = 0;
	char* line_ = (char*)malloc(MAXLINE);
	while ((c = fgetc(file1)) != EOF) {
		ungetc(c,file1);
		getline(line_, MAXLINE, file1);
		install(line_, lineno++, fname1, ignorecase);
	}
	lineno = 0;
	while ((c = fgetc(file2)) != EOF) {
		ungetc(c, file2);
		getline(line_, MAXLINE, file2);
		install(line_, lineno++, fname2, ignorecase);
	}
	/*Pseudo code on how to get this working
		go through both files line by line
		if one doesn't exist in the other
			check if there is a capitalization error
			if not find where to add/delete/move (either at the top or the end)
		if the line exists in the other
			print it with according to all the arguments flagged 
				i.e. sidebyside, suppresscommonlines, width

		cases:
			in file 1, not file 2
			in file 2, not file 1
			almost the same
			moved line in file 1
			moved line in file 2
			same line in bot files
	
	*/
	//Set the file pos back to the beginning so that I can loop through them again
	rewind(file1);
	rewind(file2);
	line* linehold[20];
	int pos = 0;
	while ((getline(line_, MAXLINE, file1)) != 0) {
		line* lp = lookup(line_, ignorecase);
		if (strcmp(lp->fname, fname1) == 0) {
			if (lp->next == NULL) {
				line* temp = lookup(line_, 1);
				if (lp->next != NULL) {
					if (sidebyside) {
						//fuck you 
					}
					else {
						printf("%d");
					}
				}
				while (lp->next == NULL) {
					linehold[pos++] = lp;
					getline(line_, MAXLINE, file1);
					lp = lookup(line_, ignorecase);
				}
				if (sidebyside) {
					//fuck side-by-side
				}
				else {
					printf("%d,%dd%d\n", linehold[0]->linenum, linehold[pos - 1]->linenum,
						lp->next->linenum);
					for (int a = 0; a < pos; a++)
						printf("%s",linehold[a]->content);
				}
			}

		}
		else {

		}
	}



	//save for a bit later
	if (sidebyside) {
		
	}
	else {

	}


	return 0;
}