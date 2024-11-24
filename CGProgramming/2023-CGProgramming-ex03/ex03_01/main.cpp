//
//  main.cpp
//
//  Created by Yonghao Yue on 2019/09/28.
//  Updated: 2021/10/13
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

/*
* 青山学院大学 理工学部情報テクノロジー学科
* デジタルメディア設計演習第3回演習課題1
* 共同制作 森下剛・堀田大智・中江朋弘
* アルゴリズム:　drawShadedBox()の中で面ごとにdrawTessellatedShadedSquare()を呼び出し、drawTessellatedShadedSquare()の中で、drawShadedSquare()を複数回呼び出して実装。
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

int width = 640;
int height = 480;
int mx, my;

Camera g_Camera;


Eigen::Vector3d g_PointLightPos{ 0.0, 3.0, 3.0 };
double g_LightIntensity = 20.0;

void drawShadedSquare(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_kd)
{
	const Eigen::Vector3d p_xmym = in_center - in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xpym = in_center + in_arm_u - in_arm_v;
	const Eigen::Vector3d p_xmyp = in_center - in_arm_u + in_arm_v;
	const Eigen::Vector3d p_xpyp = in_center + in_arm_u + in_arm_v;

	Eigen::Vector3d n = in_arm_u.cross(in_arm_v);
	n.normalize();

	Eigen::Vector3d L = g_PointLightPos - in_center;
	const double dist = L.norm();
	L.normalize();
	const double cos_theta = std::max<double>(0.0, L.dot(n));


	const Eigen::Vector3d L_o = in_kd * g_LightIntensity * cos_theta / (dist * dist);

	glBegin(GL_TRIANGLES);

	glColor3f(L_o.x(), L_o.y(), L_o.z());

	glVertex3f(p_xmym.x(), p_xmym.y(), p_xmym.z());
	glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());
	glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

	glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());
	glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());
	glVertex3f(p_xpyp.x(), p_xpyp.y(), p_xpyp.z());

	glEnd();
}

//森下剛　作成
void drawTessellatedShadedSquare_Morishita(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_kd, const int in_nSegs) {

	for (int i = 0; i < in_nSegs; i++) {
		for (int j = 0; j < in_nSegs; j++) {

			Eigen::Vector3d center = in_center - in_arm_u - in_arm_v + in_arm_u / in_nSegs + in_arm_v / in_nSegs + in_arm_v / in_nSegs * i * 2 + in_arm_u / in_nSegs * j * 2;
			Eigen::Vector3d u = in_arm_u / in_nSegs;
			Eigen::Vector3d v = in_arm_v / in_nSegs;

			drawShadedSquare(center, u, v, in_kd);
		}
	}
}

void drawShadedBox_Morishita(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_arm_w, const Eigen::Vector3d& in_kd, const int in_nSegs) {
	// X-
	drawTessellatedShadedSquare_Morishita(in_center - in_arm_u, -in_arm_v, in_arm_w, in_kd, in_nSegs);
	// X+
	drawTessellatedShadedSquare_Morishita(in_center + in_arm_u, in_arm_v, in_arm_w, in_kd, in_nSegs);
	// Y-
	drawTessellatedShadedSquare_Morishita(in_center - in_arm_v, in_arm_u, in_arm_w, in_kd, in_nSegs);
	// Y+
	drawTessellatedShadedSquare_Morishita(in_center + in_arm_v, -in_arm_u, in_arm_w, in_kd, in_nSegs);
	// Z-
	drawTessellatedShadedSquare_Morishita(in_center - in_arm_w, -in_arm_u, in_arm_v, in_kd, in_nSegs);
	// Z+
	drawTessellatedShadedSquare_Morishita(in_center + in_arm_w, in_arm_u, in_arm_v, in_kd, in_nSegs);
}

//堀田大智　作成
void drawTessellatedShadedSquare_Hotta(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_kd, const int in_nSegs) {
	int i, j;

	for (i = 0; i < in_nSegs; i++) {
		for (j = 0; j < in_nSegs; j++) {
			drawShadedSquare(in_center - in_arm_u - in_arm_v + (2 * j + 1) * in_arm_u / in_nSegs + (2 * i + 1) * in_arm_v / in_nSegs, in_arm_u / in_nSegs, in_arm_v / in_nSegs, in_kd);
		}
	}
}

void drawShadedBox_Hotta(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_arm_w, const Eigen::Vector3d& in_kd, const int in_nSegs)
{
	// X-
	drawTessellatedShadedSquare_Hotta(in_center - in_arm_u, -in_arm_v, in_arm_w, in_kd, in_nSegs);
	// X+
	drawTessellatedShadedSquare_Hotta(in_center + in_arm_u, in_arm_v, in_arm_w, in_kd, in_nSegs);
	// Y-
	drawTessellatedShadedSquare_Hotta(in_center - in_arm_v, in_arm_u, in_arm_w, in_kd, in_nSegs);
	// Y+
	drawTessellatedShadedSquare_Hotta(in_center + in_arm_v, -in_arm_u, in_arm_w, in_kd, in_nSegs);
	// Z-
	drawTessellatedShadedSquare_Hotta(in_center - in_arm_w, -in_arm_u, in_arm_v, in_kd, in_nSegs);
	// Z+
	drawTessellatedShadedSquare_Hotta(in_center + in_arm_w, in_arm_u, in_arm_v, in_kd, in_nSegs);
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

void drawFloor()
{
	glBegin(GL_TRIANGLES);
	for (int j = -20; j < 20; j++)
	{
		for (int i = -20; i < 20; i++)
		{
			int checker_bw = (i + j) % 2;
			if (checker_bw == 0)
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
	glEnd();
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

	drawShadedBox_Morishita({ 0.7, 0.3, -0.2 }, { 0.3, 0.0, 0.0 }, { 0.0, 0.3, 0.0 }, { 0.0, 0.0, 0.5 }, { 1.0, 0.8, 0.5 }, 100);
	drawShadedBox_Hotta({ -0.7, 0.2, -0.2 }, { 0.4, 0.0, 0.0 }, { 0.0, 0.2, 0.0 }, { 0.0, 0.0, 0.4 }, { 0.5, 0.8, 1.0 }, 100);

	glutSwapBuffers();
}

void resize(int w, int h)
{
	width = w;
	height = h;
}

void mouseDrag(int x, int y)
{
	const int _dx = x - mx;
	mx = x; my = y;

	const double dx = double(_dx) / double(width);
	const double scale = 2.0;

	g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
	glutPostRedisplay();
}

void mouseDown(int x, int y)
{
	mx = x; my = y;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		mouseDown(x, y);
}

int main(int argc, char* argv[])
{
	g_Camera.setEyePoint(Eigen::Vector3d{ 0.0, 1.0, 3.0 });
	g_Camera.lookAt(Eigen::Vector3d{ 0.0, 0.0, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0 });

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
