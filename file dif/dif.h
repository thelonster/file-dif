#ifndef dif_h
#define dif_h
#define _CRT_NO_SECURE_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int getline(char*  line, int max, FILE *file);
/*Routine that compares 2 files and prints out files that are different*/
void difroutine();


#endif // !dif_h
