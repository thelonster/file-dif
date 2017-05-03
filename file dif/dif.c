#include "dif.h"
#include <stdio.h>
#include <string.h>

int getline(char *line, int max, FILE *file) {
	if (fgets(line, max, file) == NULL)
		return 0;
	else
		return strlen(line);
}
