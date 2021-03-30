/*box.hpp
Nathan Damon
3/29/2021
This is the header file for the Box Class and it's derivatives
*/


#ifndef BOX_HPP
#define BOX_HPP

class Box
{
public:
	Box();
	Box(unsigned int w, unsigned int h);

	unsigned int getWidth();
	unsigned int getHeight();

	void setWidth(unsigned int w);
	void setHeight(unsigned int h);

	unsigned int _width;
	unsigned int _height;

};

class FilledBox : public Box
{

};

class HollowBox : public Box
{

};

class CheckeredBox : public Box
{

};



#endif // !BOX_HPP

