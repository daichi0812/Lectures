//
//  GLPreview.h
//  gl3d_raytracing_v2
//
//  Created by Yonghao Yue on 2019/11/19.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef GLPreview_h
#define GLPreview_h

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/freeglut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Dense>
#include "Camera.h"
#include "TriMesh.h"
#include "Light.h"

void projection_and_modelview( const Camera& in_Camera, const int width, const int height );

void drawLights( const std::vector<Light>& in_Lights );

void drawFilm( const Camera& in_Camera, GLuint in_FilmTexture );
void drawFloor();

void drawObject( const Object& in_Object );

void computeGLShading( Object& io_Object, const std::vector<Light>& lights );

#endif /* GLPreview_h */
