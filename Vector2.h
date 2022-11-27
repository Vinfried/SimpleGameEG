#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	//Operators that will allow us to perporm math functions on the vector
	Vector2 operator+(const Vector2 &otherVector);
	Vector2 operator+=(const Vector2 &otherVector);

	Vector2 operator-(const Vector2 &otherVector);
	Vector2 operator-=(const Vector2 &otherVector);

	//vector multiplication not necessary. Instead multiply by a single number (scalar)
	Vector2 operator*(const float &scalar);
	Vector2 operator*=(const float &scalar);

	Vector2 operator/(const float &scalar);
	Vector2 operator/=(const float &scalar);

	bool operator==(const Vector2 &otherVector);
	bool operator!=(const Vector2 &otherVector);

	//what is the length of both x and y
	float length();

	void normalise();
	Vector2 normalised();

	//this is a quick function to return a 0 vector
	Vector2 zero();

	//Coordinates stored in the vector
	float x;
	float y;
};

