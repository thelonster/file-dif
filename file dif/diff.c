#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 200
#define HASHSIZE 101

typedef struct line line;

line *hashtab[HASHSIZE];

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

int brief(FILE *fp1, FILE *fp2, char* fname1, char* fname2) {
	char *fp1line = (char*)malloc(MAXLINE);
	char *fp2line = (char*)malloc(MAXLINE);
	while (strcmp(fp1line, "") != 0 && strcmp(fp2line, "") == 0) {
		getline(fp1line, MAXLINE, fp1);
		getline(fp2line, MAXLINE, fp2);
		if (strcmp(fp1line, fp2line) != 0) {
			printf("Files %s and %s differ",fname1,fname2);
			return 1;	//Return 1 because files differ
		}
	}
	return 0;	//Return 0 because files are identical
}

unsigned hash(char* s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

unsigned ichash(char* s) {
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = tolower(*s) + 31 * hashval;	//Forces lower case
	return hashval % HASHSIZE;
}

line *install(char* c, int ln, char* fn, int igncse) {
	line* lp;
	unsigned hashval;
	if ((lp = lookup(c, igncse)) == NULL) {
		lp = (line*)malloc(sizeof(*lp));
		if (lp == NULL || (lp->content = strdup(c)) == NULL)
			return NULL;
		lp->linenum = ln;
		lp->fname = strdup(fn);
		hashval = igncse ? hash(c) : ichash(c);
		lp->next = hashtab[hashval];
		hashtab[hashval] = lp;
	}
	else {
		while (lp != NULL)
			lp = lp->next;
		lp = (line*)malloc(sizeof(*lp));
		lp->content = strdup(c);
		lp->linenum = ln;
		lp->fname = strdup(fn);
		lp->next = NULL;
	}
	return lp;
}

line *lookup(char* s, int igncse) {
	line* lp;
	for (lp = igncse ? hashtab[hash(s)] : hashtab[ichash(s)]; lp != NULL; lp = lp->next)
		if (!strcmp(s, lp->content))
			return lp;
	return NULL;
}

void removeline(char* c, int igncse) {
	line *lp, *pp;
	for (pp = NULL, lp = igncse ? hashtab[hash(c)] : hashtab[ichash(c)]; lp != NULL; pp = lp, lp = lp->next) {
		if (!strcmp(c, lp->content)) {
			if (pp == NULL && igncse)
				hashtab[ichash(c)] = lp->next;
			else if (pp == NULL && !igncse)
				hashtab[hash(c)] = lp->next;
			else
				pp->next = lp->next;
			free(lp->content);
			free(lp->fname);
			free(lp);
			return;
		}
	}
}