//	You can generate documentation from this file with using Doxygen
/**
 *	@file		Geometry.h
 *
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-05-25/2017-06-21
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>

enum class VECTOR : int
{
	ACCEL = 1, VERTICAL, HORIZONTAL,
	I = 1, J, K
};

#define ACCEL(v)		static_cast<int>(VECTOR::ACCEL), static_cast<int>(VECTOR::##v)
#define VERTICAL(v)		static_cast<int>(VECTOR::VERTICAL), static_cast<int>(VECTOR::##v)
#define HORIZONTAL(v)	static_cast<int>(VECTOR::HORIZONTAL), static_cast<int>(VECTOR::##v)

/// A class that contains 3D coordinate values
class Position
{
public:
	double x;	///< Value on X axis
	double y;	///< Value on Y axis
	double z;	///< Value on Z axis
public:
	/// Initialize coordinates values
	Position(double _x = 0.0, double _y = 0.0, double _z = 0.0)
	: x(_x)
	, y(_y)
	, z(_z) {}
};

/// A class that contains 3D vector values
class Vector
{
public:
	double i;	///< Front or back
	double j;	///< Left or right
	double k;	///< Up or down
public:
	/// Initialize vector values
	Vector(double _i = 0.0, double _j = 0.0, double _k = 0.0)
	: i(_i)
	, j(_j)
	, k(_k) {}

	/// Return one of vector value according to argument
	double getValue(int value)
	{
		switch (value) {
		case static_cast<int>(VECTOR::I) :
			return i;
		case static_cast<int>(VECTOR::J) :
			return j;
		case static_cast<int>(VECTOR::K) :
			return k;
		default:
			return 0;
		}
	}

	/// Set vector value
	void setValue(int var, double value)
	{
		switch (var) {
		case static_cast<int>(VECTOR::I) :
			i = value;
			break;
		case static_cast<int>(VECTOR::J) :
			j = value;
			break;
		case static_cast<int>(VECTOR::K) :
			k = value;
			break;
		}
	}

	Vector operator+(Vector& v) { return Vector(i + v.i, j + v.j, k + v.k); }
	Vector operator*(double n) { return Vector(i * n, j * n, k * n); }
	Vector operator/(double n) { return Vector(i / n, j / n, k / n); }

	double factor(Vector v) { return i * v.i + j * v.j + k * v.k; }	///< Multiply each value of two vectors
	double length(void) { return sqrt(this->factor(*this)); }	///< Length of vector
	friend Vector unit(Vector& v) { return v / v.length(); }	///< Maintain maximum value of vector to be 1
};

#endif /* __GEOMETRY_H__ */