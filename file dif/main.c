#include "diff.h"
#include <stdio.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("Error: not enough arguments\n");
		printf("");
		return 2;
	}
	for (int a = 0; a < argc; a++) {
		if (strcmp(argv[a], "--version") == 0)
			return version();
		else if (strcmp(argv[a], "--help") == 0)
			return help();			
	}
	return 0;
}