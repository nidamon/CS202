/*Lab11Main.cpp
Nathan Damon
CS 202
3/23/2021
This is the main file for lab 11
*/

#include <iostream>
using std::cout;
using std::endl;

struct Point3D
{
	Point3D(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}
	float _x;
	float _y;
	float _z;
};

struct Dimension3D
{
	float _xWidth;
	float _yWidth;
	float _zHeight;
};

class Object
{
public:
	Object() : _position(0.0f, 0.0f, 0.0f) {
		cout << "Called Object default constructor. Values: {"
			<< _position._x << ", " << _position._y << ", " << _position._z << "}" << endl;
	}

	Object(const Point3D& pos) : _position(pos) {
		cout << "Called Object member variable setting constructor.Values: {"
			<< _position._x << ", " << _position._y << ", " << _position._z << "}" << endl;
	}

	~Object(){
		cout << "Called Object destructor." << endl;
	}

private:
	Point3D _position;
};

class GameBoard : public Object
{
public:
	using Object::Object;
	GameBoard() : _dimensions{ 0.0f, 0.0f, 0.0f } {
		cout << "Called GameBoard default constructor. Values: {"
			<< _dimensions._xWidth << ", " << _dimensions._yWidth << ", " << _dimensions._zHeight << "}" << endl;
	}

	GameBoard(const Point3D& pos, const Dimension3D& dim) : Object(pos), _dimensions(dim) {
		cout << "Called GameBoard member variable setting constructor. Values: {"
			<< _dimensions._xWidth << ", " << _dimensions._yWidth << ", " << _dimensions._zHeight << "}" << endl;
	}

	~GameBoard() {
		cout << "Called GameBoard destructor." << endl;
	}

private:
	Dimension3D _dimensions;
};


int main()
{
	{Object tree;}
	cout << endl;
	{Object tree2({ 5.3f, 98.25f, 65.335f });}
	cout << endl;
	{GameBoard board; }	
	cout << endl;
	{GameBoard board2({ 0.0f, 5.0f, 2.0f }, { 50.0f, 40.0f, 4.0f });}

	return 0;
}