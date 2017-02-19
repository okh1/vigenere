#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Vigenere.h"
#define MAX_PATH_LENGTH 1000
#define MAX_PERIODO 100

int main()
{
	int scelta;
	printf("Encode/decode texts using the Vigenere cipher\n");
	printf("===============\n");
	printf("1. Encode file with keyword\n");
	printf("2. Decode file given keyword\n");
	printf("3. Attack file trying to guess the keyword\n");
	printf("4. Exit\n");
	printf("Select: ");
	scanf("%d", &scelta);
	switch (scelta)
	{
		case 1: //Codifica
		{
			char chiave[MAX_PERIODO];
			char path_in[MAX_PATH_LENGTH];
			char path_out[MAX_PATH_LENGTH];
			printf("Write the keyword you want to encode the text with:\n");
			scanf("%s", chiave); getc(stdin);
			printf("Write the input file's path:\n");
			fgets(path_in, MAX_PATH_LENGTH, stdin);
			int ln = strlen(path_in) - 1;
			if (path_in[ln] == '\n')
				path_in[ln] = '\0';
			printf("Write the encoded output file's path:\n");
			fgets(path_out, MAX_PATH_LENGTH, stdin);
			ln = strlen(path_out) - 1;
			if (path_out[ln] == '\n')
				path_out[ln] = '\0';

			FILE* in = fopen(path_in, "r");
			FILE* out = fopen(path_out, "w");
			if (in != NULL && out != NULL) Codifica(in, out, chiave);
			else printf("Couldn't open the file.\n");
		}
		break;
		case 2: //Decodifica
		{
			char chiave[MAX_PERIODO];
			char path_in[MAX_PATH_LENGTH];
			char path_out[MAX_PATH_LENGTH];
			printf("Write the keyword you want to decode the text with:\n");
			scanf("%s", chiave); getc(stdin);
			printf("Write the input file's path:\n");
			fgets(path_in, MAX_PATH_LENGTH, stdin);
			int ln = strlen(path_in) - 1;
			if (path_in[ln] == '\n')
				path_in[ln] = '\0';
			printf("Write the decoded output file's path:\n");
			fgets(path_out, MAX_PATH_LENGTH, stdin);
			ln = strlen(path_out) - 1;
			if (path_out[ln] == '\n')
				path_out[ln] = '\0';

			FILE* in = fopen(path_in, "r");
			FILE* out = fopen(path_out, "w");
			if (in != NULL && out != NULL) Decodifica(in, out, chiave);
			else printf("Couldn't open the file.\n");
		}
		break;
		case 3: //Attacco
		{
			char path_in[MAX_PATH_LENGTH]; getc(stdin);
			printf("Write the input file's path:\n");
			fgets(path_in, MAX_PATH_LENGTH, stdin);
			int ln = strlen(path_in) - 1;
			if (path_in[ln] == '\n')
				path_in[ln] = '\0';

			FILE* in = fopen(path_in, "r");
			if (in != NULL) Attacco(in);
			else printf("Coudln't open the file.\n");
		}
		break;
		case 4:
		default:
			return 1; //Usciamo dal programma
	}

	printf("\n");
    return 0;
}

