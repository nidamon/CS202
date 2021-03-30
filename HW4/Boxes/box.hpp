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
#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::unique_ptr;
using std::make_unique;

// ########################################################################################################
// Box
// ########################################################################################################

class Box
{
public:
	Box();
	Box(int w, int h);
	virtual ~Box();

	int getWidth() const;
	int getHeight() const;

	void setWidth(int w);
	void setHeight(int h);

	virtual void print(ostream& os) const = 0;
	virtual string type() const = 0;

	int _width;
	int _height;

};

// ########################################################################################################
// FilledBox
// ########################################################################################################

class FilledBox : public Box
{
public:
	using Box::Box;
	FilledBox();
	FilledBox(int w, int h);

	void print(ostream& os) const override;
	string type() const override;

};

// ########################################################################################################
// HollowBox
// ########################################################################################################

class HollowBox : public Box
{
public:
	using Box::Box;
	HollowBox();
	HollowBox(int w, int h);

	void print(ostream& os) const override;
	string type() const override;
};

// ########################################################################################################
// CheckeredBox
// ########################################################################################################

class CheckeredBox : public Box
{
public:
	using Box::Box;
	CheckeredBox();
	CheckeredBox(int w, int h);

	void print(ostream& os) const override;
	string type() const override;
};

ostream& operator<<(ostream& os, const Box& b);

unique_ptr<Box> boxFactory(char c, int w, int h);

#endif // !BOX_HPP

