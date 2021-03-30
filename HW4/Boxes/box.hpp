/*box.hpp
Nathan Damon
3/29/2021
This is the header file for the Box Class and it's derivatives
*/


#ifndef BOX_HPP
#define BOX_HPP

#include <ostream>
using std::ostream;
#include <string>
using std::string;

// ########################################################################################################
// Box
// ########################################################################################################

class Box
{
public:
	Box();
	Box(unsigned int w, unsigned int h);

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void setWidth(unsigned int w);
	void setHeight(unsigned int h);

	virtual void print(ostream& os) const = 0;
	virtual string type() const = 0;

	unsigned int _width;
	unsigned int _height;

};

// ########################################################################################################
// FilledBox
// ########################################################################################################

class FilledBox : public Box
{
	using Box::Box;
	FilledBox();

};

// ########################################################################################################
// HollowBox
// ########################################################################################################

class HollowBox : public Box
{
	using Box::Box;
	HollowBox();
};

// ########################################################################################################
// CheckeredBox
// ########################################################################################################

class CheckeredBox : public Box
{
	using Box::Box;
	CheckeredBox();
};

ostream& operator<<(ostream& os, const Box& b);

#endif // !BOX_HPP

