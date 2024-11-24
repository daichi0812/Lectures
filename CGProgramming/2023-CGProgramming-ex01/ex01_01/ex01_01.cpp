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
	int i, k;

	k = 12.0;

	for (i = 0; i < 2 * k; i++) {
		glColor3f(2.0 * sin(3.14 * i / k), 2.0 * cos(3.14 * i / k), -2.0 * sin(3.14 * i / k));
		glVertex3f(cos(3.14 * i / k), sin(3.14 * i / k), 0.0);
		glColor3f(1.5 * sin(3.14 * i / k), 1.5 * cos(3.14 * i / k), -1.5 * sin(3.14 * i / k));
		glVertex3f(cos(3.14 * (i + 1) / k), sin(3.14 * (i + 1) / k), 0.0);
		glColor3f(1.0 * sin(3.14 * i / k), 1.0 * cos(3.14 * i / k), -1.0 * sin(3.14 * i / k));
		glVertex3f(0.0, 0.0, 0.0);
	}

	glEnd();

	glEnable(GL_LINE_WIDTH);
	glLineWidth(3.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);

	for (i = 0; i < 2 * k; i++) {
		glVertex3f(cos(3.14 * i / k), sin(3.14 * i / k), 0.0);
		glVertex3f(cos(3.14 * (i + 1) / k), sin(3.14 * (i + 1) / k), 0.0);
	}

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