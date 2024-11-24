#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <unistd.h>
#else
#include <GL/freeglut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include "system.h"
#include "PenaltyRigidBody2DSim.h"

#include <iostream>

System g_System;

void key( unsigned char key , int x , int y )
{
  switch( key )
  {
    case 'I':
    case 'i':
      initState( g_System );
      break;
  }
}

void mouse( int button, int state, int x, int y )
{
  //if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
  //  mouseDown( x, y );
}


void mouseDrag( int x, int y )
{
  
}

void resize( int w, int h )
{
  g_System.window_width = w;
  g_System.window_height = h;
}

void drawCircles()
{
  glBegin( GL_TRIANGLES );
  for( int j=0; j<g_System.num_bodies; j++ )
  {
    for( int i=0; i<g_System.ball_draw_segs; i++ )
    {
      int quarter = g_System.ball_draw_segs / 4;
      double b = 1.0;
      if( ( i / quarter ) % 2 == 1 ) b = 0.0;
      
      glColor3f( b, b, b );
      
      const double theta_0 = i * 2.0 * M_PI / g_System.ball_draw_segs + g_System.sim->getState().q( 3 * j + 2 );
      const double theta_1 = ( i + 1.0 ) * 2.0 * M_PI / g_System.ball_draw_segs + g_System.sim->getState().q( 3 * j + 2 );
      
      const Eigen::Vector2d x0 = g_System.sim->getState().q.segment<2>( 3 * j ) + g_System.sim->getState().r(j) * Eigen::Vector2d{ cos( theta_0 ), sin( theta_0 ) };
      const Eigen::Vector2d x1 = g_System.sim->getState().q.segment<2>( 3 * j ) + g_System.sim->getState().r(j) * Eigen::Vector2d{ cos( theta_1 ), sin( theta_1 ) };
      
      glVertex3f( x0.x(), x0.y(), 0.0 );
      glVertex3f( x1.x(), x1.y(), 0.0 );
      glVertex3f( g_System.sim->getState().q( 3 * j ), g_System.sim->getState().q( 3 * j + 1 ), 0.0 );
    }
  }
  
  glEnd();
  
  glBegin( GL_LINES );
  glColor3f( 0.0, 0.0, 0.0 );
  for( int j=0; j<g_System.num_bodies; j++ )
  {
    for( int i=0; i<g_System.ball_draw_segs; i++ )
    {
      const double theta_0 = i * 2.0 * M_PI / g_System.ball_draw_segs + g_System.sim->getState().q( 3 * j + 2 );
      const double theta_1 = ( i + 1.0 ) * 2.0 * M_PI / g_System.ball_draw_segs + g_System.sim->getState().q( 3 * j + 2 );
      
      const Eigen::Vector2d x0 = g_System.sim->getState().q.segment<2>( 3 * j ) + g_System.sim->getState().r(j) * Eigen::Vector2d{ cos( theta_0 ), sin( theta_0 ) };
      const Eigen::Vector2d x1 = g_System.sim->getState().q.segment<2>( 3 * j ) + g_System.sim->getState().r(j) * Eigen::Vector2d{ cos( theta_1 ), sin( theta_1 ) };
      
      glVertex3f( x0.x(), x0.y(), 0.0 );
      glVertex3f( x1.x(), x1.y(), 0.0 );
    }
  }
  glEnd();
}

void display()
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
  glViewport( 0, 0, g_System.window_width * g_System.frame_window_size_scale_x, g_System.window_height * g_System.frame_window_size_scale_y );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  double ratio = double( g_System.window_width ) / double( g_System.window_height );
  glOrtho( -ratio, ratio, -1.0, 1.0, -1.0, 1.0 );
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  drawCircles();
  
  glutSwapBuffers();
}

void idle()
{
  for( int i=0; i<30; i++ )
  {
    g_System.sim->step();
  }
  glutPostRedisplay();
}

int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  
  initSystem( g_System );
  
  g_System.window_width = 512;
  g_System.window_height = 512;
  
  glutInitWindowSize( g_System.window_width, g_System.window_height );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  
  glutCreateWindow( "Penalty based rigid body simulation (2D)" );
  
  // With retina display, frame buffer size is twice the window size.
  // Viewport size should be set on the basis of the frame buffer size, rather than the window size.
  // g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
  GLint dims[4] = {0};
  glGetIntegerv(GL_VIEWPORT, dims);
  g_System.frame_window_size_scale_x = double( dims[2] ) / double( g_System.window_width );
  g_System.frame_window_size_scale_y = double( dims[3] ) / double( g_System.window_height );

  glutDisplayFunc( display );
  glutIdleFunc( idle );
  glutReshapeFunc( resize );
  glutMouseFunc( mouse );
  glutMotionFunc( mouseDrag );
  glutKeyboardFunc( key );
  
  glutMainLoop();
  
  return 0;
}
