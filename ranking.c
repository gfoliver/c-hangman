#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

void getRanking() {
	// Open the ranking file
	FILE *fp = fopen("ranking.txt", "r");
	char str[50];
	
	// Print out all the lines
	while (fgets(str, sizeof(str), fp)) {
		printf("%s\n", str);
	}
	
	fclose(fp);
}

void exportRanking(char data[]) {
	// Open the ranking file
	FILE *fp = fopen("ranking.txt", "a");
	
	// Append data to the file
	fputs(data, fp);
	
	fclose(fp);
}

void resetRanking() {
	// Open the ranking file
	FILE *fp = fopen("ranking.txt", "w");
	fclose(fp);
}
