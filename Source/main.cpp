//	You can generate documentation from this file with using Doxygen
/**
 *	@file		main.cpp
 *	@brief		OpenGL 3D Flight Simulator
 *
 *	@author		Dong-Young Kim <31337.cert@gmail.com>
 *	@date		2017-05-17/2017-06-21
 *	@version	0.2.5
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include <Windows.h>
#include <GL/glut.h>
#include "Airground.h"


/* Constants */

constexpr bool DBUF = true;		///< Use Double Buffer

constexpr int WINDOW_X = 1280;	///< OpenGL Window Width Resolution
constexpr int WINDOW_Y = 720;	///< OpenGL Window Height Resolution
const int SYSTEM_X = GetSystemMetrics(SM_CXSCREEN);	///< System Width Resolution
const int SYSTEM_Y = GetSystemMetrics(SM_CYSCREEN);	///< System Height Resolution

constexpr GLdouble WINDOW_RANGE = 2.0;	///< OpenGL Window Range
constexpr float	MOUSE_SCALE = 0.1F;	///< Rotation Scale

/// Enumerated value for MenuAction()
enum class MENU : int
{
	END, RESTART, VIEWPOINT, LIGHT, SHAPE
};


/* Variables */

Aircraft air(0, 10, 100);	// X, Y, Z Position
Aircraft air_init(0, 10, 100);	// Backup Data of Aircraft's First Position
Ground ground(100);	// Lines, Space

bool pause = false;	///< Display Pause Flag
bool end = false;	///< Display Stop Flag
bool rotating = false;	///< Rotating state
bool light = false;
bool shape = true;

int mouse_x = 0;	///< X-axis Position of Mouse
int mouse_y = 0;	///< Y-axis Position of Mouse

GLfloat view_rotx = 0.0F;	///< View angle of x-axis
GLfloat view_roty = 0.0F;	///< View angle of y-axis

GLsizei view_width = WINDOW_X;
GLsizei view_height = WINDOW_Y;

enum class ViewPoint : int {
	ORTHO, PERPECTIVE
};
ViewPoint view_point = ViewPoint::ORTHO;


/* Functions */

void Reshape(int width, int height); ///< Reshape Function for glutReshapeFunc()
void Display(void);	///< Display Function for glutDisplayFunc()

void Keyboard(unsigned char key, int x, int y);	///< Keyboard Function for glutKeyboardFunc()

void MouseClick(int button, int state, int x, int y);	///< Mouse Click Function for glutMouseFunc()
void MouseMotion(int x, int y);	///< Mouse Motion Function for glutMotionFunc()

void UpdateDisplay(void);	///< Process in Idle State for glutIdleFunc()

void MenuAction(int value);	///< Interaction of Menu for glutCreateMenu()
void MenuCreate(void);	///< Create Menu for glutCreateMenu()

/// Initialize Display
void InitDisplay(void)
{
	glFrontFace(GL_CCW);
	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// 선 부드럽게
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5F);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void InitLight(void)
{
	GLfloat Light0_Ambient[] = { 0.6F, 0.6F, 0.6F, 1.0F };
	GLfloat Light0_Diffuse[] = { 0.8F, 0.8F, 0.8F, 1.0F };
	GLfloat Light0_Position[] = { 0.0F, 1.0F, 1.0F, 1.0F };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);
}

void PrintText(GLdouble x, GLdouble y, GLdouble z, const std::string &string) {
	glColor3f(1.0F, 1.0F, 1.0F);
	glRasterPos3d(x, y, z);
	for (int i = 0; i < static_cast<int>(string.size()); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

/// main()
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | (DBUF ? GLUT_DOUBLE : GLUT_SINGLE));
	glutInitWindowSize(WINDOW_X, WINDOW_Y);
	glutInitWindowPosition((SYSTEM_X - WINDOW_X) / 2, (SYSTEM_Y - WINDOW_Y) / 2);
	glutCreateWindow("3D Flight Simulator");

	InitDisplay();
	InitLight();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);

	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);

	glutKeyboardFunc(Keyboard);
	glutIdleFunc(UpdateDisplay);

	MenuCreate();

	glutMainLoop();
	return 0;
}


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (view_point == ViewPoint::ORTHO) {
		if (width <= height) {
			glOrtho(-WINDOW_RANGE, WINDOW_RANGE
					, -WINDOW_RANGE * height / width, WINDOW_RANGE * height / width
					, -WINDOW_RANGE * 2, WINDOW_RANGE * 2
			);
		} else {
			glOrtho(-WINDOW_RANGE * width / height, WINDOW_RANGE * width / height
					, -WINDOW_RANGE, WINDOW_RANGE
					, -WINDOW_RANGE * 2, WINDOW_RANGE * 2
			);
		}
	}
	if (view_point == ViewPoint::PERPECTIVE) {
		gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 0.1, 400.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (view_point == ViewPoint::ORTHO) {
		glLoadIdentity();
		glClearColor(0.9F, 0.9F, 0.9F, 1.0F);

		glRotatef(-view_roty, 1.0F, 0.0F, 0.0F);
		glRotatef(-view_rotx, 0.0F, 1.0F, 0.0F);

		if (light) {
			glEnable(GL_LIGHTING);
		} else {
			glDisable(GL_LIGHTING);
		}

		air.modeling();
	}
	if (view_point == ViewPoint::PERPECTIVE) {
		/*
			시뮬레이터의 현재 진행 상태에 따라 배경색 변경
			중지: #FFFFFF | 일시 정지: #CCCCCC | 재생: #999999
		*/
		if (end) {
			glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
		} else if (pause) {
			glClearColor(0.8F, 0.8F, 0.8F, 0.8F);
			PrintText(air.x + (air.getVector(ACCEL(I)) * 20) - 0.5
					, air.y + (air.getVector(ACCEL(J)) * 20)
					, air.z + (air.getVector(ACCEL(K)) * 20)
					, "PAUSE"
			);
		} else {
			glClearColor(0.6F, 0.6F, 1.0F, 1.0F);
		}

		/*
			중지 상태가 아닌 경우
			즉, 재생과 일시 정지 상태일 때
			모델링 진행
		*/
		if (!end) {
			ground.create(shape);
			if (shape)
				ground.cloud();
		}
	}

	DBUF ? glutSwapBuffers() : glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	const double angle = 0.02;	// Rotation Angle

	if (view_point == ViewPoint::PERPECTIVE) {
		switch (key) {
		case 'w':
			air.pitch(-angle);
			break;
		case 's':
			air.pitch(angle);
			break;
		case 'a':
			air.roll(angle);
			break;
		case 'd':
			air.roll(-angle);
			break;
		case 'q':
			air.yaw(angle);
			break;
		case 'e':
			air.yaw(-angle);
			break;
		case '8':
			air.setSpeed(air.getSpeed() + 0.10F);
		case '2':
			air.setSpeed(air.getSpeed() - 0.05F);
			printf("Current Speed: %.2f\n", air.getSpeed());
			// 속도가 0 밑으로 떨어질 때 0으로 고정 (후진 불가)
			if (air.getSpeed() < 0.0)
				air.setSpeed(0.0F);
			break;
		}
	}
}

void MouseClick(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;

	switch (button) {
	case GLUT_LEFT_BUTTON:
		rotating = (state == GLUT_DOWN);
		break;
	case GLUT_MIDDLE_BUTTON:
		if(state == GLUT_DOWN)
			pause = !pause;
		break;
	}
}
void MouseMotion(int x, int y) {
	if (rotating && (view_point == ViewPoint::ORTHO)) {
		view_rotx += MOUSE_SCALE * (x - mouse_x);
		view_roty += MOUSE_SCALE * (y - mouse_y);

		#ifdef _DEBUG
			printf("X: %f\n", view_rotx);
			printf("Y: %f\n", view_roty);
			std::cout << std::endl;
		#endif /* _DEBUG */

		if (view_rotx >= 360.0F) {
			view_rotx -= 360.0F;
		} else if (view_rotx <= -360.0F) {
			view_rotx += 360.0F;
		}

		if (view_roty >= 360.0F) {
			view_roty -= 360.0F;
		} else if (view_roty <= -360.0F) {
			view_roty += 360.0F;
		}

		mouse_x = x;
		mouse_y = y;

		glutPostRedisplay();
	}
}

void UpdateDisplay(void)
{
	if(view_point == ViewPoint::PERPECTIVE) {
		// 정지 : 비행
		if (pause | end) {
			PlaySound(NULL, 0, 0);
		} else {
			air.move();
			// 기체가 비행 중일 때 소리 재생, 비행 중 속도가 0으로 떨어지면(기체가 멈추면) 재생 중이던 사운드 중지
			if (air.getSpeed() > 0.0F) {
				//PlaySound(TEXT(".\\Sound\\Avion.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
			} else {
				PlaySound(NULL, 0, 0);
			}
		}
		glLoadIdentity();

		// 기체가 바닥에 닿았을 때 (착륙)
		if (air.y < 10) {
			air.y = 10;
		}

		// 충돌
		if (abs(air.x) >= static_cast<double>(ground.getDistance())
			|| abs(air.z) >= static_cast<double>(ground.getDistance())) {
			end = true;
		} else {
			#ifdef _DEBUG
				air.showState();
			#endif /* _DEBUG */
		}
		
		Position way(air.x + air.getVector(ACCEL(I))
					, air.y + air.getVector(ACCEL(J))
					, air.z + air.getVector(ACCEL(K))
		);
		gluLookAt(	air.x, air.y, air.z,
					way.x, way.y, way.z,
					air.getVector(VERTICAL(I)), air.getVector(VERTICAL(J)), air.getVector(VERTICAL(K))
		);
	}

	glutPostRedisplay();
}

void MenuAction(int value)
{
	int button;
	switch (value) {
	case static_cast<int>(MENU::END) :
		button = MessageBox(NULL, TEXT("Exit Program"), TEXT("Exit"), MB_OKCANCEL | MB_ICONINFORMATION);
		if (button == IDOK)
			exit(0);
		break;

	case static_cast<int>(MENU::RESTART) :
		air = air_init;
		air.setSpeed(0.0);
		end = pause = false;
		break;

	case static_cast<int>(MENU::VIEWPOINT) :
		if (view_point == ViewPoint::ORTHO) {
			view_point = ViewPoint::PERPECTIVE;
			glDisable(GL_LIGHTING);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();

			gluPerspective(60.0, static_cast<GLdouble>(view_width / view_height), 0.01, 400.0);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
		} else {
			view_point = ViewPoint::ORTHO;

			glPopMatrix();
			glMatrixMode(GL_PROJECTION);

			if (view_width <= view_height) {
				glOrtho(-WINDOW_RANGE, WINDOW_RANGE
						, -WINDOW_RANGE * view_height / view_width, WINDOW_RANGE * view_height / view_width
						, -WINDOW_RANGE * 2, WINDOW_RANGE * 2
				);
			} else {
				glOrtho(-WINDOW_RANGE * view_width / view_height, WINDOW_RANGE * view_width / view_height
						, -WINDOW_RANGE, WINDOW_RANGE
						, -WINDOW_RANGE * 2, WINDOW_RANGE * 2
				);
			}

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		break;

	case static_cast<int>(MENU::LIGHT) :
		light = !light;
		break;

	case static_cast<int>(MENU::SHAPE) :
		shape = !shape;
		break;
	}
}
void MenuCreate(void)
{
	int MenuID = glutCreateMenu(MenuAction);
	glutAddMenuEntry("Change ViewPoint", static_cast<int>(MENU::VIEWPOINT));
	glutAddMenuEntry("Light On / Off", static_cast<int>(MENU::LIGHT));
	glutAddMenuEntry("Solid / Wire", static_cast<int>(MENU::SHAPE));
	glutAddMenuEntry("Restart", static_cast<int>(MENU::RESTART));
	glutAddMenuEntry("Exit", static_cast<int>(MENU::END));

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}