#include <GL/freeglut.h>
#include <math.h> 

int width = 640;
int height = 480;

void display()
{
	glViewport(0, 0, width, height);

	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const float half_width = 1.0 * float(width) / float(height);
	const float half_height = 1.0 * float(height) / float(height);
	glOrtho(-half_width, half_width, -half_height, half_height, -1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	int i, j, k, r[500], c = 0;
	int count = 0;
	double x[500], y[500];


	//1000までの自然数にある素数を見つける
	for (i = 2; i < 1000; i++) {
		for (j = 2; j < i+1; j++) {
			if (i % j == 0 && i > j) {
				break;
			}
			if (i % j == 0 && i == j) {
				r[c] = i;
				c++;
			}
		}
	}

	k = 156.0; //　k は　[3, 1000]で設定する

	for (i = 0; i < 2 * k ; i++) {

		//極座標表示(r, θ)において、r = θ = "素数"
		//となるとき、それらの値を直交座標表示に変換
		x[i] = r[i] * cos(r[i]) * 0.001;
		y[i] = r[i] * sin(r[i]) * 0.001;

		//上記を満たすx, yを一つの頂点とする三角形を作成。
		// k の値を大きくするごとに三角形が薄く、数が多くなる
		glColor3f(2.0 * sin(3.14 * i / k), 2.0 * cos(3.14 * i / k), -2.0 * sin(3.14 * i / k));
		glVertex3f(x[i] + 0.08 * cos(3.14 * i / k), y[i] + 0.08 * sin(3.14 * i / k), 0.0);		//点A
		glColor3f(1.5 * sin(3.14 * i / k), 1.5 * cos(3.14 * i / k), -1.5 * sin(3.14 * i / k));
		glVertex3f(x[i] + 0.08 * cos(3.14 * (i + 1) / k), y[i] + 0.08 * sin(3.14 * (i + 1) / k), 0.0);	//点B
		glColor3f(1.0 * sin(3.14 * i / k), 1.0 * cos(3.14 * i / k), -1.0 * sin(3.14 * i / k));
		glVertex3f(x[i], y[i], 0.0);	//点C
	}

	glEnd();

	glEnable(GL_LINE_WIDTH);
	glLineWidth(3.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);

	/*
	for (i = 0; i < 2 * k; i++) {
		//線分AB
		glVertex3f(x[i] + cos(3.14 * i / k), y[i] + sin(3.14 * i / k), 0.0);	//点A
		glVertex3f(x[i] + cos(3.14 * (i + 1) / k), y[i] + sin(3.14 * (i + 1) / k), 0.0);	//点B
	}
	*/

	glEnd();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	width = w;
	height = h;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Hello world!");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutMainLoop();

	return 0;
}