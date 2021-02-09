/*Vector3f.h
Nathan Damon
CS 202
2/9/2021
This is the header file for the Vector3f class
*/

#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& orig);

	float x;
	float y;
	float z;

};



#endif
