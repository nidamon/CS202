/*box.cpp
Nathan Damon
3/29/2021
This is the cpp file for the Box Class and it's derivatives
*/

#include "box.hpp"

// Takes an ostream and outputs the box to it
ostream& operator<<(ostream& os, const Box& b)
{
	b.print(os);
	return os;
}

// ########################################################################################################
// Box
// ########################################################################################################

Box::Box() : _width{1}, _height{1} {}
Box::Box(int w, int h) : _width{ w }, _height{ h } {}

Box::~Box() {}

// Returns the width
int Box::getWidth() const
{
	return _width;
}

// Returns the height
int Box::getHeight() const
{
	return _height;
}

// Sets the width
void Box::setWidth(int w)
{
	_width = w;
}

// Sets the height
void Box::setHeight(int h)
{
	_height = h;
}


// ########################################################################################################
// FilledBox
// ########################################################################################################

FilledBox::FilledBox() : Box() {}
FilledBox::FilledBox(int w, int h) : Box(w, h) {}

void FilledBox::print(ostream& os) const
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			os << 'x';
		}
		os << '\n';
	}
}

string FilledBox::type() const
{
	return "Filled";
}

// ########################################################################################################
// HollowBox
// ########################################################################################################

HollowBox::HollowBox() : Box() {}
HollowBox::HollowBox(int w, int h) : Box(w, h) {}

void HollowBox::print(ostream& os) const
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			if ((x == 0 || x == _width - 1) || (y == 0 || y == _height - 1))
				os << 'x';
			else
				os << ' ';
		}
		os << '\n';
	}
}

string HollowBox::type() const
{
	return "Hollow";
}

// ########################################################################################################
// CheckeredBox
// ########################################################################################################

CheckeredBox::CheckeredBox() : Box() {}
CheckeredBox::CheckeredBox(int w, int h) : Box(w, h) {}

void CheckeredBox::print(ostream& os) const
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			if ((y + x) % 2 == 0)
				os << 'x';
			else
				os << ' ';
		}
		os << '\n';
	}
}

string CheckeredBox::type() const
{
	return "Checkered";
}

unique_ptr<Box> boxFactory(char c, int w, int h)
{
	// If ask for a Filled Box
	if (c == 'f' || c == 'F')
		return make_unique<FilledBox>(w, h);
	// If ask for a Hollow Box
	if (c == 'h' || c == 'H')
		return make_unique<HollowBox>(w, h);
	// If ask for a Checkered Box
	if (c == 'c' || c == 'C')
		return make_unique<CheckeredBox>(w, h);
}

