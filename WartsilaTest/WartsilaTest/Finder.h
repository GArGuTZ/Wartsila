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
	bool find_square(unsigned int _err = 0);
	bool find_round(unsigned int _err = 0);

	const static unsigned int width_ = 15; // Size of image
	const static unsigned int minLength = 5;
	const static unsigned int maxLength = 10;

	std::array<std::array<int, width_>, width_> image_;
	std::array<std::array<int, width_>, width_> seen_;

	unsigned int area_ = 0;
};