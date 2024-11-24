//
//  main.cpp
//  gl3d_hello_world
//
//  Created by Yonghao Yue on 2019/09/28.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

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
#include <vector>
#include <iostream>

#include "Camera.h"
#include "Jpeg.h"
#include "TriMesh.h"

#include "GLPreview.h"
#include "random.h"

enum MouseMode
{
  MM_CAMERA,
  MM_LIGHT,
};

struct RayTracingInternalData
{
  int nextPixel_i;
  int nextPixel_j;
};

struct RayHit
{
  double t;
  double alpha;
  double beta;
  int mesh_idx;
  int tri_idx;
  bool isFront;
};

const double __FAR__ = 1.0e33;
const int MAX_RAY_DEPTH = 8;

const int g_FilmWidth = 640;
const int g_FilmHeight = 480;
float* g_FilmBuffer = nullptr;
float* g_AccumulationBuffer = nullptr;
int* g_CountBuffer = nullptr;
GLuint g_FilmTexture = 0;

RayTracingInternalData g_RayTracingInternalData;

bool g_DrawFilm = true;

int width = 640;
int height = 480;
int nSamplesPerPixel = 1;

MouseMode g_MouseMode = MM_CAMERA;
int g_MM_LIGHT_idx = 0;
int mx, my;

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

Camera g_Camera;
std::vector<Light> g_Lights;

Object g_Obj;

Eigen::Vector3d computeShading( const Ray& in_Ray, const RayHit& in_RayHit, const Object& in_Object, const std::vector<Light>& in_Lights );

void initLights()
{
  Light light1;
  light1.pos << -1.2, 1.2, 1.2;
  light1.color << 1.0, 0.8, 0.3;
  light1.intensity = 5.0;
  
  Light light2;
  light2.pos << 1.2, 1.2, 0.0;
  light2.color << 0.3, 0.3, 1.0;
  light2.intensity = 5.0;

  g_Lights.push_back( light1 );
  g_Lights.push_back( light2 );
}

void resetFilm()
{
  memset( g_AccumulationBuffer, 0, sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
  memset( g_CountBuffer, 0, sizeof(int) * g_FilmWidth * g_FilmHeight );
}

void initFilm()
{
  g_FilmBuffer = (float*)malloc( sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
  g_AccumulationBuffer = (float*)malloc( sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
  g_CountBuffer = (int*)malloc( sizeof(int) * g_FilmWidth * g_FilmHeight );
  resetFilm();
  
  glGenTextures( 1, &g_FilmTexture );
  glBindTexture( GL_TEXTURE_2D, g_FilmTexture );
  
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, g_FilmWidth, g_FilmHeight, 0, GL_RGB, GL_FLOAT, g_FilmBuffer );
  
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}

void updateFilm()
{
  for( int i=0; i<g_FilmWidth * g_FilmHeight; i++ )
  {
    if( g_CountBuffer[i] > 0 )
    {
      g_FilmBuffer[i*3] = g_AccumulationBuffer[i*3] / g_CountBuffer[i];
      g_FilmBuffer[i*3+1] = g_AccumulationBuffer[i*3+1] / g_CountBuffer[i];
      g_FilmBuffer[i*3+2] = g_AccumulationBuffer[i*3+2] / g_CountBuffer[i];
    }
    else
    {
      g_FilmBuffer[i*3] = 0.0;
      g_FilmBuffer[i*3+1] = 0.0;
      g_FilmBuffer[i*3+2] = 0.0;
    }
  }
  
  glBindTexture( GL_TEXTURE_2D, g_FilmTexture );
  glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, g_FilmWidth, g_FilmHeight, GL_RGB, GL_FLOAT, g_FilmBuffer);
}

void clearRayTracedResult()
{
  g_RayTracingInternalData.nextPixel_i = -1;
  g_RayTracingInternalData.nextPixel_j = 0;
  
  memset( g_FilmBuffer, 0, sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
}

void stepToNextPixel( RayTracingInternalData& io_data )
{
  io_data.nextPixel_i++;
  if( io_data.nextPixel_i >= g_FilmWidth )
  {
    io_data.nextPixel_i = 0;
    io_data.nextPixel_j++;
    
    if( io_data.nextPixel_j >= g_FilmHeight )
    {
      io_data.nextPixel_j = 0;
    }
  }
}

void rayTriangleIntersect( const TriMesh& in_Mesh, const int in_Triangle_idx, const Ray& in_Ray, RayHit& out_Result )
{
  out_Result.t = __FAR__;
  
  const Eigen::Vector3d v1 = in_Mesh.vertices[in_Mesh.triangles[in_Triangle_idx](0)];
  const Eigen::Vector3d v2 = in_Mesh.vertices[in_Mesh.triangles[in_Triangle_idx](1)];
  const Eigen::Vector3d v3 = in_Mesh.vertices[in_Mesh.triangles[in_Triangle_idx](2)];

  Eigen::Vector3d triangle_normal = ( v1 - v3 ).cross( v2 - v3 );
  triangle_normal.normalize();
  
  bool isFront = true;
  
  const double denominator = triangle_normal.dot( in_Ray.d );
  if( denominator >= 0.0 )
    isFront = false;
  
  const double t = triangle_normal.dot( v3 - in_Ray.o ) / denominator;
  
  if( t <= 0.0 )
    return;
  
  const Eigen::Vector3d x = in_Ray.o + t * in_Ray.d;
  
  Eigen::Matrix<double, 3, 2> A;
  A.col(0) = v1 - v3; A.col(1) = v2 - v3;
  
  Eigen::Matrix2d ATA = A.transpose() * A;
  const Eigen::Vector2d b = A.transpose() * (x - v3);
  
  const Eigen::Vector2d alpha_beta = ATA.inverse() * b;
  
  if( alpha_beta.x() < 0.0 || 1.0 < alpha_beta.x() || alpha_beta.y() < 0.0 || 1.0 < alpha_beta.y() || 1.0 - alpha_beta.x() - alpha_beta.y() < 0.0 || 1.0 < 1.0 - alpha_beta.x() - alpha_beta.y() ) return;
  
  out_Result.t = t;
  out_Result.alpha = alpha_beta.x();
  out_Result.beta = alpha_beta.y();
  out_Result.isFront = isFront;
}

void rayTracing( const Object& in_Object, const Ray& in_Ray, RayHit& io_Hit )
{
  double t_min = __FAR__;
  double alpha_I = 0.0, beta_I = 0.0;
  int mesh_idx = -1; int tri_idx = -1;
  bool isFront = true;
  
  for( int m=0; m<in_Object.meshes.size(); m++ )
  {
    for( int k=0; k<in_Object.meshes[m].triangles.size(); k++ )
    {
      RayHit temp_hit;
      rayTriangleIntersect( in_Object.meshes[m], k, in_Ray, temp_hit );
      if( temp_hit.t < t_min )
      {
        t_min = temp_hit.t;
        alpha_I = temp_hit.alpha;
        beta_I = temp_hit.beta;
        mesh_idx = m;
        tri_idx = k;
        isFront = temp_hit.isFront;
      }
    }
  }
  
  io_Hit.t = t_min;
  io_Hit.alpha = alpha_I;
  io_Hit.beta = beta_I;
  io_Hit.mesh_idx = mesh_idx;
  io_Hit.tri_idx = tri_idx;
  io_Hit.isFront = isFront;
}

Eigen::Vector3d computeDirectLighting( const Light& in_Light, const Eigen::Vector3d& in_x, const Eigen::Vector3d& in_n, const Eigen::Vector3d& in_w_eye, const Object& in_Object, const Material& in_Material, const int depth )
{
  const Eigen::Vector3d x_with_offset = in_x + in_n * 0.000001;
  
  Eigen::Vector3d w_L = in_Light.pos - x_with_offset;
  const double dist = w_L.norm();
  w_L.normalize();
  
  // shadow test
  Ray ray; ray.o = x_with_offset; ray.d = w_L; ray.depth = depth + 1;
  RayHit rh;
  rayTracing( in_Object, ray, rh );
  if( rh.t > dist )
  {
    // diffuse
    const double cos_theta = std::max<double>( 0.0, w_L.dot( in_n ) );
    return in_Light.color.cwiseProduct( in_Material.kd ) * in_Light.intensity * cos_theta / ( dist * dist );
  }
  else
    return Eigen::Vector3d::Zero();
}

Eigen::Vector3d computeRayHitNormal( const Object& in_Object, const RayHit& in_Hit )
{
  const int v1_idx = in_Object.meshes[in_Hit.mesh_idx].triangles[in_Hit.tri_idx](0);
  const int v2_idx = in_Object.meshes[in_Hit.mesh_idx].triangles[in_Hit.tri_idx](1);
  const int v3_idx = in_Object.meshes[in_Hit.mesh_idx].triangles[in_Hit.tri_idx](2);
  
  const Eigen::Vector3d n1 = in_Object.meshes[in_Hit.mesh_idx].vertex_normals[v1_idx];
  const Eigen::Vector3d n2 = in_Object.meshes[in_Hit.mesh_idx].vertex_normals[v2_idx];
  const Eigen::Vector3d n3 = in_Object.meshes[in_Hit.mesh_idx].vertex_normals[v3_idx];
  
  const double gamma = 1.0 - in_Hit.alpha - in_Hit.beta;
  Eigen::Vector3d n = in_Hit.alpha * n1 + in_Hit.beta * n2 + gamma * n3;
  n.normalize();
  
  if( !in_Hit.isFront ) n = -n;
  
  return n;
}

Eigen::Vector3d computeReflection( const Eigen::Vector3d& in_x, const Eigen::Vector3d& in_n, const Eigen::Vector3d& in_w_eye, const RayHit& in_ray_hit, const Object& in_Object, const Material& in_Material, const std::vector<Light>& in_Lights, const int depth )
{
  const Eigen::Vector3d x_with_offset = in_x + in_n * 0.000001;
  
  const double e_dot_n = in_w_eye.dot( in_n );
  Eigen::Vector3d w_L = 2.0 * in_n * e_dot_n - in_w_eye;
  w_L.normalize();
  
  Ray ray;
  ray.o = x_with_offset; ray.d = w_L; ray.depth = depth + 1;
  
  RayHit new_ray_hit;
  rayTracing( in_Object, ray, new_ray_hit );
  
  if( new_ray_hit.tri_idx >= 0 )
  {
    return computeShading( ray, new_ray_hit, in_Object, in_Lights );
  }
  
  return Eigen::Vector3d::Zero();
}

Eigen::Vector3d computeRefraction( const Eigen::Vector3d& in_x, const Eigen::Vector3d& in_n, const Eigen::Vector3d& in_w_eye, const RayHit& in_ray_hit, const Object& in_Object, const Material& in_Material, const std::vector<Light>& in_Lights, const int depth )
{
  const double e_dot_n = in_w_eye.dot( in_n );
  const double eta = in_ray_hit.isFront ? in_Material.eta : 1.0 / in_Material.eta;
  
  const double inside_sqrt = 1.0 - eta*eta * ( 1.0 - e_dot_n * e_dot_n );
  if( inside_sqrt < 0.0 )
  {
    return computeReflection( in_x, in_n, in_w_eye, in_ray_hit, in_Object, in_Material, in_Lights, depth );
  }
  else
  {
    Eigen::Vector3d w_t = - in_n * sqrt( inside_sqrt ) - eta * ( in_w_eye - e_dot_n * in_n );
    w_t.normalize();
    
    const Eigen::Vector3d x_with_offset = in_x - in_n * 0.000001;

    Ray ray;
    ray.o = x_with_offset; ray.d = w_t; ray.depth = depth + 1;
    
    RayHit new_ray_hit;
    rayTracing( in_Object, ray, new_ray_hit );
    
    if( new_ray_hit.tri_idx >= 0 )
    {
      return computeShading( ray, new_ray_hit, in_Object, in_Lights );
    }

    return Eigen::Vector3d::Zero();
  }
}

Eigen::Vector3d computeShading( const Ray& in_Ray, const RayHit& in_RayHit, const Object& in_Object, const std::vector<Light>& in_Lights )
{
// if( in_Ray.depth > MAX_RAY_DEPTH ) return Eigen::Vector3d::Zero();
  
  const Eigen::Vector3d x = in_Ray.o + in_RayHit.t * in_Ray.d;
  const Eigen::Vector3d n = computeRayHitNormal( in_Object, in_RayHit );
  
  Eigen::Vector3d I = Eigen::Vector3d::Zero();
  
  const double kd_max = in_Object.meshes[in_RayHit.mesh_idx].material.kd.maxCoeff();
  const double ks_max = in_Object.meshes[in_RayHit.mesh_idx].material.ks.maxCoeff();
  const double kt_max = in_Object.meshes[in_RayHit.mesh_idx].material.kt.maxCoeff();
  
  const double r = randomMT();
  
  if( r < kd_max )
  {
    Eigen::Vector3d direct_contribution = Eigen::Vector3d::Zero();
    for( int i=0; i<in_Lights.size(); i++ )
    {
      direct_contribution += computeDirectLighting( in_Lights[i], x, n, -in_Ray.d, in_Object, in_Object.meshes[in_RayHit.mesh_idx].material, in_Ray.depth );
    }
    
    I += direct_contribution / kd_max;
  }
  else if( r < kd_max + ks_max )
  {
    I += in_Object.meshes[in_RayHit.mesh_idx].material.ks.cwiseProduct( computeReflection( x, n, -in_Ray.d, in_RayHit, in_Object, in_Object.meshes[in_RayHit.mesh_idx].material, in_Lights, in_Ray.depth ) ) / ks_max;
  }
  else if( r < kd_max + ks_max + kt_max )
  {
    I += in_Object.meshes[in_RayHit.mesh_idx].material.kt.cwiseProduct( computeRefraction( x, n, -in_Ray.d, in_RayHit, in_Object, in_Object.meshes[in_RayHit.mesh_idx].material, in_Lights, in_Ray.depth ) ) / kt_max;
  }
  
  return I;
}

void shadeNextPixel()
{
  stepToNextPixel( g_RayTracingInternalData );
  
  const int pixel_flat_idx = g_RayTracingInternalData.nextPixel_j * g_FilmWidth + g_RayTracingInternalData.nextPixel_i;
  
  Eigen::Vector3d I = Eigen::Vector3d::Zero();
  
  for( int k=0; k<nSamplesPerPixel; k++ )
  {
    double p_x = ( g_RayTracingInternalData.nextPixel_i + randomMT() ) / g_FilmWidth;
    double p_y = ( g_RayTracingInternalData.nextPixel_j + randomMT() ) / g_FilmHeight;
  
    Ray ray; ray.depth = 0;
    g_Camera.screenView( p_x, p_y, ray );
  
    RayHit ray_hit;
    rayTracing( g_Obj, ray, ray_hit );
  
    if( ray_hit.tri_idx >= 0 )
    {
      I += computeShading( ray, ray_hit, g_Obj, g_Lights );
    }
  }
  
  g_AccumulationBuffer[pixel_flat_idx*3] += I.x();
  g_AccumulationBuffer[pixel_flat_idx*3+1] += I.y();
  g_AccumulationBuffer[pixel_flat_idx*3+2] += I.z();
  g_CountBuffer[pixel_flat_idx] += nSamplesPerPixel;
}

void idle()
{
#ifdef __APPLE__
  //usleep( 1000*1000 / 60 );
  usleep( 1000 / 60 );
#else
  Sleep(1000.0/60.0);
#endif
  
  for( int i=0; i<g_FilmWidth * g_FilmHeight; i++ ) shadeNextPixel();
  updateFilm();
  
  glutPostRedisplay();
}

void mouseDrag( int x, int y )
{
  int _dx = x - mx, _dy = y - my;
  mx = x; my = y;
  
  double dx = double( _dx ) / double( width );
  double dy = - double( _dy ) / double( height );
  
  if( g_MouseMode == MM_CAMERA )
  {
    double scale = 2.0;
  
    g_Camera.rotateCameraInLocalFrameFixLookAt( dx * scale );
    resetFilm();
    updateFilm();
    glutPostRedisplay();
  }
  else if( g_MouseMode == MM_LIGHT && g_MM_LIGHT_idx < g_Lights.size() )
  {
    double scale = 1.0;
    
    g_Lights[g_MM_LIGHT_idx].pos += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
    resetFilm();
    updateFilm();
    glutPostRedisplay();
  }
}

void mouseDown( int x, int y )
{
  mx = x; my = y;
}

void mouse( int button, int state, int x, int y )
{
  if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    mouseDown( x, y );
}

void key( unsigned char key , int x , int y )
{
  switch( key )
  {
    case 'C':
    case 'c':
      g_MouseMode = MM_CAMERA;
      break;
    case '1':
    case '2':
    case '3':
      g_MouseMode = MM_LIGHT;
      g_MM_LIGHT_idx = key - '1';
      break;
    case 'f':
    case 'F':
      g_DrawFilm = !g_DrawFilm;
      glutPostRedisplay();
      break;
  }
}

void display()
{
  glViewport( 0, 0, width * g_FrameSize_WindowSize_Scale_x, height * g_FrameSize_WindowSize_Scale_y );
  
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  projection_and_modelview( g_Camera, width, height );
  
  glEnable( GL_DEPTH_TEST );
  
  drawFloor();
  
  computeGLShading( g_Obj, g_Lights );
  drawObject( g_Obj );
  
  drawLights( g_Lights );
  
  if( g_DrawFilm )
    drawFilm( g_Camera, g_FilmTexture );
  
  glDisable( GL_DEPTH_TEST );
  
  glutSwapBuffers();
}

void resize( int w, int h )
{
  width = w;
  height = h;
}

int main( int argc, char* argv[] )
{
  g_Camera.setEyePoint( Eigen::Vector3d{ 0.0, 1.0, 4.0 } );
  g_Camera.lookAt( Eigen::Vector3d{ 0.0, 0.5, 0.0 }, Eigen::Vector3d{ 0.0, 1.0, 0.0} );
  initLights();
  
  glutInit( &argc, argv );
  glutInitWindowSize( width, height );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE );
  
  glutCreateWindow( "Hello world!!" );
  
  // With retina display, frame buffer size is twice the window size.
  // Viewport size should be set on the basis of the frame buffer size, rather than the window size.
  // g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
  GLint dims[4] = {0};
  glGetIntegerv(GL_VIEWPORT, dims);
  g_FrameSize_WindowSize_Scale_x = double( dims[2] ) / double( width );
  g_FrameSize_WindowSize_Scale_y = double( dims[3] ) / double( height );
  
  glutDisplayFunc( display );
  glutIdleFunc( idle );
  glutReshapeFunc( resize );
  glutMouseFunc( mouse );
  glutMotionFunc( mouseDrag );
  glutKeyboardFunc( key );
  
  initFilm();
  clearRayTracedResult();
  loadObj( "box.obj", g_Obj );
  
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  
  glutMainLoop();
  return 0;
}
