//	You can generate documentation from this file with using Doxygen
/**
 *	@file		Airground.cpp
 *
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-05-25/2017-06-21
 */

/**
 *	@fn			Aircraft::Aircraft(double x, double y, double z)
 *	@brief		Initialize aircraft's speed and position
 *
 *	@param x	Aircraft's starting position of x axis
 *	@param y	Aircraft's starting position of y axis
 *	@param z	Aircraft's starting position of z axis
 */
/**
 *	@fn			void Aircraft::modeling(float scale)
 *	@brief		Model a aircraft that my mock-up of F-117
 *
 *	@param scale	Scale to multiply value by vertices
 */
/**
 *	@fn			void move(void)
 *	@brief		Update continuously aircraft's position according to vectors
 */
/**
 *	@fn			void Aircraft::yaw(double angle)
 *	@brief		Rotation of yaw
 *
 *	@param angle	Rotation angle
 */
/**
 *	@fn			void Aircraft::roll(double angle)
 *	@brief		Rotation of roll
 *
 *	@param angle	Rotation angle
 */
/**
 *	@fn			void Aircraft::pitch(double angle)
 *	@brief		Rotation of pitch
 *
 *	@param angle	Rotation angle
 */
/**
 *	@fn			void Aircraft::showState(void)
 *	@brief		Print current state of aircraft to console
 */
/**
 *	@fn			Ground::Ground(int _lines, float _space)
 *	@brief		Initialize field size
 *
 *	@param _lines	Each number of row and collumn
 *	@param	_space	Space between lines
 */
/**
 *	@fn			void create(bool floor)
 *	@brief		Model a ground
 *
 *	@param floor	Decide to create floor
 */
/**
 *	@fn			void cloud(void)
 *	@brief		Model a cloud that is copy of ground
 */

#include <iostream>
#include <GL/glut.h>
#include "Airground.h"

Aircraft::Aircraft(double x, double y, double z) : Position(x, y, z)
{
	accel = Vector(0, 0, -1);
	vertical = Vector(0, 1, 0);
	horizontal = Vector(1, 0, 0);
	speed = 0.0F;
}

void Aircraft::modeling(float scale)
{
	// Up Floor
	glColor3f(0.3F, 0.3F, 0.3F);
	glBegin(GL_POLYGON);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);	// Front Point
		glVertex3f( 0.9F * scale, 0.05F * scale, -1.9F * scale);
		glVertex3f( 0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f( 0.8F * scale, 0.05F * scale, -2.1F * scale);
		glVertex3f( 0.3F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.3F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f( 0.0F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
	glEnd();
	glColor3f(0.24F, 0.24F, 0.24F);
	glBegin(GL_POLYGON);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);	// Front Point
		glVertex3f( 0.0F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
		glVertex3f(-0.3F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f(-0.3F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f(-0.8F * scale, 0.05F * scale, -2.1F * scale);
		glVertex3f(-0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.9F * scale, 0.05F * scale, -1.9F * scale);
	glEnd();

	// Middle Floor
	glColor3f(0.2F, 0.2F, 0.2F);
	glBegin(GL_QUADS);
		glVertex3f(-0.9F * scale, 0.05F * scale, -1.9F * scale);
		glVertex3f(-0.9F * scale, 0.00F * scale, -1.9F * scale);
		glVertex3f( 0.0F * scale, 0.00F * scale,  0.0F * scale);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);

		glVertex3f(-0.9F * scale, 0.00F * scale, -1.9F * scale);
		glVertex3f(-0.9F * scale, 0.05F * scale, -1.9F * scale);
		glVertex3f(-0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.9F * scale, 0.00F * scale, -2.0F * scale);

		glVertex3f(-0.9F * scale, 0.00F * scale, -2.0F * scale);
		glVertex3f(-0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.8F * scale, 0.05F * scale, -2.1F * scale);
		glVertex3f(-0.8F * scale, 0.00F * scale, -2.1F * scale);

		glVertex3f(-0.8F * scale, 0.00F * scale, -2.1F * scale);
		glVertex3f(-0.8F * scale, 0.05F * scale, -2.1F * scale);
		glVertex3f(-0.3F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f(-0.3F * scale, 0.00F * scale, -1.7F * scale);

		glVertex3f(-0.3F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f(-0.3F * scale, 0.00F * scale, -1.8F * scale);
		glVertex3f(-0.3F * scale, 0.00F * scale, -1.7F * scale);
		glVertex3f(-0.3F * scale, 0.05F * scale, -1.7F * scale);

		glVertex3f(-0.3F * scale, 0.00F * scale, -1.8F * scale);
		glVertex3f(-0.3F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f( 0.0F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
		glVertex3f( 0.0F * scale, 0.00F * scale, -2.0F * scale);


		glVertex3f( 0.0F * scale, 0.00F * scale, -2.0F * scale);
		glVertex3f( 0.0F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
		glVertex3f( 0.3F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f( 0.3F * scale, 0.00F * scale, -1.8F * scale);

		glVertex3f( 0.3F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.3F * scale, 0.00F * scale, -1.7F * scale);
		glVertex3f( 0.3F * scale, 0.00F * scale, -1.8F * scale);
		glVertex3f( 0.3F * scale, 0.05F * scale, -1.8F * scale);

		glVertex3f( 0.3F * scale, 0.00F * scale, -1.7F * scale);
		glVertex3f( 0.3F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.8F * scale, 0.05F * scale, -2.1F * scale);
		glVertex3f( 0.8F * scale, 0.00F * scale, -2.1F * scale);

		glVertex3f( 0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f( 0.9F * scale, 0.00F * scale, -2.0F * scale);
		glVertex3f( 0.8F * scale, 0.00F * scale, -2.1F * scale);
		glVertex3f( 0.8F * scale, 0.05F * scale, -2.1F * scale);

		glVertex3f( 0.9F * scale, 0.00F * scale, -2.0F * scale);
		glVertex3f( 0.9F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f( 0.9F * scale, 0.05F * scale, -1.9F * scale);
		glVertex3f( 0.9F * scale, 0.00F * scale, -1.9F * scale);

		glVertex3f( 0.9F * scale, 0.00F * scale, -1.9F * scale);
		glVertex3f( 0.9F * scale, 0.05F * scale, -1.9F * scale);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);
		glVertex3f( 0.0F * scale, 0.00F * scale,  0.0F * scale);
	glEnd();
	
	// Down Floor
	glColor3f(0.1F, 0.1F, 0.1F);
	glBegin(GL_POLYGON);
		glVertex3f( 0.0F * scale, 0.0F * scale,  0.0F * scale);	// Front Point
		glVertex3f(-0.9F * scale, 0.0F * scale, -1.9F * scale);
		glVertex3f(-0.9F * scale, 0.0F * scale, -2.0F * scale);
		glVertex3f(-0.8F * scale, 0.0F * scale, -2.1F * scale);
		glVertex3f(-0.3F * scale, 0.0F * scale, -1.7F * scale);
		glVertex3f(-0.3F * scale, 0.0F * scale, -1.8F * scale);
		glVertex3f( 0.0F * scale, 0.0F * scale, -2.0F * scale);	// Rear Point
		glVertex3f( 0.3F * scale, 0.0F * scale, -1.8F * scale);
		glVertex3f( 0.3F * scale, 0.0F * scale, -1.7F * scale);
		glVertex3f( 0.8F * scale, 0.0F * scale, -2.1F * scale);
		glVertex3f( 0.9F * scale, 0.0F * scale, -2.0F * scale);
		glVertex3f( 0.9F * scale, 0.0F * scale, -1.9F * scale);
	glEnd();

	
	// 정면 앞
	glBegin(GL_TRIANGLES);
		glColor3f(1.0F, 0.0F, 0.0F);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);	// Front Point
		glVertex3f( 0.1F * scale, 0.05F * scale, -0.2F * scale);
		glVertex3f( 0.0F * scale, 0.20F * scale, -0.3F * scale);	// C 1

		glColor3f(0.8F, 0.0F, 0.0F);
		glVertex3f( 0.0F * scale, 0.05F * scale,  0.0F * scale);	// Front Point
		glVertex3f( 0.0F * scale, 0.20F * scale, -0.3F * scale);	// C 1
		glVertex3f(-0.1F * scale, 0.05F * scale, -0.2F * scale);
	glEnd();

	// 정면 상단
	glColor3f(0.8F, 0.0F, 0.0F);
	glBegin(GL_QUADS);
		glVertex3f( 0.0F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f(-0.1F * scale, 0.05F * scale, -0.20F * scale);	// R 1
		glVertex3f( 0.0F * scale, 0.20F * scale, -0.30F * scale);	// C 1
		glVertex3f( 0.1F * scale, 0.05F * scale, -0.20F * scale);	// L 1
	glEnd();

	// 정면 옆
	glBegin(GL_TRIANGLES);
		glColor3f(1.0F, 0.0F, 0.0F);
		glVertex3f( 0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f( 0.10F * scale, 0.05F * scale, -0.20F * scale);	// L 1
		glVertex3f( 0.14F * scale, 0.05F * scale, -0.35F * scale);

		glColor3f(0.6F, 0.0F, 0.0F);
		glVertex3f( 0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f(-0.14F * scale, 0.05F * scale, -0.35F * scale);
		glVertex3f(-0.10F * scale, 0.05F * scale, -0.20F * scale);	// R 1
	glEnd();


	// 기체 좌현
	glBegin(GL_QUADS);
		// 날개쪽 정면
		glColor3f(0.0F, 0.4F, 0.0F);
		glVertex3f(0.33F * scale, 0.05F * scale, -0.80F * scale);	// L 2-3
		glVertex3f(0.28F * scale, 0.21F * scale, -0.85F * scale);	// L 2-2
		glVertex3f(0.15F * scale, 0.20F * scale, -0.75F * scale);	// L 2-1
		glVertex3f(0.18F * scale, 0.05F * scale, -0.70F * scale);

		// 날개쪽 측면 1
		glColor3f(0.0F, 1.0F, 0.0F);
		glVertex3f(0.28F * scale, 0.21F * scale, -0.85F * scale);	// L 2-2
		glVertex3f(0.33F * scale, 0.05F * scale, -0.80F * scale);	// L 2-3
		glVertex3f(0.42F * scale, 0.05F * scale, -1.20F * scale);
		glVertex3f(0.28F * scale, 0.25F * scale, -1.40F * scale);	// L 3

		// 기체 상판 후미
		glColor3f(0.0F, 0.8F, 0.8F);
		glVertex3f(0.00F * scale, 0.30F * scale, -1.5F * scale);	// C 2
		glVertex3f(0.28F * scale, 0.25F * scale, -1.4F * scale);	// L 3
		glVertex3f(0.30F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f(0.00F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
	glEnd();
	glBegin(GL_TRIANGLES);
		// 날개쪽 상판
		glColor3f(0.0F, 0.8F, 0.0F);
		glVertex3f(0.28F * scale, 0.25F * scale, -1.40F * scale);	// L 3
		glVertex3f(0.15F * scale, 0.20F * scale, -0.75F * scale);	// L 2-1
		glVertex3f(0.28F * scale, 0.21F * scale, -0.85F * scale);	// L 2-2

		// 날개쪽 측면 2
		glColor3f(0.0F, 0.9F, 0.0F);
		glVertex3f(0.28F * scale, 0.25F * scale, -1.4F * scale);	// L 3
		glVertex3f(0.42F * scale, 0.05F * scale, -1.2F * scale);
		glVertex3f(0.28F * scale, 0.05F * scale, -1.8F * scale);

		// 기체 상판 중앙
		glColor3f(0.0F, 1.0F, 0.8F);
		glVertex3f(0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f(0.28F * scale, 0.25F * scale, -1.40F * scale);	// L 3
		glVertex3f(0.00F * scale, 0.30F * scale, -1.50F * scale);	// C 2
	glEnd();

	// 옆면
	glBegin(GL_POLYGON);
		glColor3f(0.9F, 0.9F, 0.0F);
		glVertex3f(0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f(0.14F * scale, 0.05F * scale, -0.35F * scale);
		glVertex3f(0.18F * scale, 0.05F * scale, -0.70F * scale);
		glVertex3f(0.15F * scale, 0.20F * scale, -0.75F * scale);	// L 2-1
		glVertex3f(0.28F * scale, 0.25F * scale, -1.40F * scale);	// L 3
	glEnd();


	// 기체 우현
	glBegin(GL_QUADS);
		// 날개쪽 정면
		glColor3f(0.0F, 0.2F, 0.0F);
		glVertex3f(-0.18F * scale, 0.05F * scale, -0.70F * scale);
		glVertex3f(-0.15F * scale, 0.20F * scale, -0.75F * scale);	// R 2-1
		glVertex3f(-0.28F * scale, 0.21F * scale, -0.85F * scale);	// R 2-2
		glVertex3f(-0.33F * scale, 0.05F * scale, -0.80F * scale);	// R 2-3

		// 날개쪽 측면 1
		glColor3f(0.0F, 0.6F, 0.0F);
		glVertex3f(-0.33F * scale, 0.05F * scale, -0.80F * scale);	// R 2-3
		glVertex3f(-0.28F * scale, 0.21F * scale, -0.85F * scale);	// R 2-2
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.40F * scale);	// R 3
		glVertex3f(-0.42F * scale, 0.05F * scale, -1.20F * scale);

		// 기체 상판 후미
		glColor3f(0.0F, 0.6F, 0.6F);
		glVertex3f(-0.00F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point
		glVertex3f(-0.30F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.4F * scale);	// R 3
		glVertex3f(-0.00F * scale, 0.30F * scale, -1.5F * scale);	// C 2
	glEnd();
	glBegin(GL_TRIANGLES);
		// 날개쪽 상판
		glColor3f(0.0F, 0.4F, 0.0F);
		glVertex3f(-0.28F * scale, 0.21F * scale, -0.85F * scale);	// R 2-2
		glVertex3f(-0.15F * scale, 0.20F * scale, -0.75F * scale);	// R 2-1
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.40F * scale);	// R 3

		// 날개쪽 측면 2
		glColor3f(0.0F, 0.5F, 0.0F);
		glVertex3f(-0.28F * scale, 0.05F * scale, -1.8F * scale);
		glVertex3f(-0.42F * scale, 0.05F * scale, -1.2F * scale);
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.4F * scale);	// R 3

		// 기체 상판 중앙
		glColor3f(0.0F, 0.8F, 0.6F);
		glVertex3f(-0.00F * scale, 0.30F * scale, -1.50F * scale);	// C 2
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.40F * scale);	// R 3
		glVertex3f(-0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
	glEnd();

	// 옆면
	glBegin(GL_POLYGON);
		glColor3f(0.7F, 0.7F, 0.0F);
		glVertex3f(-0.00F * scale, 0.40F * scale, -0.65F * scale);	// Top Point
		glVertex3f(-0.28F * scale, 0.25F * scale, -1.40F * scale);	// R 3
		glVertex3f(-0.15F * scale, 0.20F * scale, -0.75F * scale);	// R 2-1
		glVertex3f(-0.18F * scale, 0.05F * scale, -0.70F * scale);
		glVertex3f(-0.14F * scale, 0.05F * scale, -0.35F * scale);
	glEnd();


	// 꼬리
	glBegin(GL_QUADS);
		// 좌현쪽
		glColor3f(0.0F, 0.0F, 1.0F);
		glVertex3f( 0.22F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f( 0.22F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f( 0.02F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.02F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point

		glColor3f(0.0F, 0.0F, 0.8F);
		glVertex3f( 0.00F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f( 0.00F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.20F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f( 0.20F * scale, 0.40F * scale, -2.4F * scale);

		glColor3f(0.0F, 0.0F, 1.0F);
		glVertex3f( 0.00F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.02F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f( 0.22F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f( 0.20F * scale, 0.40F * scale, -2.2F * scale);

		glVertex3f( 0.22F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f( 0.20F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f( 0.20F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f( 0.22F * scale, 0.40F * scale, -2.2F * scale);

		glVertex3f( 0.20F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f( 0.22F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f( 0.02F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f( 0.00F * scale, 0.05F * scale, -2.0F * scale);

		// 우현쪽
		glColor3f(0.0F, 0.0F, 0.8F);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.00F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f(-0.00F * scale, 0.05F * scale, -2.0F * scale);	// Rear Point

		glColor3f(0.0F, 0.0F, 0.6F);
		glVertex3f(-0.02F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.02F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f(-0.22F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.22F * scale, 0.40F * scale, -2.4F * scale);

		glColor3f(0.0F, 0.0F, 0.8F);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.22F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.02F * scale, 0.05F * scale, -1.7F * scale);
		glVertex3f(-0.00F * scale, 0.05F * scale, -1.7F * scale);

		glVertex3f(-0.22F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.2F * scale);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f(-0.22F * scale, 0.40F * scale, -2.4F * scale);

		glVertex3f(-0.00F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.02F * scale, 0.05F * scale, -2.0F * scale);
		glVertex3f(-0.22F * scale, 0.40F * scale, -2.4F * scale);
		glVertex3f(-0.20F * scale, 0.40F * scale, -2.4F * scale);
	glEnd();
}

void Aircraft::move(void)
{
	x += accel.i * speed;
	y += accel.j * speed;
	z += accel.k * speed;
}

void Aircraft::yaw(double angle)
{
	horizontal = unit(horizontal * cos(angle) + accel * sin(angle));

	accel.i = (vertical.j * horizontal.k) - (vertical.k * horizontal.j);
	accel.j = (vertical.k * horizontal.i) - (vertical.i * horizontal.k);
	accel.k = (vertical.i * horizontal.j) - (vertical.j * horizontal.i);
}

void Aircraft::roll(double angle)
{
	horizontal = unit(horizontal * cos(angle) + vertical * sin(angle));

	vertical.i = (horizontal.j * accel.k) - (horizontal.k * accel.j);
	vertical.j = (horizontal.k * accel.i) - (horizontal.i * accel.k);
	vertical.k = (horizontal.i * accel.j) - (horizontal.j * accel.i);
}

void Aircraft::pitch(double angle)
{
	accel = unit(accel * cos(angle) + vertical * sin(angle));

	vertical.i = (horizontal.j * accel.k) - (horizontal.k * accel.j);
	vertical.j = (horizontal.k * accel.i) - (horizontal.i * accel.k);
	vertical.k = (horizontal.i * accel.j) - (horizontal.j * accel.i);
}

void Aircraft::showState(void)
{
	printf("POSITION  : %5.2f, %5.2f, % .2f\n", x, y, z);
	printf("ACCEL     : %5.2f, %5.2f, %5.2f\n"
		, getVector(ACCEL(I))
		, getVector(ACCEL(J))
		, getVector(ACCEL(K))
	);
	printf("VERTICAL  : %5.2f, %5.2f, %5.2f\n"
		, getVector(VERTICAL(I))
		, getVector(VERTICAL(J))
		, getVector(VERTICAL(K))
	);
	printf("HORIZONTAL: %5.2f, %5.2f, %5.2f\n"
		, getVector(HORIZONTAL(I))
		, getVector(HORIZONTAL(J))
		, getVector(HORIZONTAL(K))
	);
	std::cout << '\n';
}


Ground::Ground(int _lines, float _space)
:	lines(_lines)
,	space(_space)
,	distance(_lines * _space / 2) {}

void Ground::create(bool floor)
{
	glColor3f(0.8F, 0.8F, 0.8F);
	glBegin(GL_LINES);
	for (GLfloat i = -distance; i <= distance; i += space) {
		glVertex3f(-distance, 0.0F, i);
		glVertex3f( distance, 0.0F, i);
		glVertex3f(i, 0.0F, -distance);
		glVertex3f(i, 0.0F,  distance);
	}
	glEnd();

	if (floor) {
		glColor3f(0.1F, 0.1F, 0.1F);
		glBegin(GL_QUADS);
			glVertex3f( distance, -0.05F, -distance);
			glVertex3f(-distance, -0.05F, -distance);
			glVertex3f(-distance, -0.05F,  distance);
			glVertex3f( distance, -0.05F,  distance);
		glEnd();
	}
}

void Ground::cloud(void)
{
	glColor3f(0.8F, 0.8F, 1.0F);
	glBegin(GL_QUADS);
		glVertex3f( distance, 300.0F, -distance);
		glVertex3f(-distance, 300.0F, -distance);
		glVertex3f(-distance, 300.0F,  distance);
		glVertex3f( distance, 300.0F,  distance);
		
		glVertex3f( distance, 300.0F,  distance);
		glVertex3f(-distance, 300.0F,  distance);
		glVertex3f(-distance, 300.0F, -distance);
		glVertex3f( distance, 300.0F, -distance);
	glEnd();
}