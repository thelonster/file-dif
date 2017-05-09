#include "diff.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("Error: not enough arguments\n");
		printf("");
		return 2;
	}
	char* fname1, fname2;
	int numf = 0;

	int text = 0, ignorespacechange = 0, ignoreblanklines = 0, ignoretabexpansion = 0,
		ignorecase = 0, leftcolumn = 0, reportidenticalfiles = 0, recursive = 0,
		suppresscommonlines = 0, width = 0, ignoreallspace = 0, sidebyside = 0;

	for (int a = 0; a < argc; a++) {
		char* temp = strdup(strstr(argv[a], "."));
		if (temp != NULL) {
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
		else if (strcmp(argv[a], "--recursive") == 0 || strcmp(argv[a], "-r") == 0)
			recursive = 1;
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

	}
	for (int a = 0; a < argc; a++) {
		if (strcmp(argv[a], "--version") == 0 || strcmp(argv[a], "-v") == 0)
			return version();
		else if (strcmp(argv[a], "--help") == 0)
			return help();
		else if (strcmp(argv[a], "--brief") == 0 || strcmp(argv[a], "-q" == 0))
			;// return brief();
	}
	return 0;
}