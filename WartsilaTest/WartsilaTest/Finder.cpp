#include "Finder.h"

Finder::Finder()
{
	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			image_[i][j] = 0;
		}
	}
}

Finder::~Finder()
{

}

bool Finder::find(FILE* _file, unsigned int _err)
{
	if (_file == NULL)
	{
		std::cout << "File not found or path is wrong" << std::endl;
		return 0;
	}

	// Read file
	std::cout << "Reading file " << _file << std::endl;
	int dataLength = width_ * width_ + 2 * (width_ - 1);
	char* readedString(new char[dataLength + 1]);
	fread(readedString, 1, dataLength, _file);
	readedString[dataLength] = '\0';

	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			image_[i][j] = readedString[i*width_ + j + 2*i] - '0';
			std::cout << image_[i][j] << ' ';
			if (image_[i][j])
			{
				++area_;
			}
		}
		std::cout << std::endl;
	}

	delete[] readedString;

	std::cout << "Begin search" << std::endl;
	if (find_square(_err))
	{
		std::cout << "Found square" << std::endl;

		return 1;
	}
	if (find_round(_err))
	{
		std::cout << "Found round" << std::endl;

		return 1;
	}

	return 0;
}

bool Finder::find_square(unsigned int _err)
{
	unsigned int currentError = 0;

	std::pair <int, int> nullPoint(0, 0);

	bool edgeTop = 0;
	bool topFound = 0;
	std::pair<std::pair<int, int>, std::pair<int, int>> top(nullPoint, nullPoint);
	bool edgeBottom = 0;
	bool bottomFound = 0;
	std::pair<std::pair<int, int>, std::pair<int, int>> bottom(nullPoint, nullPoint);
	bool edgeLeft = 0;
	bool leftFound = 0;
	std::pair<std::pair<int, int>, std::pair<int, int>> left(nullPoint, nullPoint);
	bool edgeRight = 0;
	bool rightFound = 0;
	std::pair<std::pair<int, int>, std::pair<int, int>> right(nullPoint, nullPoint);

	bool edgesFound = 0;
	bool outerFound = 0;

	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			// Try to find begin of the edge
			if (!edgeTop && image_[i][j] && !topFound)
			{
				edgeTop = 1;
				top.first = std::make_pair(i, j);
			}
			if (!edgeBottom && image_[width_ - i - 1][j] && !bottomFound)
			{
				edgeBottom = 1;
				bottom.first = std::make_pair(width_ - i - 1, j);
			}
			if (!edgeLeft && image_[j][i] && !leftFound)
			{
				edgeLeft = 1;
				left.first = std::make_pair(j, i);
			}
			if (!edgeRight && image_[j][width_ - i - 1] && !rightFound)
			{
				edgeRight = 1;
				right.first = std::make_pair(j, width_ - i - 1);
			}

			// Try to find end of the edge
			if (edgeTop && !image_[i][j] && !topFound)
			{
				topFound = 1;
				top.second = std::make_pair(i, j - 1);
			}
			if (edgeBottom && !image_[width_ - i - 1][j] && !bottomFound)
			{
				bottomFound = 1;
				bottom.second = std::make_pair(width_ - i - 1, j - 1);
			}
			if (edgeLeft && !image_[j][i] && !leftFound)
			{
				leftFound = 1;
				left.second = std::make_pair(j - 1, i);
			}
			if (edgeRight && !image_[j][width_ - i - 1] && !rightFound)
			{
				rightFound = 1;
				right.second = std::make_pair(j - 1, width_ - i - 1);
			}

			// Edge must be 1
			if (edgeTop && image_[i][j] && topFound)
			{
				return 0;
			}
			if (edgeBottom && image_[width_ - i - 1][j] && bottomFound)
			{
				return 0;
			}
			if (edgeLeft && image_[j][i] && leftFound)
			{
				return 0;
			}
			if (edgeRight && image_[j][width_ - i - 1] && rightFound)
			{
				return 0;
			}


		}

		// Means that we found start & end of the edge, otherwise image is wrong
		if (edgeTop && topFound)
		{
			edgeTop = 0;
			std::cout << "Top edge is (" << top.first.first << ',' << top.first.second << "), (" << top.second.first << ',' << top.second.second << ')' << std::endl;
		}
		else if (edgeTop && !topFound)
		{
			return 0;
		}
		if (edgeBottom && bottomFound)
		{
			edgeBottom = 0;
			std::cout << "Bottom edge is (" << bottom.first.first << ',' << bottom.first.second << "), (" << bottom.second.first << ',' << bottom.second.second << ')' << std::endl;
		}
		else if (edgeBottom && !bottomFound)
		{
			return 0;
		}
		if (edgeLeft && leftFound)
		{
			edgeLeft = 0;
			std::cout << "Left edge is (" << left.first.first << ',' << left.first.second << "), (" << left.second.first << ',' << left.second.second << ')' << std::endl;
		}
		else if (edgeLeft && !leftFound)
		{
			return 0;
		}
		if (edgeRight && rightFound)
		{
			edgeRight = 0;
			std::cout << "Right edge is (" << right.first.first << ',' << right.first.second << "), (" << right.second.first << ',' << right.second.second << ')' << std::endl;
		}
		else if (edgeRight && !rightFound)
		{
			return 0;
		}

		if (topFound && bottomFound && leftFound && rightFound) // All 4 edges found
		{
			std::cout << "All edges is found" << std::endl;
			edgesFound = 1;
			break;
		}
	}

	if (!topFound) // Case when all cells == 0
	{
		std::cout << "Image is empty" << std::endl;
		return 0;
	}

	// In search for the square ends of the edges must coincide
	if (edgesFound)
	{
		if ((top.second.second - top.first.second + 1) < minLength || (bottom.second.second - bottom.first.second + 1) < minLength || (left.second.first - left.first.first + 1) < minLength || (right.second.first - right.first.first + 1) < minLength)
		{
			std::cout << "Edge length is shorter than minimum" << std::endl;
			return 0;
		}
		if ((top.second.second - top.first.second + 1) > maxLength || (bottom.second.second - bottom.first.second + 1) > maxLength || (left.second.first - left.first.first + 1) > maxLength || (right.second.first - right.first.first + 1) > maxLength)
		{
			std::cout << "Edge length is longer than maximum" << std::endl;
			return 0;
		}

		if ((top.first == left.first) && (top.second == right.first) && (bottom.first == left.second) && (bottom.second == right.second))
		{
			outerFound = 1;
			std::cout << "Outer is a square" << std::endl;
		}

		if (outerFound)
		{
			for (int i = top.first.first + 1; i < bottom.second.first; ++i)
			{
				for (int j = top.first.second + 1; j < bottom.second.second; ++j)
				{
					if (!image_[i][j])
					{
						++currentError;
					}

					if (currentError > _err)
					{
						std::cout << "More noise than expected" << std::endl;
						return 0;
					}
				}
			}

			std::cout << "Square is filled inside" << std::endl;
			std::cout << "Square edge length is " << top.second.second - top.first.second + 1 << std::endl;
			std::cout << "Square top left point is (" << top.first.first << ',' << top.first.second << ')' << std::endl;
			return 1;
		}

		std::cout << "Outer is not found" << std::endl;
		return 0;
	}

	std::cout << "Edges is not found" << std::endl;
	return 0;
}

bool Finder::find_round(unsigned int _err)
{



	return 0;
}