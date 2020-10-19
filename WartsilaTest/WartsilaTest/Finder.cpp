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
	std::pair <int, int> nullPoint(0, 0);
	top_ = std::make_pair(nullPoint, nullPoint);
	bottom_ = std::make_pair(nullPoint, nullPoint);
	left_ = std::make_pair(nullPoint, nullPoint);
	right_ = std::make_pair(nullPoint, nullPoint);
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

	if (area_ == 0)
	{
		std::cout << "Image is empty" << std::endl;
		return 0;
	}

	edgesFound_ = find_edges();
	if (!edgesFound_)
	{
		std::cout << "Edges not found or image is bad" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "All edges is found" << std::endl;
	}

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

bool Finder::find_edges()
{
	bool edgeTop = 0;
	bool topFound = 0;
	bool edgeBottom = 0;
	bool bottomFound = 0;
	bool edgeLeft = 0;
	bool leftFound = 0;
	bool edgeRight = 0;
	bool rightFound = 0;

	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			// Try to find begin of the edge
			if (!edgeTop && image_[i][j] && !topFound)
			{
				edgeTop = 1;
				top_.first = std::make_pair(i, j);
			}
			if (!edgeBottom && image_[width_ - i - 1][j] && !bottomFound)
			{
				edgeBottom = 1;
				bottom_.first = std::make_pair(width_ - i - 1, j);
			}
			if (!edgeLeft && image_[j][i] && !leftFound)
			{
				edgeLeft = 1;
				left_.first = std::make_pair(j, i);
			}
			if (!edgeRight && image_[j][width_ - i - 1] && !rightFound)
			{
				edgeRight = 1;
				right_.first = std::make_pair(j, width_ - i - 1);
			}

			// Try to find end of the edge
			if (edgeTop && !image_[i][j] && !topFound)
			{
				topFound = 1;
				top_.second = std::make_pair(i, j - 1);
			}
			if (edgeBottom && !image_[width_ - i - 1][j] && !bottomFound)
			{
				bottomFound = 1;
				bottom_.second = std::make_pair(width_ - i - 1, j - 1);
			}
			if (edgeLeft && !image_[j][i] && !leftFound)
			{
				leftFound = 1;
				left_.second = std::make_pair(j - 1, i);
			}
			if (edgeRight && !image_[j][width_ - i - 1] && !rightFound)
			{
				rightFound = 1;
				right_.second = std::make_pair(j - 1, width_ - i - 1);
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
			std::cout << "Top edge is (" << top_.first.first << ',' << top_.first.second << "), (" << top_.second.first << ',' << top_.second.second << ')' << std::endl;
		}
		else if (edgeTop && !topFound)
		{
			return 0;
		}
		if (edgeBottom && bottomFound)
		{
			edgeBottom = 0;
			std::cout << "Bottom edge is (" << bottom_.first.first << ',' << bottom_.first.second << "), (" << bottom_.second.first << ',' << bottom_.second.second << ')' << std::endl;
		}
		else if (edgeBottom && !bottomFound)
		{
			return 0;
		}
		if (edgeLeft && leftFound)
		{
			edgeLeft = 0;
			std::cout << "Left edge is (" << left_.first.first << ',' << left_.first.second << "), (" << left_.second.first << ',' << left_.second.second << ')' << std::endl;
		}
		else if (edgeLeft && !leftFound)
		{
			return 0;
		}
		if (edgeRight && rightFound)
		{
			edgeRight = 0;
			std::cout << "Right edge is (" << right_.first.first << ',' << right_.first.second << "), (" << right_.second.first << ',' << right_.second.second << ')' << std::endl;
		}
		else if (edgeRight && !rightFound)
		{
			return 0;
		}

		if (topFound && bottomFound && leftFound && rightFound) // All 4 edges found
		{
			return 1;
		}
	}

	if (!topFound) // Case when all cells == 0
	{
		std::cout << "Image is empty" << std::endl;
		return 0;
	}

	return 0;
}

bool Finder::find_square(unsigned int _err)
{
	if (!edgesFound_)
	{
		return 0;
	}

	unsigned int currentError = 0;

	bool outerFound = 0;

	if ((top_.second.second - top_.first.second + 1) < minLength_ || (bottom_.second.second - bottom_.first.second + 1) < minLength_ || (left_.second.first - left_.first.first + 1) < minLength_ || (right_.second.first - right_.first.first + 1) < minLength_)
	{
		std::cout << "Edge length is shorter than minimum" << std::endl;
		return 0;
	}
	if ((top_.second.second - top_.first.second + 1) > maxLength_ || (bottom_.second.second - bottom_.first.second + 1) > maxLength_ || (left_.second.first - left_.first.first + 1) > maxLength_ || (right_.second.first - right_.first.first + 1) > maxLength_)
	{
		std::cout << "Edge length is longer than maximum" << std::endl;
		return 0;
	}

	// In search for the square ends of the edges must coincide
	if ((top_.first == left_.first) && (top_.second == right_.first) && (bottom_.first == left_.second) && (bottom_.second == right_.second))
	{
		outerFound = 1;
		std::cout << "Outer is a square" << std::endl;
	}

	if (outerFound)
	{
		for (int i = top_.first.first + 1; i < bottom_.second.first; ++i)
		{
			for (int j = top_.first.second + 1; j < bottom_.second.second; ++j)
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
		std::cout << "Square edge length is " << top_.second.second - top_.first.second + 1 << std::endl;
		std::cout << "Square top left point is (" << top_.first.first << ',' << top_.first.second << ')' << std::endl;
		return 1;
	}

	std::cout << "Outer is not found" << std::endl;
	return 0;
}

bool Finder::check_Bresenham(int _x, int _y, unsigned int _radius, unsigned int _err)
{
	unsigned int currentErr = 0;
	//std::cout << "Start Bresenham with x = " << _x << ", y = " << _y << ", & radius = " << _radius << std::endl;
	int x = 0;
	int y = _radius;
	int decision = 3 - 2 * _radius;
	//std::cout << "Start x = " << x << ", start y = " << y << ", Decision = " << decision << std::endl;
	//std::cout << "Octant 1 : (" << _x + x << ", " << _y + y << ')' << std::endl;
	//std::cout << "Octant 2 : (" << _x + y << ", " << _y + x << ')' << std::endl;


	for (x += 1; x < y; ++x)
	{
		if (decision < 0)
		{
			decision = decision + 4 * x + 6;
		}
		else
		{
			--y;
			decision = decision + 4 * (x - y) + 10;
		}

		// Check 4 columns in the inner of the round using symmetry
		int currentX1 = _x + x;
		int currentX2 = _x - x;
		int currentY1 = _y + y;
		int currentY2 = _y + x;
		for (int i = _y - y; i <= currentY1; ++i)
		{
			if (!image_[i][currentX1] || !image_[i][currentX2])
			{
				++currentErr;
			}
		}
		currentX1 = _x + y;
		currentX2 = _x - y;
		for (int i = _y - x; i <= currentY2; ++i)
		{
			if (!image_[i][currentX1] || !image_[i][currentX2])
			{
				++currentErr;
			}
		}

		if (currentErr > _err)
		{
			std::cout << "More noise than expected" << std::endl;
			return 0;
		}
		//std::cout << "New x = " << x << ", New y = " << y << ", Decision = " << decision << std::endl;
		//std::cout << "Octant 1 : (" << _x + x << ", " << _y + y << ')' << std::endl;
		//std::cout << "Octant 2 : (" << _x + y << ", " << _y + x << ')' << std::endl;
	}

	std::cout << "Round is filled" << std::endl;
	return 1;
}

bool Finder::find_round(unsigned int _err)
{
	if (!edgesFound_)
	{
		return 0;
	}

	unsigned int currentErr = 0;

	bool symmetryFound = 0;

	// In search for the round edges must be symmetrical
	if ((top_.first.second == bottom_.first.second) && (top_.second.second == bottom_.second.second) && (left_.first.first == right_.first.first) && (left_.second.first == right_.second.first))
	{
		symmetryFound = 1;
		std::cout << "Outer is a symmetrical" << std::endl;
	}
	else
	{
		std::cout << "Outer is not symmetrical" << std::endl;
		return 0;
	}

	int diameter = bottom_.first.first - top_.first.first + 1;
	std::cout << "Round diameter is " << diameter << std::endl;
	if (diameter < minLength_)
	{
		std::cout << "Diameter is shorter than minimum" << std::endl;
		return 0;
	}
	if (diameter > maxLength_)
	{
		std::cout << "Diameter is longer than maximum" << std::endl;
		return 0;
	}

	int radius = (diameter - 1) / 2;
	// Symmetrical edge must different
	if (top_.first.second - left_.first.second < radius - 1 || right_.first.second - top_.first.second < radius - 1 || bottom_.first.second - left_.second.second < radius - 1 || right_.second.second - bottom_.second.second < radius - 1 || bottom_.first.first - left_.second.first < radius - 1 || left_.first.first - top_.first.first < radius - 1 || bottom_.second.first - right_.second.first < radius - 1 || right_.first.first - top_.second.first < radius - 1)
	{
		std::cout << "Edges is too close" << std::endl;
		return 0;
	}

	// Check one of the axis
	int axis = (left_.first.first + left_.second.first) / 2;
	for (int j = left_.first.second + 1; j < right_.first.second; ++j)
	{
		if (!image_[axis][j])
		{
			++currentErr;
		}
	}
	if (currentErr > _err)
	{
		std::cout << "More noise than expected" << std::endl;
		return 0;
	}

	int centerX = (top_.first.second + top_.second.second) / 2;
	int centerY = (bottom_.first.first + top_.first.first) / 2;
	// Then compare Bresenham's drawing of circle with image
	if (diameter & 1)
	{
		std::cout << "Diameter is odd" << std::endl;
		if (check_Bresenham(centerX, centerY, radius))
		{
			std::cout << "Center in " << centerX << ',' << centerY << " and diameter " << diameter << std::endl;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		++centerX;
		std::cout << "Diameter is even" << std::endl;
		// Check 4 diagonals, 1 column & 1 line around the central round - valid check for rounds with diameters <= 10
		// 4 points must not filled - valid check for rounds with diameters <= 10
		if (image_[centerY - 3][centerX + 3] || image_[centerY - 3][centerX - 4] || image_[centerY + 4][centerX + 3] || image_[centerY + 4][centerX - 4])
		{
			std::cout << image_[centerY - 3][centerX + 3] << image_[centerY - 3][centerX - 4] << image_[centerY + 4][centerX + 3] << image_[centerY + 4][centerX - 4] << std::endl;
			std::cout << "This is not a round" << std::endl;
			return 0;
		}
		int startColumn = left_.first.second;
		int currentLine = left_.first.first;
		int endColumn = top_.first.second;
		for (int j = startColumn; j < endColumn; ++j) // top left diagonal
		{
			if (!image_[currentLine][j])
			{
				++currentErr;
			}
			--currentLine;
		}
		startColumn = bottom_.second.second;
		currentLine = bottom_.second.first;
		endColumn = right_.second.second;
		for (int j = startColumn; j < endColumn; ++j) // bottom right diagonal
		{
			if (!image_[currentLine][j])
			{
				++currentErr;
			}
			--currentLine;
		}
		startColumn = left_.second.second;
		currentLine = left_.second.first;
		endColumn = bottom_.first.second;
		for (int j = startColumn; j < endColumn; ++j) // 2 bottom left diagonals
		{
			if (!image_[currentLine][j] || !image_[currentLine][j + 1])
			{
				++currentErr;
			}
			++currentLine;
		}

		startColumn = bottom_.first.second;
		currentLine = bottom_.first.first - 1;
		endColumn = bottom_.second.second;
		for (int j = startColumn; j < endColumn; ++j) // 1 bottom line
		{
			if (!image_[currentLine][j])
			{
				++currentErr;
			}
		}

		int startLine = left_.first.first;
		int currentColumn = left_.first.second + 1;
		int endLine = left_.second.first;
		for (int i = startLine; i < endLine; ++i) // 1 bottom line
		{
			if (!image_[i][currentColumn])
			{
				++currentErr;
			}
		}




		if (currentErr > _err)
		{
			std::cout << "More noise than expected" << std::endl;
			return 0;
		}

		if (check_Bresenham(centerX, centerY, radius))
		{
			std::cout << "Center in " << centerX << ',' << centerY << " and diameter " << diameter << std::endl;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}