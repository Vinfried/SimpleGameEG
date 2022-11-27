#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{

}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;


}

Vector2::~Vector2()
{
}

//gives new Vector2
Vector2 Vector2::operator+(const Vector2& otherVector)
{
	return Vector2(this->x + otherVector.x, this->y + otherVector.y);
}

//increments on existing Vector2
Vector2 Vector2::operator+=(const Vector2& otherVector)
{
	//increase the x and y values by the other vectors values
	this->x += otherVector.x;
	this->y += otherVector.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& otherVector)
{
	return Vector2(this->x - otherVector.x, this->y - otherVector.y);
}


Vector2 Vector2::operator-=(const Vector2& otherVector)
{
	//decrement the x and y values by other vector values
	this->x -= otherVector.x;
	this->y -= otherVector.y;
	return *this;
}

Vector2 Vector2::operator*(const float& scalar)
{
	return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator*=(const float& scalar)
{
	//multiply the x and y values by the scalar value to multiply the vector uniformly
	this->x *= scalar;
	this->y *= scalar;

	return *this;
}

Vector2 Vector2::operator/(const float& scalar)
{
	Vector2 dividedVector = Vector2(this->x, this->y);

	//is the scalar 0
	if (scalar != 0) {
		
		//is the current x value 0
		if (this->x != 0) {
			dividedVector.x / scalar;	
		}

		//is the current y value 0
		if (this->y != 0) {
			dividedVector.y /= scalar;
		}
	}

	return dividedVector;
}

Vector2 Vector2::operator/=(const float& scalar)
{
	//is the scalar 0
	if (scalar != 0) {

		//is the current x value 0
		if (this->x != 0) {
			this->x / scalar;
		}

		//is the current y value 0
		if (this->y != 0) {
			this->y /= scalar;
		}
	}

	return *this;
}

bool Vector2::operator==(const Vector2& otherVector)
{
	bool matchX = this->x == otherVector.x;
	bool matchY = this->y == otherVector.y;
	
	//return true only of both matchX and matchy are true, otherwise return false
	return matchX && matchY;
}

bool Vector2::operator!=(const Vector2& otherVector)
{
	bool matchX = this->x != otherVector.x;
	bool matchY = this->y != otherVector.y;

	//return true only of both matchX and matchy are false, otherwise return true
	return matchX && matchY;
}

float Vector2::length()
{
	return sqrtf(x*x + y*y);
}

void Vector2::normalise()
{
	if (length() != 0) {
		this->x /= length();
		this->y /= length();
	}

	else {
		this->x = 0;
		this->y = 0;
	}
}

Vector2 Vector2::normalised()
{
	Vector2 result = Vector2(0, 0);

	if (length() != 0) {
		result.x = this->x / length();
		result.y = this->y / length();
	}

	return result;
}

Vector2 Vector2::zero()
{
	return Vector2(0, 0);
}
