//　Edited by Daichi Hotta
// 
//  main.cpp
//  gl3d_hello_world
//
//  Created by Yonghao Yue on 2019/09/28.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

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

enum MouseMode
{
    MM_CAMERA,
    MM_LIGHT
};

struct TriMesh
{
    std::vector<Eigen::Vector3d> vertices;
    std::vector<Eigen::Vector3d> vertex_normals;
    std::vector<Eigen::Vector3d> vertex_colors;
    std::vector<Eigen::Vector2d> tex_coords;
    std::vector<Eigen::Vector3i> triangles;

    GLuint texture;
    Eigen::Vector3d kd;
};


MouseMode g_MouseMode = MM_CAMERA;

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

int width = 640;
int height = 480;

int mx, my;

Camera g_Camera;

Eigen::Vector3d g_PointLightPos { -0.8, 0.8, 0.8 };
double g_LightIntensity = 2.0;

GLuint g_Texture = 0;

//make box
TriMesh g_Box;
// ex5 make sphere
TriMesh g_Sphere;

//Initialinzing the Mesh
void resetMesh(TriMesh& io_Mesh)
{
    io_Mesh.vertices.clear();
    io_Mesh.vertex_normals.clear();
    io_Mesh.vertex_colors.clear();
    io_Mesh.tex_coords.clear();
    io_Mesh.triangles.clear();

    io_Mesh.texture = 0;
    io_Mesh.kd << 0.0, 0.0, 0.0;
}

// Meshing example
void generateTessellatedSquare(TriMesh& out_mesh, const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_arm_u, const Eigen::Vector3d& in_arm_v, const Eigen::Vector3d& in_kd, const int in_nSegs)
{
    out_mesh.vertices.resize((in_nSegs + 1) * (in_nSegs + 1));
    out_mesh.vertex_normals.resize((in_nSegs + 1) * (in_nSegs + 1));
    out_mesh.vertex_colors.resize((in_nSegs + 1) * (in_nSegs + 1));
    out_mesh.tex_coords.resize((in_nSegs + 1) * (in_nSegs + 1));
    out_mesh.triangles.resize(in_nSegs * in_nSegs * 2);

    out_mesh.kd = in_kd;
    out_mesh.texture = 0;

    const Eigen::Vector3d delta_x = 2.0 * in_arm_u / double(in_nSegs);
    const Eigen::Vector3d delta_y = 2.0 * in_arm_v / double(in_nSegs);
    Eigen::Vector3d n = in_arm_u.cross(in_arm_v);
    n.normalize();

    for (int j = 0; j <= in_nSegs; j++)		 // Setting up connection information
    {
        for (int i = 0; i <= in_nSegs; i++)
        {
            const Eigen::Vector3d pm = in_center - in_arm_u - in_arm_v + i * delta_x + j * delta_y;

            const int vertex_flat_idx = j * (in_nSegs + 1) + i;
            out_mesh.vertices[vertex_flat_idx] = pm;
            out_mesh.vertex_normals[vertex_flat_idx] = n;

            out_mesh.tex_coords[vertex_flat_idx].x() = double(i) / double(in_nSegs);
            out_mesh.tex_coords[vertex_flat_idx].y() = double(j) / double(in_nSegs);
        }
    }

    for (int j = 0; j < in_nSegs; j++)
    {
        for (int i = 0; i < in_nSegs; i++)
        {
            const int v_flat_idx = j * (in_nSegs + 1) + i;
            const int vr_flat_idx = j * (in_nSegs + 1) + i + 1;
            const int vt_flat_idx = (j + 1) * (in_nSegs + 1) + i;
            const int vtr_flat_idx = (j + 1) * (in_nSegs + 1) + i + 1;

            const Eigen::Vector3i t1 = { v_flat_idx, vr_flat_idx, vt_flat_idx };
            const Eigen::Vector3i t2 = { vt_flat_idx, vr_flat_idx, vtr_flat_idx };

            const int triangle_flat_idx = 2 * (j * in_nSegs + i);

            out_mesh.triangles[triangle_flat_idx] = t1;
            out_mesh.triangles[triangle_flat_idx + 1] = t2;
        }
    }
}

//computing on a mesh
void computeShading(TriMesh& io_Mesh)
{
    for (int i = 0; i < io_Mesh.vertices.size(); i++)
    {
        Eigen::Vector3d p = io_Mesh.vertices[i];
        Eigen::Vector3d n = io_Mesh.vertex_normals[i];

        Eigen::Vector3d L = g_PointLightPos - p;
        const double dist = L.norm();
        L.normalize();
        const double cos_theta = std::max<double>(0.0, L.dot(n));
        const Eigen::Vector3d I = io_Mesh.kd * g_LightIntensity * cos_theta / (dist * dist);

        io_Mesh.vertex_colors[i] = I;
    }
}

//draw mesh
void drawMesh(const TriMesh& in_Mesh)
{
    if (in_Mesh.texture != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, in_Mesh.texture);
    }

    glBegin(GL_TRIANGLES);

    for (int j = 0; j < in_Mesh.triangles.size(); j++)
    {
        for (int i = 0; i < 3; i++)
        {
            const int vid = in_Mesh.triangles[j](i);
            glColor3d(in_Mesh.vertex_colors[vid].x(), in_Mesh.vertex_colors[vid].y(), in_Mesh.vertex_colors[vid].z());
            glTexCoord2d(in_Mesh.tex_coords[vid].x(), in_Mesh.tex_coords[vid].y());
            glVertex3d(in_Mesh.vertices[vid].x(), in_Mesh.vertices[vid].y(), in_Mesh.vertices[vid].z());
        }
    }

    glEnd();

    if (in_Mesh.texture != 0)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

// mesh connected (Sometimes you use it and sometimes you don't use it)
void extendMesh(TriMesh& io_BaseMesh, const TriMesh& in_SecondMesh)
{
    const size_t vid_offset = io_BaseMesh.vertices.size();

    const size_t num_v_to_extend = in_SecondMesh.vertices.size();
    for (size_t i = 0; i < num_v_to_extend; i++)
    {
        io_BaseMesh.vertices.push_back(in_SecondMesh.vertices[i]);
        io_BaseMesh.vertex_normals.push_back(in_SecondMesh.vertex_normals[i]);
        io_BaseMesh.vertex_colors.push_back(in_SecondMesh.vertex_colors[i]);
        io_BaseMesh.tex_coords.push_back(in_SecondMesh.tex_coords[i]);
    }

    const size_t num_t_to_extend = in_SecondMesh.triangles.size();
    for (size_t i = 0; i < num_t_to_extend; i++)
    {
        const Eigen::Vector3i triangle_vids = in_SecondMesh.triangles[i];
        io_BaseMesh.triangles.push_back(triangle_vids.array() + vid_offset);
    }

    io_BaseMesh.kd = in_SecondMesh.kd;
    io_BaseMesh.texture = in_SecondMesh.texture;
}

/*
// make box
void generateTessellatedBox(TriMesh& out_mesh, const Eigen::Vector3d& in_center, const Eigen::Vector3d& in_x_arm, const Eigen::Vector3d& in_y_arm, const Eigen::Vector3d& in_z_arm, const Eigen::Vector3d& in_kd, const int in_nSegs)
{
    resetMesh(out_mesh);

    // X-
    TriMesh Xm;
    generateTessellatedSquare(Xm, in_center - in_x_arm, -in_y_arm, in_z_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Xm);

    // X+
    TriMesh Xp;
    generateTessellatedSquare(Xp, in_center + in_x_arm, in_y_arm, in_z_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Xp);

    // Y-
    TriMesh Ym;
    generateTessellatedSquare(Ym, in_center - in_y_arm, in_x_arm, in_z_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Ym);

    // Y+
    TriMesh Yp;
    generateTessellatedSquare(Yp, in_center + in_y_arm, -in_x_arm, in_z_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Yp);

    // Z-
    TriMesh Zm;
    generateTessellatedSquare(Zm, in_center - in_z_arm, -in_x_arm, in_y_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Zm);

    // Z+
    TriMesh Zp;
    generateTessellatedSquare(Zp, in_center + in_z_arm, in_x_arm, in_y_arm, in_kd, in_nSegs);
    extendMesh(out_mesh, Zp);
}
*/

#define MAX 3000

void generateTessellatedSphere(TriMesh& out_mesh, const Eigen::Vector3d& in_center, const double& in_r, const Eigen::Vector3d& in_kd, const int in_nSegs) {
    int i, j, k, l;
    int c = 0;
    double ido[MAX], keido[MAX];
    double v[MAX][3], v1[MAX][3], v2[MAX][3], v3[MAX][3];

    //それぞれの角度を定める(θ:緯度(ido)、Φ:経度(keido))
    for (i = 0; i < in_nSegs + 1; i++) {
        for (j = 0; j < in_nSegs * 2; j++) {
            ido[c] = i * 3.1415 / in_nSegs;
            keido[c] = j * 3.1415 / in_nSegs;

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
        v[k][1] = in_r * sin(ido[k]) * cos(keido[k]);
        v[k][2] = in_r * sin(ido[k]) * sin(keido[k]);
        v[k][3] = in_r * cos(ido[k]);

        //次の経度(keido + 1)の点
        v1[k][1] = in_r * sin(ido[k]) * cos(keido[k] + 3.1415 / in_nSegs);
        v1[k][2] = in_r * sin(ido[k]) * sin(keido[k] + 3.1415 / in_nSegs);
        v1[k][3] = in_r * cos(ido[k]);

        //次の緯度(ido + 1)の点
        v2[k][1] = in_r * sin(ido[k] + 3.1415 / in_nSegs) * cos(keido[k]);
        v2[k][2] = in_r * sin(ido[k] + 3.1415 / in_nSegs) * sin(keido[k]);
        v2[k][3] = in_r * cos(ido[k] + 3.1415 / in_nSegs);

        //次の緯度(ido + 1)、経度(keido + 1)の点
        v3[k][1] = in_r * sin(ido[k] + 3.1415 / in_nSegs) * cos(keido[k] + 3.1415 / in_nSegs);
        v3[k][2] = in_r * sin(ido[k] + 3.1415 / in_nSegs) * sin(keido[k] + 3.1415 / in_nSegs);
        v3[k][3] = in_r * cos(ido[k] + 3.1415 / in_nSegs);

        Eigen::Vector3d in_p1{ v[k][1], v[k][3], v[k][2] };		//点v の位置ベクトル
        Eigen::Vector3d in_p2{ v2[k][1], v2[k][3], v2[k][2] };	//点v2 の位置ベクトル
        Eigen::Vector3d in_p2s{ v1[k][1], v1[k][3], v1[k][2] };	//点v1 の位置ベクトル
        Eigen::Vector3d in_p3{ v3[k][1], v3[k][3], v3[k][2] };		//点v3 の位置ベクトル

        TriMesh V;
        generateTessellatedSquare(V, (in_p2s + in_p2) / 2.0 + in_center, (((in_p3 + in_p2s) / 2.0) - ((in_p2 + in_p1)) / 2.0) / 2.0, (in_p3 - in_p2s) / 2.0, in_kd, in_nSegs);
        /* in_arm_u すなわち x成分のベクトルの生成について、四角形の頂点から作り出そうとすると球を生成した際に北半球は隙間ができないが、南半球には隙間ができるといった現象が起きた。
        ので、四角形の中心の始点とする in_arm_u をつくるために、複雑な式となった。結果、北半球と南半球のどちらにも小さくなった隙間が生じるようになった。
        これは、分割数を増やすことで解決しようと思う。
        */
        extendMesh(out_mesh, V);

    }
}

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

void idle()		// 1/60 second wait -> 1/60 second Count+1 -> make animation
{
#ifdef __APPLE__
    usleep(1000 * 1000 / 60);
#else
    Sleep(1000.0 / 60.0);
#endif
    glutPostRedisplay();
}

void mouseDrag(int x, int y)
{
    int _dx = x - mx, _dy = y - my;
    mx = x; my = y;

    double dx = double(_dx) / double(width);
    double dy = -double(_dy) / double(height);

    if (g_MouseMode == MM_CAMERA)
    {
        double scale = 2.0;

        g_Camera.rotateCameraInLocalFrameFixLookAt(dx * scale);
        glutPostRedisplay();
    }
    else if (g_MouseMode == MM_LIGHT)
    {
        double scale = 1.0;

        g_PointLightPos += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
        glutPostRedisplay();
    }
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

void drawLight()
{
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

    // box
    //computeShading(g_Box);
    //drawMesh(g_Box);

    //sphere
    computeShading(g_Sphere);
    drawMesh(g_Sphere);

    drawLight();

    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void resize(int w, int h)
{
    width = w;
    height = h;
}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
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
    glutKeyboardFunc(key);

    //g_Texture = prepareTextureFromJpegFile( "./wood2.jpeg" );
    //g_Texture = prepareTextureFromJpegFile( "./Lenna.jpg" );

    //make box
    //generateTessellatedBox(g_Box, { 0.7, 0.3, -0.2 }, { 0.3, 0.0, 0.0 }, { 0.0, 0.3, 0.0 }, { 0.0, 0.0, 0.5 }, { 1.0, 1.0, 1.0 }, 8);
    generateTessellatedSphere(g_Sphere, { 0.0, 0.5, 0.0 }, 0.5, { 0.3, 0.3, 0.3 }, 38);
    g_Sphere.texture = prepareTextureFromJpegFile("/CGProgramming/ex05/Release/wood2.jpeg");

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glutMainLoop();
    return 0;
}
