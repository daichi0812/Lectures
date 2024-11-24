//
//  CollisionDetection.h
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef CollisionDetection_h
#define CollisionDetection_h

#include "system.h"

bool circleCircleCollisionHappens( const Eigen::Vector2d& q0, double r0, const Eigen::Vector2d& q1, double r1 );

void computeActiveSet( const RigidBody2DState& in_state, ActiveSet& out_active_set );

void computeCollisionForce( const DEMSettings& in_settings, const double dt, const ActiveSet& in_active_set, RigidBody2DState& io_state );

#endif /* CollisionDetection_h */
