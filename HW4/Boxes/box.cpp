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
Box::Box(unsigned int w, unsigned int h) : _width{ w }, _height{ h } {}

// Returns the width
unsigned int Box::getWidth() const
{
	return _width;
}

// Returns the height
unsigned int Box::getHeight() const
{
	return _height;
}

// Sets the width
void Box::setWidth(unsigned int w)
{
	_width = w;
}

// Sets the height
void Box::setHeight(unsigned int h)
{
	_height = h;
}


// ########################################################################################################
// FilledBox
// ########################################################################################################

FilledBox::FilledBox() : Box() {}
FilledBox::FilledBox(unsigned int w, unsigned int h) : Box(w, h) {}

string FilledBox::type() const
{
	return "Filled";
}

// ########################################################################################################
// HollowBox
// ########################################################################################################

HollowBox::HollowBox() : Box() {}
HollowBox::HollowBox(unsigned int w, unsigned int h) : Box(w, h) {}

string HollowBox::type() const
{
	return "Hollow";
}

// ########################################################################################################
// CheckeredBox
// ########################################################################################################

CheckeredBox::CheckeredBox() : Box() {}
CheckeredBox::CheckeredBox(unsigned int w, unsigned int h) : Box(w, h) {}

string CheckeredBox::type() const
{
	return "Checkered";
}



