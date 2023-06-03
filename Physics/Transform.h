#pragma once
#include <string>
#include <iostream>

class Vector_2D
{
public:
	float X, Y;
	virtual ~Vector_2D() {};
	Vector_2D(float x = 0, float y = 0) :X(x), Y(y) {}

	inline Vector_2D operator+(const Vector_2D& v2) const {
		return Vector_2D(X + v2.X, Y + v2.Y);
	}

	inline Vector_2D operator-(const Vector_2D& v2) const {
		return Vector_2D(X - v2.X, Y - v2.Y);
	}

	inline Vector_2D operator*(const float& scalar) const {
		return Vector_2D(X * scalar, Y * scalar);
	}

	void Log(std::string msg = "")
	{
		std::cout << msg << " (X, Y) = (" << X << " " << Y << ")" << std::endl;
	}

private:
};



class Transform
{
public:
	float X, Y;

	void Log(std::string msg = "")
	{
		std::cout << msg << " (X, Y) = (" << X << " " << Y << ")" << std::endl;
	}

	Transform(float x = 0, float y = 0) :X(x), Y(y) {}
private:

	inline void TranslateX(float x) { X += x; }

	inline void TranslateY(float y) { Y += y; }

	inline void Translate(Vector_2D v) { X += v.X; Y += v.Y; }


};