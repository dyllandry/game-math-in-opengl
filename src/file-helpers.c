#include <stdio.h>
#include <stdlib.h>
#include "file-helpers.h"

char * getFileBytes(const char *filePath)
{
	FILE *file = fopen(filePath, "r");
	if (!file)
	{
		printf("ERROR::FILE_HELPERS::GET_FILE_TEXT::OPEN_FILE_FAILED PATH=%s\n", filePath);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	// Use calloc to zero memory, thus null terminating every character ahead of time.
	char *fileText = calloc(fileSize + 1, 1);
	if (!fileText)
	{
		printf("ERROR::FILE_HELPERS::GET_FILE_TEXT::ALLOCATE_BUFFER_FOR_FILE_FAILED PATH=%s\n", filePath);
		exit(EXIT_FAILURE);
	}

	fread(fileText, 1, fileSize, file);
	if (ferror(file))
	{
		printf("ERROR::FILE_HELPERS::GET_FILE_TEXT::READ_FILE_FAILED PATH=%s\n", filePath);
		exit(EXIT_FAILURE);
	}

	fclose(file);
	printf("INFO::FILE_HELPERS::GET_FILE_TEXT::READ_FILE FILE=%s BYTES=%ld\n", filePath, fileSize);
	return fileText;
}
