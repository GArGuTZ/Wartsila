#define _CRT_SECURE_NO_DEPRECATE

#include <cstdlib>
#include "Finder.h"

#define ARG_COUNT 2

int main(int argc, char* argv[])
{
	if (argc != ARG_COUNT)
	{
		fprintf(stderr, "Too few arguments\n");
		return EXIT_FAILURE;
	}
	
	FILE* fileToRead = fopen(argv[1], "rb");
	if (fileToRead == NULL)
	{
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	Finder firstFinder;
	firstFinder.find(fileToRead);

	fclose(fileToRead);
	return EXIT_SUCCESS;
}