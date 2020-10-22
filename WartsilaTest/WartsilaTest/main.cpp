#define _CRT_SECURE_NO_DEPRECATE

#include <cstdlib>
#include "Finder.h"

#define MIN_ARG_COUNT 2
#define MAX_ARG_COUNT 3

int main(int argc, char* argv[])
{
	if (argc < MIN_ARG_COUNT)
	{
		fprintf(stderr, "Too few arguments\n");
		return EXIT_FAILURE;
	}
	if (argc > MAX_ARG_COUNT)
	{
		fprintf(stderr, "Too many arguments\n");
		return EXIT_FAILURE;
	}
	
	FILE* fileToRead = fopen(argv[1], "rb");
	if (fileToRead == NULL)
	{
		perror("Error opening file");
		return EXIT_FAILURE;
	}

	Finder firstFinder;
	if (argc == MIN_ARG_COUNT)
	{
		firstFinder.find(fileToRead);
	}
	else
	{
		int maxNoise = std::atoi(argv[2]);
		if (maxNoise < 0)
		{
			maxNoise = 0;
		}
		firstFinder.find(fileToRead, maxNoise);
	}

	fclose(fileToRead);
	return EXIT_SUCCESS;
}