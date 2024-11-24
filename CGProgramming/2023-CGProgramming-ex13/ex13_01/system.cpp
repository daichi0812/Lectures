//
//  system.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>

#include "system.h"
#include "random.h"

#include <iostream>

void initSetting( System& io_System, DEMSettings& io_DEMSettings )
{
  // timestep
  io_DEMSettings.dt = 0.003;
  // gravitational acceleration
  io_DEMSettings.g << 0.0, -0.0981;
  // parameters for penalty based
  io_DEMSettings.kn = 50000.0;
  io_DEMSettings.gamman = 1000.0;
  io_DEMSettings.kt = 50000.0;
  io_DEMSettings.gammat = 100.0;
  io_DEMSettings.mu = 1.0;
  
  // number of segments per each ball (used for rendering)
  io_System.ball_draw_segs = 20;
  
  // ball density
  io_System.rho = 1000.0;
  // average radius
  io_System.r_avr = 0.07;
  // radius deviation
  io_System.r_dev = 0.04;
  // number of balls (4 fixed balls for walls, and 64 dynamic balls)
  io_System.num_bodies = 4 + 64;
}

void initState( System& io_System )
{
  RigidBody2DState state;
  
  state.q.setZero( 3 * io_System.num_bodies );
  state.v.setZero( 3 * io_System.num_bodies );
  state.r.setZero( io_System.num_bodies );
  state.F.setZero( 3 * io_System.num_bodies );
  state.M.setZero( 3 * io_System.num_bodies );
  state.Minv.setZero( 3 * io_System.num_bodies );
  
  state.fixed.resize( io_System.num_bodies );
  for( int i=0; i<io_System.num_bodies; i++ )
  {
    state.fixed[i] = false;
  }
  
  // Add four fixed boundary geometries
  const double size = 200.0;
  
  state.q.segment<3>(0) = Eigen::Vector3d { -1.0 - size, 0.0, 0.0 };
  state.r(0) = size;
  state.fixed[0] = true;
  
  state.q.segment<3>(3) = Eigen::Vector3d { 1.0 + size, 0.0, 0.0 };
  state.r(1) = size;
  state.fixed[1] = true;
  
  state.q.segment<3>(6) = Eigen::Vector3d { 0.0, -1.0 - size, 0.0 };
  state.r(2) = size;
  state.fixed[2] = true;
  
  state.q.segment<3>(9) = Eigen::Vector3d { 0.0, 1.0 + size, 0.0 };
  state.r(3) = size;
  state.fixed[3] = true;
  
  // For simple test of two balls
  /*
  io_System.state.r(4) = 0.1;
  io_System.state.r(5) = 0.1;
  //*/
  
  /*
  io_System.state.q.segment<3>(12) = Eigen::Vector3d {  0.5,  0.05, 0.0 };
  io_System.state.q.segment<3>(15) = Eigen::Vector3d { -0.5, -0.05, 0.0 };
  io_System.state.v.segment<3>(12) = Eigen::Vector3d { -0.02,  0.0, 0.0 };
  io_System.state.v.segment<3>(15) = Eigen::Vector3d {  0.02,  0.0, 0.0 };
  //*/
  
  /*
  io_System.state.q.segment<3>(12) = Eigen::Vector3d {  0.5,  0.0, 0.0 };
  io_System.state.q.segment<3>(15) = Eigen::Vector3d { -0.5,  0.0, 0.0 };
  io_System.state.v.segment<3>(12) = Eigen::Vector3d { -0.02,  0.0, 0.0 };
  io_System.state.v.segment<3>(15) = Eigen::Vector3d {  0.02,  0.0, 0.0 };
  //*/
  
  /*
  io_System.state.q.segment<3>(12) = Eigen::Vector3d {  0.5,  0.095, 0.0 };
  io_System.state.q.segment<3>(15) = Eigen::Vector3d { -0.5, -0.095, 0.0 };
  io_System.state.v.segment<3>(12) = Eigen::Vector3d { -0.02,   0.0, 0.0 };
  io_System.state.v.segment<3>(15) = Eigen::Vector3d {  0.02,   0.0, 0.0 };
  //*/
  
  /*
  io_System.state.q.segment<3>(12) = Eigen::Vector3d {  0.5,  0.095, 0.0 };
  io_System.state.q.segment<3>(15) = Eigen::Vector3d {  0.0, -0.095, 0.0 };
  io_System.state.v.segment<3>(12) = Eigen::Vector3d { -0.02,   0.0, 0.0 };
  io_System.state.v.segment<3>(15) = Eigen::Vector3d {  0.0,    0.0, 0.0 };
  //*/
  
  /*
  io_System.state.q.segment<3>(12) = Eigen::Vector3d {  0.0,  0.09, 0.0 };
  io_System.state.q.segment<3>(15) = Eigen::Vector3d { -0.5, -0.09, 0.0 };
  io_System.state.v.segment<3>(12) = Eigen::Vector3d {  0.0,    0.0, 0.0 };
  io_System.state.v.segment<3>(15) = Eigen::Vector3d { 0.02,    0.0, 0.0 };
  //*/
  
  //*
  for( int i=4; i<io_System.num_bodies; i++ )
  {
    state.r(i) = io_System.r_avr + ( randomMT() * 2.0 - 1.0 ) * io_System.r_dev;
    
    state.q.segment<3>( 3 * i ) << ( randomMT() * 2.0 - 1.0 ) * ( 1.0 - state.r(i) ), ( randomMT() * 2.0 - 1.0 ) * ( 1.0 - state.r(i) ) , randomMT() * 2.0 * M_PI;
    state.v.segment<3>( 3 * i ) << ( randomMT() * 2.0 - 1.0 ) * 0.01, ( randomMT() * 2.0 - 1.0 ) * 0.01, ( randomMT() * 2.0 - 1.0 ) * 10.0 * M_PI;
    
    state.fixed[i] = false;
    
  }
  //*/
  
  for( int i=0; i<io_System.num_bodies; i++ )
  {
    const double r { state.r(i) };
    const double m = io_System.rho * M_PI * r * r;
    const double I = 0.5 * m * r * r;
    state.M.segment<3>( 3 * i ) << m, m, I;
    state.Minv.segment<3>( 3 * i ) << 1.0 / m, 1.0 / m, 1.0 / I;
  }
  
  io_System.sim->setInitialState( state );
}

void initSystem( System& io_System )
{
  DEMSettings dem_settings;
  initSetting( io_System, dem_settings );
  io_System.sim = new PenaltyRigidBody2DSim( dem_settings );
  
  initState( io_System );
}

