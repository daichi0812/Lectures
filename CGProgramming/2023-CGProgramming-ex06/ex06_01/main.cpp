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
#include "TriMesh.h"

enum MouseMode
{
  MM_CAMERA,
  MM_LIGHT1,
  MM_LIGHT2,
  MM_LIGHT3
};

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

void updateLightPosition( Eigen::Vector3d& pos, const double dtheta, const double dt )
{
  const double l = ( pos - Eigen::Vector3d{ 0.0, pos.y(), 0.0 } ).norm();
  double theta = atan2( pos.x(), pos.z() ) + dtheta * dt;
  
  pos << l * sin( theta ), pos.y(), l * cos( theta );
}

void updateLightPositions( const double dt )
{
  updateLightPosition( g_PointLightPos1, g_dtheta1, dt );
  updateLightPosition( g_PointLightPos2, g_dtheta2, dt );
  updateLightPosition( g_PointLightPos3, g_dtheta3, dt );
}

void idle()
{
#ifdef __APPLE__
  usleep( 1000*1000 / 60 );
#else
  Sleep(1000.0/60.0);
#endif
  updateLightPositions( 1.0 / 60.0 );
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
  
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );
  glEnable( GL_POINT_SMOOTH );
  glEnable( GL_LINE_SMOOTH );
  glEnable( GL_POLYGON_SMOOTH);
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
  glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
  
  drawFloor();
  
  computeShading( g_Obj );
  drawObject( g_Obj );
  
  drawLights();
  
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
  
  loadObj( "apple.obj", g_Obj );
  //loadObj( "AppleStrudel.obj", g_Obj );
  //loadObj( "Stump.obj", g_Obj );
  
  resizeObj( g_Obj, { -1.0, 0.0, -1.0 }, { 1.0, 1.0, 1.0 } );
  
  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  
  glutMainLoop();
  return 0;
}
