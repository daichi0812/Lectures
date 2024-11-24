//
//  main.cpp
//  Bezier_for_class
//
//  Created by Yonghao Yue on 2021/01/12.
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
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>
#include <iostream>

#include "bezier.h"

struct System
{
  int window_width;
  int window_height;
  double frame_window_size_scale_x;
  double frame_window_size_scale_y;
  int selected_curve_idx;
  int selected_handle_idx;
  double handle_size;
  int mx, my;
};

std::vector<CubicBezier> g_Curve;
System g_System;


void initSystem( System& io_System )
{
  io_System.window_width = 512;
  io_System.window_height = 512;
  io_System.frame_window_size_scale_x = 1.0;
  io_System.frame_window_size_scale_y = 1.0;

  io_System.mx = io_System.my = 0;
  
  io_System.handle_size = 0.02;
  io_System.selected_curve_idx = -1;
  io_System.selected_handle_idx = -1;
  
  CubicBezier bezier;
  bezier.P[0] << 0.2, 0.2;
  bezier.P[1] << 0.3, 0.5;
  bezier.P[2] << 0.7, 0.5;
  bezier.P[3] << 0.8, 0.8;
  
  g_Curve.push_back( bezier );
}

bool withinHandleRegion( const Eigen::Vector4d& in_Handle_Region, const Eigen::Vector2d& in_p )
{
  return in_Handle_Region(0) <= in_p.x() && in_p.x() <= in_Handle_Region(2) && in_Handle_Region(1) <= in_p.y() && in_p.y() <= in_Handle_Region(3);
}

Eigen::Vector4d getHandleRegion( const Eigen::Vector2d& p )
{
  return Eigen::Vector4d { p.x() - 0.5 * g_System.handle_size, p.y() - 0.5 * g_System.handle_size, p.x() + 0.5 * g_System.handle_size, p.y() + 0.5 * g_System.handle_size };
}

Eigen::Vector4d getHandleRegion( int segment_idx, int cp_idx )
{
  return getHandleRegion( g_Curve[segment_idx].P[cp_idx] );
}

void drawHandle( const Eigen::Vector2d& p )
{
  glBegin( GL_LINE_LOOP );
    
  const Eigen::Vector4d handle_region = getHandleRegion( p );
    
  glVertex2d( handle_region(0), handle_region(1) );
  glVertex2d( handle_region(2), handle_region(1) );
  glVertex2d( handle_region(2), handle_region(3) );
  glVertex2d( handle_region(0), handle_region(3) );
      
  glEnd();
}

void drawBezierHandle( const int in_Segment_Idx )
{
  glLineWidth( 2.0 );
  
  for( int i=0; i<4; i++ )
  {
    if( g_System.selected_curve_idx == in_Segment_Idx && g_System.selected_handle_idx == i )
      glColor3f( 0.8, 0.3, 0.3 );
    else
      glColor3f( 0.0, 0.0, 0.0 );
    
    drawHandle( g_Curve[in_Segment_Idx].P[i] );
  }
  
  glColor3f( 0.0, 0.0, 0.0 );
  
  for( int i=0; i<2; i++ )
  {
    glBegin( GL_LINES );
    
    glVertex2d( g_Curve[in_Segment_Idx].P[i*2].x(), g_Curve[in_Segment_Idx].P[i*2].y() );
    glVertex2d( g_Curve[in_Segment_Idx].P[i*2+1].x(), g_Curve[in_Segment_Idx].P[i*2+1].y() );
    
    glEnd();
  }
}

void drawBezierSegment( const CubicBezier& in_Bezier )
{
  Eigen::Vector2d min_C = in_Bezier.P[0].cwiseMin( in_Bezier.P[1] ).cwiseMin( in_Bezier.P[2].cwiseMin( in_Bezier.P[3] ) );
  Eigen::Vector2d max_C = in_Bezier.P[0].cwiseMax( in_Bezier.P[1] ).cwiseMax( in_Bezier.P[2].cwiseMax( in_Bezier.P[3] ) );
  
  const int w = 2 * g_System.window_width * ( max_C.x() - min_C.x() );
  const int h = 2 * g_System.window_width * ( max_C.y() - min_C.y() );
  const int nSteps = std::max<int>( w, h );
  
  glLineWidth( 3.0 );
  glColor3d( 0.3, 0.3, 0.8 );
  glBegin( GL_LINE_STRIP );
  
  for( int i=0; i<=nSteps; i++ )
  {
    const double t = double( i ) / double( nSteps );
    Eigen::Vector2d pt = evaluateCubicBezier( in_Bezier, t );
    glVertex2d( pt.x(), pt.y() );
  }
  
  glEnd();
}

void drawBezierCurve()
{
  for( int i=0; i<g_Curve.size(); i++ )
  {
    drawBezierSegment( g_Curve[i] );
    drawBezierHandle( i );
  }
}

void display()
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
  glViewport( 0, 0, g_System.window_width * g_System.frame_window_size_scale_x, g_System.window_height * g_System.frame_window_size_scale_y );
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  double ratio = double( g_System.window_width ) / double( g_System.window_height );
  glOrtho( 0.0, ratio, 0.0, 1.0, -1.0, 1.0 );
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  drawBezierCurve();
  
  glutSwapBuffers();
}

void mouse( int button, int state, int x, int y )
{
  g_System.selected_curve_idx = -1;
  g_System.selected_handle_idx = -1;
  
  if( button == GLUT_LEFT_BUTTON && ( state == GLUT_DOWN || state == GLUT_UP ) )
  {
    const double _x = double( x ) / double( g_System.window_height );
    const double _y = double( g_System.window_height - y ) / double( g_System.window_height );
    
    for( int j=0; j<g_Curve.size(); j++ )
    {
      for( int i=0; i<4; i++ )
      {
        if( withinHandleRegion( getHandleRegion( j, i ), Eigen::Vector2d{ _x, _y } ) )
        {
          g_System.selected_curve_idx = j;
          g_System.selected_handle_idx = i;
        }
      }
    }

    glutPostRedisplay();
  }
  
  g_System.mx = x;
  g_System.my = y;
}

void mouseDrag( int x, int y )
{
  double dx = double( x - g_System.mx ) / double( g_System.window_height );
  double dy = double( g_System.my - y ) / double( g_System.window_height );
  
  Eigen::Vector2d d{ dx, dy };
    
  if( g_System.selected_curve_idx >= 0 && g_System.selected_handle_idx >= 0 )
  {
    if( g_System.selected_handle_idx == 0 )
    {
      g_Curve[g_System.selected_curve_idx].P[0] += d;
      g_Curve[g_System.selected_curve_idx].P[1] += d;
      
      if( g_System.selected_curve_idx >= 1 )
      {
        g_Curve[g_System.selected_curve_idx-1].P[2] += d;
        g_Curve[g_System.selected_curve_idx-1].P[3] += d;
      }
    }
    else if( g_System.selected_handle_idx == 1 )
    {
      g_Curve[g_System.selected_curve_idx].P[1] += d;
        
      if( g_System.selected_curve_idx >= 1 )
      {
        Eigen::Vector2d d01 = g_Curve[g_System.selected_curve_idx].P[1] - g_Curve[g_System.selected_curve_idx].P[0];
        d01.normalize();
        
        const double l = ( g_Curve[g_System.selected_curve_idx-1].P[3] - g_Curve[g_System.selected_curve_idx-1].P[2] ).norm();
        
        g_Curve[g_System.selected_curve_idx-1].P[2] = g_Curve[g_System.selected_curve_idx-1].P[3] - d01 * l;
      }
    }
    else if( g_System.selected_handle_idx == 2 )
    {
      g_Curve[g_System.selected_curve_idx].P[2] += d;
        
      if( g_System.selected_curve_idx < g_Curve.size() - 1 )
      {
        Eigen::Vector2d d32 = g_Curve[g_System.selected_curve_idx].P[2] - g_Curve[g_System.selected_curve_idx].P[3];
        d32.normalize();
        
        const double l = ( g_Curve[g_System.selected_curve_idx+1].P[1] - g_Curve[g_System.selected_curve_idx+1].P[0] ).norm();
        
        g_Curve[g_System.selected_curve_idx+1].P[1] = g_Curve[g_System.selected_curve_idx+1].P[0] - d32 * l;
      }
    }
    else if( g_System.selected_handle_idx == 3 )
    {
      g_Curve[g_System.selected_curve_idx].P[2] += d;
      g_Curve[g_System.selected_curve_idx].P[3] += d;
        
      if( g_System.selected_curve_idx < g_Curve.size() - 1 )
      {
        g_Curve[g_System.selected_curve_idx+1].P[0] += d;
        g_Curve[g_System.selected_curve_idx+1].P[1] += d;
      }
    }
    
    glutPostRedisplay();
  }
  
  g_System.mx = x;
  g_System.my = y;
}

void key( unsigned char key , int x , int y )
{
  switch( key )
  {
    case 's':
    case 'S':
      const size_t nSegs = g_Curve.size();
      //const int _i = randomMT_i();
      //const int i = _i % nSegs;
      //const double t = randomMT() * 0.8 + 0.1;
      const size_t i = nSegs - 1;
      const double t = 0.7;
      
      CubicBezier C1, C2;
      splitCurve( g_Curve[i], t, C1, C2 );
      g_Curve[i] = C1;
      g_Curve.push_back( C2 );
      glutPostRedisplay();
      break;
  }
}

void resize( int w, int h )
{
  g_System.window_width = w;
  g_System.window_height = h;
}

void idle()
{
  glutPostRedisplay();
}

int main( int argc, char* argv[] )
{
  glutInit( &argc, argv );
  
  initSystem( g_System );
  
  glutInitWindowSize( g_System.window_width, g_System.window_height );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE );
  
  glutCreateWindow( "2D Bezier Test" );

  // With retina display, frame buffer size is twice the window size.
  // Viewport size should be set on the basis of the frame buffer size, rather than the window size.
  // g_FrameSize_WindowSize_Scale_x and g_FrameSize_WindowSize_Scale_y account for this factor.
  GLint dims[4] = {0};
  glGetIntegerv( GL_VIEWPORT, dims );
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
