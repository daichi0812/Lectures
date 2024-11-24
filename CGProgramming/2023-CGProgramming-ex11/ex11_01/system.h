//
//  system.h
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef system_h
#define system_h

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include <Eigen/Core>
#include <Eigen/Dense>

#include <set>
#include <map>
#include <vector>

#include "PenaltyRigidBody2DSim.h"

struct System
{
  int window_width;
  int window_height;
  double frame_window_size_scale_x;
  double frame_window_size_scale_y;
  
  int num_bodies;
  int ball_draw_segs;
  double rho;
  double r_avr;
  double r_dev;

  PenaltyRigidBody2DSim* sim;
};

inline double cross( const Eigen::Vector2d& a, const Eigen::Vector2d& b )
{
  return a.x() * b.y() - a.y() * b.x();
}

inline double sgn( const double& a )
{
  return ( 0.0 < a ) - ( a < 0.0 );
}

void initSystem( System& io_System );
void initState( System& io_System );

#endif /* system_h */
