/*box.cpp
Nathan Damon
3/29/2021
This is the cpp file for the Box Class and it's derivatives
*/

#include "box.hpp"

Box::Box() : _width{2}, _height{2} {}

Box::Box(unsigned int w, unsigned int h) : _width{ w }, _height{ h } {}

unsigned int Box::getWidth()
{
	return _width;
}

unsigned int Box::getHeight()
{
	return _height;
}

void Box::setWidth(unsigned int w)
{
	_width = w;
}

void Box::setHeight(unsigned int h)
{
	_height = h;
}




