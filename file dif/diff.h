#ifndef dif_h
#define dif_h
#define _CRT_NO_SECURE_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>

struct line {
	struct line* next;
	char* content;
	int linenum;
	char* fname;
};

int getline(char*  line, int max, FILE *file);
/*Routine that compares 2 files and prints out files that are different*/
void difroutine();
/*Prints out the version information*/
int version();
/*Prints out help information*/
int help();
/*Prints out whether or not the files differ*/
int brief(FILE *fp1, FILE *fp2, char* fname1, char* fname2);
/*Normal Hash*/
unsigned hash(char* s);
/*Hash for ignore case*/
unsigned ichash(char* s);
/*Installs line into hash table*/
struct line *install(char* c, int ln, char* fn, int igncse);
/*Looks up if a line is in the hash table*/
struct line *lookup(char* s, int igncse);

#endif // !dif_h
