#include <iostream>
#include <array>
#include <utility>

class Finder
{
public:
	Finder();
	~Finder();

	bool find(FILE* _file, unsigned int _err = 0);
private:
	bool edgesFound_ = 0;
	bool find_edges();
	bool find_square(unsigned int _err = 0);
	bool check_Bresenham(int _x, int _y, unsigned int _radius, unsigned int _err = 0);
	bool find_round(unsigned int _err = 0);

	const static unsigned int width_ = 15; // Size of image
	const static unsigned int minLength_ = 5;
	const static unsigned int maxLength_ = 10;

	std::array<std::array<int, width_>, width_> image_;
	std::array<std::array<int, width_>, width_> seen_;

	unsigned int area_ = 0;

	std::pair<std::pair<int, int>, std::pair<int, int>> top_;
	std::pair<std::pair<int, int>, std::pair<int, int>> bottom_;
	std::pair<std::pair<int, int>, std::pair<int, int>> left_;
	std::pair<std::pair<int, int>, std::pair<int, int>> right_;
};