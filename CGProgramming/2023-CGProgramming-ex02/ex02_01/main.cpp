//
//  main.cpp
//
//  Created by Yonghao Yue on 2019/09/28.
//  Updated: 2021/10/06
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

/*
* 青山学院大学 理工学部情報テクノロジー学科
* デジタルメディア設計演習第2回課題
* 共同制作 森下剛・堀田大智・中江朋弘
* 解答は関数drewCG_1～4内で作成
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

#define sides 999 //分割数指定
#define radius 0.8 //大きさ指定(0<radius<1)
#define M_PI 3.141592653589 //円周率

Camera g_Camera;

/*カメラの中心にある最初の三角形の座標vertexの値は
* glVertex3f(0.0, 0.8, 0.0);
* glVertex3f(-0.8, -0.8, 0.0);
* glVertex3f(0.8, -0.8, 0.0);
*/

//演習問題1
void drawCG_1() {
	//一番手前の面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.7);	//点B
	glColor3f(0.8, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.7);	//点C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0.5, 0.7);	//点A
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.5, 0.7);	//点A
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.5, 0.7);	//点D
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.5, 0, 0.7);	//点C
	glEnd();

	//右側面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.5, 0.5, 0.7);	//点D
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.7);	//点C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.5, 0.5, 0.2);	//点H
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.5, 0.0, 0.2);	//点G
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.7);	//点C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.5, 0.5, 0.2);	//点H
	glEnd();

	//左側面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.5, 0.7);	//点A
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.7);	//点B
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0, 0.2);	//点F
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.5, 0.7);	//点A
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 0.5, 0.2);	//点E
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0, 0.2);	//点F
	glEnd();

	//上面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.5, 0.7);	//点A
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.5, 0.7);	//点D
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0.5, 0.2);	//点E
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.5, 0.5, 0.2);	//点H
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.5, 0.7);	//点D
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0.5, 0.2);	//点E
	glEnd();

	//底面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.0, 0.7);	//点B
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.7);	//点C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0, 0.2);	//点F
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.5, 0.0, 0.2);	//点G
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.7);	//点C
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0, 0.2);	//点F
	glEnd();

	//奥の面
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.5, 0.2);	//点E
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.5, 0.2);	//点H
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.5, 0, 0.2);	//点G
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.8, 0.0);
	glVertex3f(1.0, 0.0, 0.2);	//点F
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.5, 0.0, 0.2);	//点G
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(1.0, 0.5, 0.2);	//点E
	glEnd();
}


void drawCG_2() {

	const double angle = 2 * M_PI / sides;

	for (int i = 0; i < sides; i++) {

		glColor3f(cos(i * angle), sin(i * angle), -cos(i * angle - (M_PI / 4)));//位相がちょうどよくずれるようにBlueの値を設定

		glBegin(GL_TRIANGLES);
		glVertex3f(0.0 - 2.0, 2.0, 0.0 - 2.0); //頂点座標

		double x1 = radius * cos(i * angle);
		double z1 = radius * sin(i * angle);
		glVertex3f(x1 - 2.0, 0.0, z1 - 2.0); // - 2.0は座標ずらし

		//x1,y1よりiを1ずらした座標をセットする
		double x2 = radius * cos((i + 1) * angle);
		double z2 = radius * sin((i + 1) * angle);
		glVertex3f(x2 - 2.0, 0.0, z2 - 2.0); // - 2.0は座標ずらし

		glEnd();
	}
}

//演習問題3 4
#define MAX 4705
#define n 48

void drawCG_3_4() {
	int i, j, k, l;
	double r = 1.0;
	int c = 0;
	double ido[MAX], keido[MAX];
	double v[MAX][3], v1[MAX][3], v2[MAX][3], v3[MAX][3];

	//それぞれの角度を定める(θ:緯度(ido)、Φ:経度(keido))
	for (i = 0; i < n + 1; i++) {
		for (j = 0; j < n * 2; j++) {
			ido[c] = i * 3.1415 / n;
			keido[c] = j * 3.1415 / n;

			if (ido[c] >= 3.1415) {
				ido[c] = 3.14159265;
			}

			if (keido[c] >= 6.283) {
				keido[c] = 0.0;

			}
			c++;
		}
	}

	for (k = 0; k < c + 1; k++) {
		//現在の点
		v[k][1] = r * sin(ido[k]) * cos(keido[k]);
		v[k][2] = r * sin(ido[k]) * sin(keido[k]);
		v[k][3] = r * cos(ido[k]);

		//次の経度(keido + 1)の点
		v1[k][1] = r * sin(ido[k]) * cos(keido[k] + 3.1415 / n);
		v1[k][2] = r * sin(ido[k]) * sin(keido[k] + 3.1415 / n);
		v1[k][3] = r * cos(ido[k]);

		//次の緯度(ido + 1)の点
		v2[k][1] = r * sin(ido[k] + 3.1415 / n) * cos(keido[k]);
		v2[k][2] = r * sin(ido[k] + 3.1415 / n) * sin(keido[k]);
		v2[k][3] = r * cos(ido[k] + 3.1415 / n);

		//次の緯度(ido + 1)、経度(keido + 1)の点
		v3[k][1] = r * sin(ido[k] + 3.1415 / n) * cos(keido[k] + 3.1415 / n);
		v3[k][2] = r * sin(ido[k] + 3.1415 / n) * sin(keido[k] + 3.1415 / n);
		v3[k][3] = r * cos(ido[k] + 3.1415 / n);
	}

	for (l = 0; l < c + 1; l++) {
		//v, v2, v3からなる三角形
		glBegin(GL_TRIANGLES);
		glColor3f(0.4, 0.9, 0.4);
		glVertex3f(v[l][1], v[l][3], v[l][2]);
		glVertex3f(v2[l][1], v2[l][3], v2[l][2]);
		glVertex3f(v3[l][1], v3[l][3], v3[l][2]);
		glEnd();

		//v, v1, v3からなる三角形
		glBegin(GL_TRIANGLES);
		glColor3f(0.4, 0.9, 0.4);
		glVertex3f(v[l][1], v[l][3], v[l][2]);
		glVertex3f(v1[l][1], v1[l][3], v1[l][2]);
		glVertex3f(v3[l][1], v3[l][3], v3[l][2]);
		glEnd();
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

	drawCG_3_4();

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
