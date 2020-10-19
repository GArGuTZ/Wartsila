#define _CRT_SECURE_NO_DEPRECATE

#include "Finder.h"

void main()
{
	Finder firstFinder;
	char* pathToEmpty = "Round06w05.txt";
	FILE* fileToRead = fopen(pathToEmpty, "rb");
	//emptyLRead.Deserialize(fileToRead);
	std::cout << firstFinder.find(fileToRead) << std::endl;
	fclose(fileToRead);
	return;
}