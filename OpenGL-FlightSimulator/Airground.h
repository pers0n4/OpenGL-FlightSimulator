//	You can generate documentation from this file with using Doxygen
/**
 *	@file		Airground.h
 *
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-05-25/2017-06-21
 */

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "Geometry.h"

/// A class that contains information of aircraft
class Aircraft : public Position
{
private:
	float speed;	///< Speed of aircraft
	Vector accel;	///< Vector of z axis
	Vector vertical;	///< Vector of y axis
	Vector horizontal;	///< Vector of x axis
public:
	/// Initialize aircraft's speed and position
	Aircraft(double x = 0.0, double y = 0.0, double z = 0.0);

	float getSpeed() { return speed; }	///< Return speed
	void setSpeed(float speed) { this->speed = speed; }	///< Set speed
	double getVector(int vector, int value)	///< Return one of vector value according to argument
	{
		switch (vector) {
		case static_cast<int>(VECTOR::ACCEL) :
			return accel.getValue(value);
		case static_cast<int>(VECTOR::VERTICAL) :
			return vertical.getValue(value);
		case static_cast<int>(VECTOR::HORIZONTAL) :
			return horizontal.getValue(value);
		default:
			return NULL;
		}
	}
	void setVector(int vector, int var, double value)	///< Set vector value
	{
		switch (vector) {
		case static_cast<int>(VECTOR::ACCEL) :
			accel.setValue(var, value);
		case static_cast<int>(VECTOR::VERTICAL) :
			vertical.setValue(var, value);
		case static_cast<int>(VECTOR::HORIZONTAL) :
			horizontal.setValue(var, value);
		}
	}

	void modeling(float scale = 1.0F);	///< Model a aircraft that my mock-up of F-117

	void move(void);	///< Update continuously aircraft's position according to vectors

	void yaw(double angle);	///< Rotation of yaw
	void roll(double angle);	///< Rotation of roll
	void pitch(double angle);	///< Rotation of pitch

	void showState(void);	///< Print current state of aircraft to console
};

/// A class that contains values of filed's width and height
class Ground
{
private:
	int lines;	///< Each number of row and collumn
	float space;	///< Space between lines
	float distance;	///< Half of total length
public:
	Ground(int _lines = 10, float _space = 10.0F);	///< Initialize field size
	float getDistance(void) { return distance; }	///< Return distance of field

	void create(bool floor = true);	///< Model a ground
	void cloud(void);	///< Model a cloud that is copy of ground
};

#endif /* __AIRCRAFT_H__ */