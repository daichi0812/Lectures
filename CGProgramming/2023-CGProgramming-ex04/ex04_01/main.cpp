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
#include <vector>
#include <iostream>

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include "Camera.h"
#include "Jpeg.h"

//キーで操作モードを切り替える
enum MouseMode{ MM_CAMERA, MM_LIGHT};

MouseMode g_MouseMode = MM_CAMERA;

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

int width = 640;
int height = 480;

int mx, my;

Camera g_Camera;

Eigen::Vector3d g_PointLightPos{ -0.8, 0.8, 0.8 };
double g_LightIntensity = 2.0;

GLuint g_Texture = 0;

GLuint prepareTextureFromJpegFile(const char* in_FileName)
{
    JpegData data;
    readJpegData(data, in_FileName);

    if (data.ch != 3)
    {
        std::cout << "Error: Currently only images with three color channels are supported." << std::endl;
        std::cout << "The loaded image has " << data.ch << " channels." << std::endl;

        finalizeJpegData(data);
        exit(-1);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    finalizeJpegData(data);

    return texture;
}

void drawSquareWithTexture(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_color, GLuint in_texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, in_texture);

    glBegin(GL_TRIANGLES);

    glColor3f(in_color.x(), in_color.y(), in_color.z());

    const Eigen::Vector3d p_xmym = in_center - in_arm_u - in_arm_v;
    const Eigen::Vector3d p_xpym = in_center + in_arm_u - in_arm_v;
    const Eigen::Vector3d p_xmyp = in_center - in_arm_u + in_arm_v;
    const Eigen::Vector3d p_xpyp = in_center + in_arm_u + in_arm_v;

    //glTexCoord2f( 0.0, 0.0 );
    glTexCoord2f(0.0, 1.0);
    glVertex3f(p_xmym.x(), p_xmym.y(), p_xmym.z());

    //glTexCoord2f( 1.0, 0.0 );
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());

    //glTexCoord2f( 0.0, 1.0 );
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

    //glTexCoord2f( 0.0, 1.0 );
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

    //glTexCoord2f( 1.0, 0.0 );
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());

    //glTexCoord2f( 1.0, 1.0 );
    glTexCoord2f(1.0, 0.0);
    glVertex3f(p_xpyp.x(), p_xpyp.y(), p_xpyp.z());

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

Eigen::Vector3d computeShading(const Eigen::Vector3d& in_pos, const Eigen::Vector3d& in_normal, const Eigen::Vector3d& in_kd) {
    Eigen::Vector3d L = g_PointLightPos - in_pos;
    const double dist = L.norm();
    L.normalize();
    const double cos_theta = std::max<double>(0.0, L.dot(in_normal));
    return in_kd * g_LightIntensity * cos_theta / (dist * dist);
}

void drawSquareWithTextureWithShading(const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_color, GLuint in_texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, in_texture);

    glBegin(GL_TRIANGLES);

    const Eigen::Vector3d p_xmym = in_center - in_arm_u - in_arm_v;
    const Eigen::Vector3d p_xpym = in_center + in_arm_u - in_arm_v;
    const Eigen::Vector3d p_xmyp = in_center - in_arm_u + in_arm_v;
    const Eigen::Vector3d p_xpyp = in_center + in_arm_u + in_arm_v;

    Eigen::Vector3d normal = in_arm_u.cross(in_arm_v);
    normal.normalize();

    const Eigen::Vector3d color_xmym = computeShading(p_xmym, normal, in_color);
    const Eigen::Vector3d color_xpym = computeShading(p_xpym, normal, in_color);
    const Eigen::Vector3d color_xmyp = computeShading(p_xmyp, normal, in_color);
    const Eigen::Vector3d color_xpyp = computeShading(p_xpyp, normal, in_color);

    glColor3f(color_xmym.x(), color_xmym.y(), color_xmym.z());
    glTexCoord2f(0.0, 1.0);
    glVertex3f(p_xmym.x(), p_xmym.y(), p_xmym.z());

    glColor3f(color_xpym.x(), color_xpym.y(), color_xpym.z());
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());

    glColor3f(color_xmyp.x(), color_xmyp.y(), color_xmyp.z());
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

    glColor3f(color_xmyp.x(), color_xmyp.y(), color_xmyp.z());
    glTexCoord2f(0.0, 0.0);
    glVertex3f(p_xmyp.x(), p_xmyp.y(), p_xmyp.z());

    glColor3f(color_xpym.x(), color_xpym.y(), color_xpym.z());
    glTexCoord2f(1.0, 1.0);
    glVertex3f(p_xpym.x(), p_xpym.y(), p_xpym.z());

    glColor3f(color_xpyp.x(), color_xpyp.y(), color_xpyp.z());
    glTexCoord2f(1.0, 0.0);
    glVertex3f(p_xpyp.x(), p_xpyp.y(), p_xpyp.z());

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawLight(){
    const double size = 0.05;
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() + size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() + size);
    glVertex3f(g_PointLightPos.x() + size, g_PointLightPos.y(), g_PointLightPos.z());

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() + size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x() + size, g_PointLightPos.y(), g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() - size);

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() + size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() - size);
    glVertex3f(g_PointLightPos.x() - size, g_PointLightPos.y(), g_PointLightPos.z());

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() + size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x() - size, g_PointLightPos.y(), g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() + size);

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() - size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x() + size, g_PointLightPos.y(), g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() + size);

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() - size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() - size);
    glVertex3f(g_PointLightPos.x() + size, g_PointLightPos.y(), g_PointLightPos.z());

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() - size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x() - size, g_PointLightPos.y(), g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() - size);

    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y() - size, g_PointLightPos.z());
    glVertex3f(g_PointLightPos.x(), g_PointLightPos.y(), g_PointLightPos.z() + size);
    glVertex3f(g_PointLightPos.x() - size, g_PointLightPos.y(), g_PointLightPos.z());

    glEnd();
}


void idle()
{
#ifdef __APPLE__
    usleep(1000 * 1000 / 60);
#else
    Sleep(1000.0 / 60.0);
#endif
    glutPostRedisplay();
}

//キーで操作モードを切り替える
void key(unsigned char key, int x, int y) {
    switch (key) {
    case 'C':
    case 'c':
        g_MouseMode = MM_CAMERA;
        break;
    case 'L':
    case 'l':
        g_MouseMode = MM_LIGHT;
        break;
    }
}

void mouseDrag(int x, int y){
    int _dx = x - mx, _dy = y - my;
    mx = x; my = y;

    double dx = double(_dx) / double(width);
    double dy = -double(_dy) / double(height);

    if (g_MouseMode == MM_CAMERA){
        double scale = 2.0;

        g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
        glutPostRedisplay();
    }
    else if (g_MouseMode == MM_LIGHT) {
        double scale = 1.0;

        g_PointLightPos += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
        glutPostRedisplay();
    }
}

void mouseDown(int x, int y){
    mx = x; my = y;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        mouseDown(x, y);
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

    drawFloor();
  
    drawSquareWithTexture( {0.0, 0.5, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.4, -0.1}, {1.0, 1.0, 1.0}, g_Texture );

    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void resize(int w, int h)
{
    width = w;
    height = h;
}

int main(int argc, char* argv[])
{
    g_Camera.setEyePoint(Eigen::Vector3d{ 0.0, 1.0, 3.0 });
    g_Camera.lookAt(Eigen::Vector3d{ 0.0, 0.0, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0 });

    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutCreateWindow("Hello world!!");

    GLint dims[4] = { 0 };
    glGetIntegerv(GL_VIEWPORT, dims);
    g_FrameSize_WindowSize_Scale_x = double(dims[2]) / double(width);
    g_FrameSize_WindowSize_Scale_y = double(dims[3]) / double(height);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseDrag);
    //キーで操作モードを切り替える


    g_Texture = prepareTextureFromJpegFile( "C:/CGProgramming/ex04/Release/wood2.jpeg" );
    //g_Texture = prepareTextureFromJpegFile("C:/CGProgramming/ex04/Release/Lenna.jpg");

    //テクスチャ
    //drawSquareWithTexture({ 0.0, 0.5, 0.0 }, { 0.5, 0.0, 00 }, { 0.0, 0.4, -0.1 }, { 1.0, 1.0, 1.0 }, g_Texture);
    drawSquareWithTextureWithShading({ 0.0, 0.5, 0.0 }, { 0.5, 0.0, 0.0 }, { 0.0, 0.4, -0.1 }, { 1.0, 1.0, 1.0 }, g_Texture);

    drawLight();

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glutMainLoop();
    return 0;
}
