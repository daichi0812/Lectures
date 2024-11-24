//
//  main.cpp
//
//  Created by Yonghao Yue on 2019/09/28.
//  Updated: 2021/10/06
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

/*
* デジタルメディア設計演習第2回課題
* 共同制作 森下剛・堀田大智・中江朋弘
* 解答は関数drawCG_1,drawCG_2内で作成
*/

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <unistd.h>
#else
#include <GL/freeglut.h>
#include <Windows.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera.h"

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

int width = 1000;
int height = 600;
int mx, my;

Camera g_Camera;

#define sides 999 //分割数指定

#define M_PI 3.141592653589 //円周率

// トーラスの作成
void drawCG_1() {
	double R = 1.5; // 0で球

	int M = 100;
	int S = 100;
	double radius4 = 0.4;

	const double angleS = 2 * M_PI / S;

	const double angleM = 2 * M_PI / M;

	for (int i = 0; i < M; i++) {

		for (int j = 0; j < S; j++) {

			glColor3f(cos((i + j) * angleM * 3.2 * M_PI), sin((i + j) * angleM * 7.8 * M_PI), -sin((i + j) * angleM * M_PI - (M_PI / 4)));

			glBegin(GL_TRIANGLES);

			double x1 = (R + radius4 * sin((i - 1) * angleS)) * cos(j * angleM);
			double y1 = radius4 * cos((i - 1) * angleS);
			double z1 = (R + radius4 * sin((i - 1) * angleS)) * sin(j * angleM);
			glVertex3f(x1, z1, y1);

			double x2 = (R + radius4 * sin(i * angleS)) * cos(j * angleM);
			double y2 = radius4 * cos(i * angleS);
			double z2 = (R + radius4 * sin(i * angleS)) * sin(j * angleM);
			glVertex3f(x2, z2, y2);

			double x3 = (R + radius4 * sin(i * angleS)) * cos((j + 1) * angleM);
			double y3 = radius4 * cos(i * angleS);
			double z3 = (R + radius4 * sin(i * angleS)) * sin((j + 1) * angleM);
			glVertex3f(x3, z3, y3);

			glEnd();


			glBegin(GL_TRIANGLES);

			double x11 = (R + radius4 * sin(i * angleS)) * cos(j * angleM);
			double y11 = radius4 * cos(i * angleS);
			double z11 = (R + radius4 * sin(i * angleS)) * sin(j * angleM);
			glVertex3f(x11, z11, y11);

			double x22 = (R + radius4 * sin(i * angleS)) * cos((j + 1) * angleM);
			double y22 = radius4 * cos(i * angleS);
			double z22 = (R + radius4 * sin(i * angleS)) * sin((j + 1) * angleM);
			glVertex3f(x22, z22, y22);

			double x33 = (R + radius4 * sin((i + 1) * angleS)) * cos((j + 1) * angleM);
			double y33 = radius4 * cos((i + 1) * angleS);
			double z33 = (R + radius4 * sin((i + 1) * angleS)) * sin((j + 1) * angleM);
			glVertex3f(x33, z33, y33);

			glEnd();


		}

	}
}

// トーラスの結び目の作成
void drawCG_2() {
	double R = 7;

	int M = 100;
	int S = 100;
	double radius4 = 0.4;

	const double angleS = 2 * M_PI / S;

	const double angleM = 2 * M_PI / M;

	for (int i = 0; i < M; i++) {

		for (int j = 0; j < S; j++) {

			glColor3f(-sin(angleS * i), sin(angleS * i), cos(angleS * i));

			glBegin(GL_TRIANGLES);

			double x1 = (R - cos((i - 1) * angleS) + sin(5 * j * angleM)) * cos(2 * j * angleM);
			double y1 = cos(5 * j * angleM) + sin((i - 1) * angleS);
			double z1 = (R - cos((i - 1) * angleS) + sin(5 * j * angleM)) * sin(2 * j * angleM);
			glVertex3f(x1, y1, z1);

			double x2 = (R - cos(i * angleS) + sin(5 * j * angleM)) * cos(2 * j * angleM);
			double y2 = cos(5 * j * angleM) + sin(i * angleS);
			double z2 = (R - cos(i * angleS) + sin(5 * j * angleM)) * sin(2 * j * angleM);
			glVertex3f(x2, y2, z2);

			double x3 = (R - cos(i * angleS) + sin(5 * (j + 1) * angleM)) * cos(2 * (j + 1) * angleM);
			double y3 = cos(5 * (j + 1) * angleM) + sin(i * angleS);
			double z3 = (R - cos(i * angleS) + sin(5 * (j + 1) * angleM)) * sin(2 * (j + 1) * angleM);
			glVertex3f(x3, y3, z3);

			glEnd();


			glBegin(GL_TRIANGLES);

			double x11 = (R - cos(i * angleS) + sin(5 * j * angleM)) * cos(2 * j * angleM);
			double y11 = cos(5 * j * angleM) + sin(i * angleS);
			double z11 = (R - cos(i * angleS) + sin(5 * j * angleM)) * sin(2 * j * angleM);
			glVertex3f(x11, y11, z11);

			double x22 = (R - cos(i * angleS) + sin(5 * (j + 1) * angleM)) * cos(2 * (j + 1) * angleM);
			double y22 = cos(5 * (j + 1) * angleM) + sin(i * angleS);
			double z22 = (R - cos(i * angleS) + sin(5 * (j + 1) * angleM)) * sin(2 * (j + 1) * angleM);
			glVertex3f(x22, y22, z22);

			double x33 = (R - cos((i + 1) * angleS) + sin(5 * (j + 1) * angleM)) * cos(2 * (j + 1) * angleM);
			double y33 = cos(5 * (j + 1) * angleM) + sin((i + 1) * angleS);
			double z33 = (R - cos((i + 1) * angleS) + sin(5 * (j + 1) * angleM)) * sin(2 * (j + 1) * angleM);
			glVertex3f(x33, y33, z33);

			glEnd();


		}

	}
}

void idle()
{
#ifdef __APPLE__
	usleep(1000.0 * 1000.0 / 60.0); // in microseconds
#else
	Sleep(1000.0 / 60.0); // in milliseconds
#endif
	glutPostRedisplay();
}

void projection_and_modelview(const Camera& in_Camera)
{
	const double fovy_deg = (2.0 * 180.0 / M_PI) * atan(0.024 * 0.5 / in_Camera.getFocalLength());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy_deg, double(width) / double(height), 0.01 * in_Camera.getFocalLength(), 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const Eigen::Vector3d lookAtPoint = in_Camera.getLookAtPoint();
	gluLookAt(in_Camera.getEyePoint().x(), in_Camera.getEyePoint().y(), in_Camera.getEyePoint().z(), lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z(), in_Camera.getYVector().x(), in_Camera.getYVector().y(), in_Camera.getYVector().z());
}

void drawFloor() {
	glBegin(GL_TRIANGLES);
	for (int j = -20; j < 20; j++) {
		for (int i = -20; i < 20; i++) {
			int cheaker_bw = (i + j) % 2;
			if (cheaker_bw == 0)
			{
				glColor3f(0.3, 0.3, 0.3);

				glVertex3f(i * 0.5, 0.0, j * 0.5);
				glVertex3f(i * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i + 1) * 0.5, 0.0, j * 0.5);

				glVertex3f(i * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i + 1) * 0.5, 0.0, (j + 1) * 0.5);
				glVertex3f((i + 1) * 0.5, 0.0, j * 0.5);
			}
		}
	}
}

void display()
{
	glViewport(0, 0, width * g_FrameSize_WindowSize_Scale_x, height * g_FrameSize_WindowSize_Scale_y);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	projection_and_modelview(g_Camera);

	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	drawFloor();

	drawCG_1();

	drawCG_2();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	width = w;
	height = h;
}

void mouseDrag(int x, int y) {
	const int _dx = x - mx;
	mx = x;
	my = y;

	const double dx = double(_dx) / double(width);
	const double scale = 2.0;

	g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
	glutPostRedisplay();
}

void mouseDown(int x, int y) {
	mx = x;
	my = y;
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT && state == GLUT_DOWN)
		mouseDown(x, y);
}

int main(int argc, char* argv[])
{
	g_Camera.setEyePoint(Eigen::Vector3d{ 0.0, 1.0, 3.0 });
	g_Camera.lookAt(Eigen::Vector3d{ 0.0, 0.0, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0});

	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("Hello world!!");

	// With retina display, frame buffer size is twice the window size.
	// Viewport size should be set on the basis of the frame buffer size, rather than the window size.
	// g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	g_FrameSize_WindowSize_Scale_x = double(dims[2]) / double(width);
	g_FrameSize_WindowSize_Scale_y = double(dims[3]) / double(height);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);


	glutMainLoop();
	return 0;
}