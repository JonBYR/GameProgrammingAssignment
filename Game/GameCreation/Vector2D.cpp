#include "Vector2D.h"
Vector2D::Vector2D() {}
Vector2D::Vector2D(double xVal, double yVal) 
{
	x = xVal;
	y = yVal;
}
double Vector2D::getX() 
{
	return x;
}
double Vector2D::getY()
{
	return y;
}
void Vector2D::setX(double val) 
{
	x = val;
}
void Vector2D::setY(double val)
{
	y = val;
}
double Vector2D::length() 
{
	double xSqr = pow(x, 2);
	double ySqr = pow(y, 2);
	return sqrt(xSqr + ySqr);
}

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D((vec1.x + vec2.x), (vec1.y, vec2.y));
}

Vector2D operator+=(Vector2D& vec1, const Vector2D& vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	return vec1;
}

Vector2D operator*(const Vector2D& vec, double scalar)
{
	return Vector2D((vec.x * scalar), (vec.y * scalar));
}

Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2)
{
	return Vector2D((vec1.x - vec2.x), (vec1.y -  vec2.y));
}
Vector2D& Vector2D::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}
Vector2D& Vector2D::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}
void Vector2D::normalize() 
{
	double l = length();
	if (l > 0) 
	{
		(*this) *= 1 / l;
	}
}
