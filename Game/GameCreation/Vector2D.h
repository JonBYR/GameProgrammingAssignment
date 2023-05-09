#pragma once
#include <math.h>
class Vector2D
{
public:
	Vector2D();
	Vector2D(double xVal, double yVal);
	double getX();
	double getY();
	void setX(double val);
	void setY(double val);
	double length();
	friend Vector2D operator +(const Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D operator +=(Vector2D& vec1, const Vector2D& vec2);
	friend Vector2D operator *(const Vector2D& vec, double scalar);
	friend Vector2D operator -(const Vector2D& vec1, const Vector2D& vec2);
	Vector2D& operator /=(double scalar);
	Vector2D& operator *=(double scalar);
	void normalize();
private:
	double x;
	double y;
};

