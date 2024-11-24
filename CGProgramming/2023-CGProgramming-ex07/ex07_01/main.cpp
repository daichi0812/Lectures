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

enum MouseMode
{
  MM_CAMERA,
  MM_LIGHT1,
  MM_LIGHT2,
  MM_LIGHT3
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
};

const double __FAR__ = 1.0e33;

const int g_FilmWidth = 640;
const int g_FilmHeight = 480;
float* g_FilmBuffer = nullptr; 
GLuint g_FilmTexture = 0;

RayTracingInternalData g_RayTracingInternalData;

bool g_DrawFilm = true;

int width = 640;
int height = 480;

MouseMode g_MouseMode = MM_CAMERA;
int mx, my;

double g_FrameSize_WindowSize_Scale_x = 1.0;
double g_FrameSize_WindowSize_Scale_y = 1.0;

Camera g_Camera;

Eigen::Vector3d g_PointLightPos1 { -1.2, 1.2, 1.2 };
Eigen::Vector3d g_PointLightColor1 { 1.0, 0.8, 0.3 };
double g_LightIntensity1 = 2.0;
double g_dtheta1 = 3.0;

Eigen::Vector3d g_PointLightPos2 { 1.2, 1.2, 0.0 };
Eigen::Vector3d g_PointLightColor2 { 0.3, 0.3, 1.0 };
double g_LightIntensity2 = 2.0;
double g_dtheta2 = 4.5;

Eigen::Vector3d g_PointLightPos3 { 0.0, 1.2, -1.2 };
Eigen::Vector3d g_PointLightColor3 { 1.0, 0.4, 0.8 };
double g_LightIntensity3 = 1.0;
double g_dtheta3 = 3.9;

Object g_Obj;

void initFilm()
{   
  g_FilmBuffer = (float*)malloc( sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
  memset( g_FilmBuffer, 0, sizeof(float) * g_FilmWidth * g_FilmHeight * 3 );
  
  glGenTextures( 1, &g_FilmTexture );
  glBindTexture( GL_TEXTURE_2D, g_FilmTexture );
  
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, g_FilmWidth, g_FilmHeight, 0, GL_RGB, GL_FLOAT, g_FilmBuffer );
  
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}

void updateFilm()
{
  glBindTexture( GL_TEXTURE_2D, g_FilmTexture );
  glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, g_FilmWidth, g_FilmHeight, GL_RGB, GL_FLOAT, g_FilmBuffer);
}

void drawFilm()
{
  Eigen::Vector3d screen_center = g_Camera.getEyePoint() - g_Camera.getZVector() * g_Camera.getFocalLength();
  Eigen::Vector3d p1 = screen_center - g_Camera.getXVector() * g_Camera.getScreenWidth() * 0.5 - g_Camera.getYVector() * g_Camera.getScreenHeight() * 0.5;
  Eigen::Vector3d p2 = screen_center + g_Camera.getXVector() * g_Camera.getScreenWidth() * 0.5 - g_Camera.getYVector() * g_Camera.getScreenHeight() * 0.5;
  Eigen::Vector3d p3 = screen_center + g_Camera.getXVector() * g_Camera.getScreenWidth() * 0.5 + g_Camera.getYVector() * g_Camera.getScreenHeight() * 0.5;
  Eigen::Vector3d p4 = screen_center - g_Camera.getXVector() * g_Camera.getScreenWidth() * 0.5 + g_Camera.getYVector() * g_Camera.getScreenHeight() * 0.5;
  
  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, g_FilmTexture );
  
  glBegin( GL_TRIANGLES );
  glColor3f( 1.0, 1.0, 1.0 );
  
  glTexCoord2f( 0.0, 1.0 );
  glVertex3f( p1.x(), p1.y(), p1.z() );
  glTexCoord2f( 1.0, 1.0 );
  glVertex3f( p2.x(), p2.y(), p2.z() );
  glTexCoord2f( 1.0, 0.0 );
  glVertex3f( p3.x(), p3.y(), p3.z() );
  
  glTexCoord2f( 0.0, 1.0 );
  glVertex3f( p1.x(), p1.y(), p1.z() );
  glTexCoord2f( 1.0, 0.0 );
  glVertex3f( p3.x(), p3.y(), p3.z() );
  glTexCoord2f( 0.0, 0.0 );
  glVertex3f( p4.x(), p4.y(), p4.z() );
  
  glEnd();
  
  glDisable( GL_TEXTURE_2D );
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
  
  Eigen::Vector3d N = (v1 - v3).cross(v2 - v3);
  N.normalize();

  if (N.dot(in_Ray.d) >= 0) {
      return;
  }

  double _t = (N.dot(v3 - in_Ray.o)) / (N.dot(in_Ray.d));

  if (_t <= 0) {       
      return;
  }

  Eigen::Vector3d x = in_Ray.o + _t * in_Ray.d;

  Eigen::Matrix<double, 3, 2> A;
 
  A.col(0) = v1 - v3;
  A.col(1) = v2 - v3;

  Eigen::Vector2d y = (A.transpose() * A).inverse() * A.transpose() * (x - v3);
  
  if (0 <= y(0) && y(0) <= 1.0 && 0 <= y(1) && y(1) <= 1.0 && 0 <= (1 - y(0) - y(1)) && (1 - y(0) - y(1)) <= 1.0) {
      out_Result.t = _t;
      out_Result.alpha = y(0);
      out_Result.beta = y(1);
  }
  return;
}

void rayTracing( const Ray& in_Ray, RayHit& io_Hit )
{
  double t_min = __FAR__;
  double alpha_I = 0.0, beta_I = 0.0;
  int mesh_idx = -1; int tri_idx = -1;
  
  for( int m=0; m<g_Obj.meshes.size(); m++ )
  {
    for( int k=0; k<g_Obj.meshes[m].triangles.size(); k++ )
    {   
        RayHit t_Hit;
        rayTriangleIntersect(g_Obj.meshes[m], k, in_Ray, t_Hit);

        if (t_Hit.t == __FAR__ || t_min < t_Hit.t) {
            continue;
        }

        t_min = t_Hit.t;
        alpha_I = t_Hit.alpha;
        beta_I = t_Hit.beta;
        mesh_idx = m;
        tri_idx = k;
    }
  }
  
  io_Hit.t = t_min;
  io_Hit.alpha = alpha_I;
  io_Hit.beta = beta_I;
  io_Hit.mesh_idx = mesh_idx;
  io_Hit.tri_idx = tri_idx;
}

void shadeNextPixel()
{
  stepToNextPixel( g_RayTracingInternalData );
  
  const int pixel_flat_idx = g_RayTracingInternalData.nextPixel_j * g_FilmWidth + g_RayTracingInternalData.nextPixel_i;

  double p_x = ( g_RayTracingInternalData.nextPixel_i + 0.5 ) / g_FilmWidth;
  double p_y = ( g_RayTracingInternalData.nextPixel_j + 0.5 ) / g_FilmHeight;
  
  Ray ray;
  g_Camera.screenView( p_x, p_y, ray );
  
  RayHit ray_hit;
  rayTracing( ray, ray_hit );
  
  if( ray_hit.tri_idx >= 0 )
  {
    const Eigen::Vector3d x = ray.o + ray_hit.t * ray.d;
    const int v1_idx = g_Obj.meshes[ray_hit.mesh_idx].triangles[ray_hit.tri_idx](0);
    const int v2_idx = g_Obj.meshes[ray_hit.mesh_idx].triangles[ray_hit.tri_idx](1);
    const int v3_idx = g_Obj.meshes[ray_hit.mesh_idx].triangles[ray_hit.tri_idx](2);
    
    const Eigen::Vector3d v1 = g_Obj.meshes[ray_hit.mesh_idx].vertices[v1_idx];
    const Eigen::Vector3d v2 = g_Obj.meshes[ray_hit.mesh_idx].vertices[v2_idx];
    const Eigen::Vector3d v3 = g_Obj.meshes[ray_hit.mesh_idx].vertices[v3_idx];
    
    const Eigen::Vector3d n1 = g_Obj.meshes[ray_hit.mesh_idx].vertex_normals[v1_idx];
    const Eigen::Vector3d n2 = g_Obj.meshes[ray_hit.mesh_idx].vertex_normals[v2_idx];
    const Eigen::Vector3d n3 = g_Obj.meshes[ray_hit.mesh_idx].vertex_normals[v3_idx];
    
    const double gamma = 1.0 - ray_hit.alpha - ray_hit.beta;
    Eigen::Vector3d n = ray_hit.alpha * n1 + ray_hit.beta * n2 + gamma * n3;
    n.normalize();
    
    Eigen::Vector3d L1 = g_PointLightPos1 - x;
    const double dist1 = L1.norm();
    L1.normalize();
    const double cos_theta1 = std::max<double>( 0.0, L1.dot( n ) );
    
    Eigen::Vector3d L2 = g_PointLightPos2 - x;
    const double dist2 = L2.norm();
    L2.normalize();
    const double cos_theta2 = std::max<double>( 0.0, L2.dot( n ) );
    
    Eigen::Vector3d L3 = g_PointLightPos3 - x;
    const double dist3 = L3.norm();
    L3.normalize();
    const double cos_theta3 = std::max<double>( 0.0, L3.dot( n ) );
    
    const Eigen::Vector3d kd = g_Obj.meshes[ray_hit.mesh_idx].kd;
    const Eigen::Vector3d I = g_PointLightColor1.cwiseProduct( kd ) * g_LightIntensity1 * cos_theta1 / ( dist1 * dist1 ) + g_PointLightColor2.cwiseProduct( kd ) * g_LightIntensity2 * cos_theta2 / ( dist2 * dist2 ) + g_PointLightColor3.cwiseProduct( kd ) * g_LightIntensity3 * cos_theta3 / ( dist3 * dist3 );
    
    g_FilmBuffer[pixel_flat_idx*3] = I.x();
    g_FilmBuffer[pixel_flat_idx*3+1] = I.y();
    g_FilmBuffer[pixel_flat_idx*3+2] = I.z();
  }
  else
  {
    g_FilmBuffer[pixel_flat_idx*3] = 1.0;
    g_FilmBuffer[pixel_flat_idx*3+1] = 1.0;
    g_FilmBuffer[pixel_flat_idx*3+2] = 1.0;
  }
}

void computeShading( TriMesh& io_Mesh )
{
  for( int i=0; i<io_Mesh.vertices.size(); i++ )
  {
    Eigen::Vector3d p = io_Mesh.vertices[i];
    Eigen::Vector3d n = io_Mesh.vertex_normals[i];
    
    Eigen::Vector3d L1 = g_PointLightPos1 - p;
    const double dist1 = L1.norm();
    L1.normalize();
    const double cos_theta1 = std::max<double>( 0.0, L1.dot( n ) );
    
    Eigen::Vector3d L2 = g_PointLightPos2 - p;
    const double dist2 = L2.norm();
    L2.normalize();
    const double cos_theta2 = std::max<double>( 0.0, L2.dot( n ) );
    
    Eigen::Vector3d L3 = g_PointLightPos3 - p;
    const double dist3 = L3.norm();
    L3.normalize();
    const double cos_theta3 = std::max<double>( 0.0, L3.dot( n ) );
    
    const Eigen::Vector3d I = g_PointLightColor1.cwiseProduct( io_Mesh.kd ) * g_LightIntensity1 * cos_theta1 / ( dist1 * dist1 ) + g_PointLightColor2.cwiseProduct( io_Mesh.kd ) * g_LightIntensity2 * cos_theta2 / ( dist2 * dist2 ) + g_PointLightColor3.cwiseProduct( io_Mesh.kd ) * g_LightIntensity3 * cos_theta3 / ( dist3 * dist3 );
    
    io_Mesh.vertex_colors[i] = I;
  }
}

void computeShading( Object& io_Object )
{
  for( int i=0; i<io_Object.meshes.size(); i++ )
  {
    computeShading( io_Object.meshes[i] );
  }
}

void drawMesh( const TriMesh& in_Mesh )
{
  if( in_Mesh.texture != 0 )
  {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, in_Mesh.texture );
  }
  
  glBegin( GL_TRIANGLES );
  
  for( int j=0; j<in_Mesh.triangles.size(); j++ )
  {
    for( int i=0; i<3; i++ )
    {
      const int vid = in_Mesh.triangles[j](i);
      glColor3d( in_Mesh.vertex_colors[vid].x(), in_Mesh.vertex_colors[vid].y(), in_Mesh.vertex_colors[vid].z() );
      glTexCoord2d( in_Mesh.tex_coords[vid].x() , in_Mesh.tex_coords[vid].y() );
      glVertex3d( in_Mesh.vertices[vid].x(), in_Mesh.vertices[vid].y(), in_Mesh.vertices[vid].z() );
    }
  }
  
  glEnd();
  
  if( in_Mesh.texture != 0 )
  {
    glDisable( GL_TEXTURE_2D );
  }
}

void drawObject( const Object& in_Object )
{
  for( int i=0; i<in_Object.meshes.size(); i++ )
    drawMesh( in_Object.meshes[i] );
}

void drawLight( const Eigen::Vector3d& pos, const Eigen::Vector3d& color )
{
  const double size = 0.05;
  glBegin( GL_TRIANGLES );
  
  glColor3f( color.x(), color.y(), color.z() );
  glVertex3f( pos.x(), pos.y() + size, pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() + size );
  glVertex3f( pos.x() + size, pos.y(), pos.z() );
  
  glVertex3f( pos.x(), pos.y() + size, pos.z() );
  glVertex3f( pos.x() + size, pos.y(), pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() - size );
  
  glVertex3f( pos.x(), pos.y() + size, pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() - size );
  glVertex3f( pos.x() - size, pos.y(), pos.z() );
  
  glVertex3f( pos.x(), pos.y() + size, pos.z() );
  glVertex3f( pos.x() - size, pos.y(), pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() + size );
  
  glVertex3f( pos.x(), pos.y() - size, pos.z() );
  glVertex3f( pos.x() + size, pos.y(), pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() + size );
  
  glVertex3f( pos.x(), pos.y() - size, pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() - size );
  glVertex3f( pos.x() + size, pos.y(), pos.z() );
  
  glVertex3f( pos.x(), pos.y() - size, pos.z() );
  glVertex3f( pos.x() - size, pos.y(), pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() - size );
  
  glVertex3f( pos.x(), pos.y() - size, pos.z() );
  glVertex3f( pos.x(), pos.y(), pos.z() + size );
  glVertex3f( pos.x() - size, pos.y(), pos.z() );
  
  glEnd();
}

void drawLights()
{
  drawLight( g_PointLightPos1, g_PointLightColor1 );
  drawLight( g_PointLightPos2, g_PointLightColor2 );
  drawLight( g_PointLightPos3, g_PointLightColor3 );
}

void idle()
{
#ifdef __APPLE__
  usleep( 1000*1000 / 60 );
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
    glutPostRedisplay();
  }
  else if( g_MouseMode == MM_LIGHT1 )
  {
    double scale = 1.0;
    
    g_PointLightPos1 += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
    glutPostRedisplay();
  }
  else if( g_MouseMode == MM_LIGHT2 )
  {
    double scale = 1.0;
    
    g_PointLightPos2 += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
    glutPostRedisplay();
  }
  else if( g_MouseMode == MM_LIGHT3 )
  {
    double scale = 1.0;
    
    g_PointLightPos3 += dx * scale * g_Camera.getXVector() + dy * scale * g_Camera.getYVector();
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
      g_MouseMode = MM_LIGHT1;
      break;
    case '2':
      g_MouseMode = MM_LIGHT2;
      break;
    case '3':
      g_MouseMode = MM_LIGHT3;
      break;
    case 'f':
    case 'F':
      g_DrawFilm = !g_DrawFilm;
      glutPostRedisplay();
      break;
  }
}

void projection_and_modelview( const Camera& in_Camera )
{
  const double fovy_deg = ( 2.0 * 180.0 / M_PI ) * atan( 0.024 * 0.5 / in_Camera.getFocalLength() );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fovy_deg, double( width ) / double( height ), 0.01 * in_Camera.getFocalLength(), 1000.0 );
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  const Eigen::Vector3d lookAtPoint = in_Camera.getLookAtPoint();
  gluLookAt( in_Camera.getEyePoint().x(), in_Camera.getEyePoint().y(), in_Camera.getEyePoint().z(), lookAtPoint.x(), lookAtPoint.y(), lookAtPoint.z(), in_Camera.getYVector().x(), in_Camera.getYVector().y(), in_Camera.getYVector().z() );
}

void drawFloor()
{
  glBegin( GL_TRIANGLES );
  for( int j=-20; j<20; j++ )
  {
    for( int i=-20; i<20; i++ )
    {
      int checker_bw = ( i+j ) % 2;
      if( checker_bw == 0 )
      {
        glColor3f( 0.3, 0.3, 0.3 );

        glVertex3f( i*0.5, 0.0, j*0.5 );
        glVertex3f( i*0.5, 0.0, (j+1)*0.5 );
        glVertex3f( (i+1)*0.5, 0.0, j*0.5 );
        
        glVertex3f( i*0.5, 0.0, (j+1)*0.5 );
        glVertex3f( (i+1)*0.5, 0.0, (j+1)*0.5 );
        glVertex3f( (i+1)*0.5, 0.0, j*0.5 );
      }
    }
  }
  glEnd();
}

void display()
{
  glViewport( 0, 0, width * g_FrameSize_WindowSize_Scale_x, height * g_FrameSize_WindowSize_Scale_y );
  
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  projection_and_modelview( g_Camera );
  
  glEnable( GL_DEPTH_TEST );
  
  drawFloor();
  
  computeShading( g_Obj );
  drawObject( g_Obj );
  
  drawLights();
  
  if( g_DrawFilm )
    drawFilm();
  
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
