//
//  RigidBody2DState.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/15.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#include "RigidBody2DState.h"

void ActiveSet::clear()
{
  for( int i=0; i<collision_pairs.size(); i++ )
    collision_pairs[i].clear();
}
      
void ActiveSet::setSize( const int size )
{
  collision_pairs.resize( size );
}

void CollisionCache::clear()
{
  for( int i=0; i<circle_circle_constraints.size(); i++ )
    circle_circle_constraints[i].clear();
}

void CollisionCache::setSize( const int size )
{
  circle_circle_constraints.resize( size );
}
