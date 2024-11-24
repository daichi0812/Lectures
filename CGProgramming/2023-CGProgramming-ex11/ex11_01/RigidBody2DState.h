//
//  RigidBody2DState.h
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/15.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef RigidBody2DState_h
#define RigidBody2DState_h

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include <Eigen/Core>
#include <Eigen/Dense>

#include <set>
#include <map>
#include <vector>

struct RigidBody2DState
{
  // position (x, y) and rotation angle (t)
  Eigen::VectorXd q; //x0, y0, t0, x1, y1, t1, ...
  
  // velocity (vx, vy) and angular velocity (vt)
  Eigen::VectorXd v; //vx0, vy0, vt0, vx1, vy1, vt1, ...

  // radius
  Eigen::VectorXd r; //r0, r1, r2, ...
  
  // force (fx, fy) and torque (ft)
  Eigen::VectorXd F; //fx0, fy0, ft0, fx1, fy1, ft1, ...

  // mass (m) and inertia (I), I = m r^2 for discs
  Eigen::VectorXd M; // m0, m0, I0, m1, m1, I1, ...

  // inverse of mass and inertia
  Eigen::VectorXd Minv; // m0^(-1), m0^(-1), I0^(-1), m1^(-1), m1^(-1), I1^(-1), ...
  
  std::vector<bool> fixed;
  
  int num_bodies;
};

#endif /* RigidBody2DState_h */
