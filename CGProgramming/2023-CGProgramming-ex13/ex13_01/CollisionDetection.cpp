//
//  CollisionDetection.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#include "CollisionDetection.h"
#include <iostream>

double secondRootOfQuadratic( const double& a, const double& b, const double& c, const double& dscr_sqrt )
{
  double root;
  if( b > 0.0 )
  {
    assert( ( -b - dscr_sqrt ) != 0.0 );
    root = ( 2.0 * c ) / ( -b - dscr_sqrt );
    assert(root == root);
  }
  else
  {
    assert( a != 0.0 );
    root = ( -b + dscr_sqrt ) / ( 2.0 * a );
    assert(root == root);
  }
  return root;
}

bool circleCircleCollisionHappens( const Eigen::Vector2d& q0, double r0, const Eigen::Vector2d& q1, double r1 )
{
  const double dist2 = ( q0 - q1 ).squaredNorm();
  return dist2 < ( r0 + r1 ) * ( r0 + r1 );
}

void computeActiveSet( const RigidBody2DState& in_state, ActiveSet& out_active_set )
{
  out_active_set.clear();
  
  for( int i=0; i<in_state.r.size(); i++ )
  {
    for( int j=i+1; j<in_state.r.size(); j++ )
    {
      if( circleCircleCollisionHappens( in_state.q.segment<2>( 3 * i ), in_state.r(i), in_state.q.segment<2>( 3 * j ), in_state.r(j) ) )
      {
        out_active_set.collision_pairs[i].insert(j);
      }
    }
  }
}

void updateCollisionCache( const RigidBody2DState& in_state, const ActiveSet& in_active_set, CollisionCache*& io_collision_cache_old, CollisionCache*& io_collision_cache_new )
{
  std::swap( io_collision_cache_old, io_collision_cache_new );
  io_collision_cache_new->clear();
  
  for( int idx0 = 0; idx0 < in_active_set.collision_pairs.size(); idx0++ )
  {
    for( auto& p: in_active_set.collision_pairs[idx0] )
    {
      auto q = io_collision_cache_old->circle_circle_constraints[idx0].find( p );
      if( q != io_collision_cache_old->circle_circle_constraints[idx0].end() )
      {
        io_collision_cache_new->circle_circle_constraints[idx0].insert( std::pair< int, Eigen::Vector2d>( p, q->second ) );
      }
      else
      {
        io_collision_cache_new->circle_circle_constraints[idx0].insert( std::pair< int, Eigen::Vector2d>( p, Eigen::Vector2d::Zero() ) );
      }
    }
  }
}

void computeCollisionForce( const DEMSettings& in_settings, const double dt, CollisionCache& io_collision_cache, RigidBody2DState& io_state )
{
  Eigen::Matrix2d R90;
  R90 << 0.0, -1.0, 1.0, 0.0;
  
  for( int idx0 = 0; idx0 < io_collision_cache.circle_circle_constraints.size(); idx0++ )
  {
    for( auto& p: io_collision_cache.circle_circle_constraints[ idx0 ] )
    {
      const int idx1 = p.first;
      Eigen::Vector2d& delta_s = p.second;
    
      const Eigen::Vector2d q0 { io_state.q.segment<2>( 3 * idx0 ) };
      const Eigen::Vector2d q1 { io_state.q.segment<2>( 3 * idx1 ) };
      const double r0 = io_state.r( idx0 );
      const double r1 = io_state.r( idx1 );

      const Eigen::Vector2d arm = q1 - q0;
      const double penetration_depth = std::max( 0.0, ( r0 + r1 ) - arm.norm() );
      Eigen::Vector2d contact_normal { arm };
      contact_normal.normalize();
      
      // arm_r0 is the vector pointing from the center of ball 0 to the contact point.
      const Eigen::Vector2d arm_r0 = contact_normal * ( r0 - 0.5 * penetration_depth );
      
      // arm_r1 is the vector pointing from the center of ball 1 to the contact point.
      const Eigen::Vector2d arm_r1 = - contact_normal * ( r1 - 0.5 * penetration_depth );
      
      const Eigen::Vector2d vrel = io_state.v.segment<2>( 3 * idx0 ) - io_state.v.segment<2>( 3 * idx1 ) + io_state.v( 3 * idx0 + 2 ) * R90 * arm_r0 - io_state.v( 3 * idx1 + 2 ) * R90 * arm_r1;
      
      const double vrel_n = contact_normal.dot( vrel );
      const Eigen::Vector2d vn = vrel_n * contact_normal;
      const Eigen::Vector2d vt = vrel - vn;
    
      // update delta_s
      // add current displacement
      delta_s += dt * vrel;
      // project out normal component
      delta_s -= contact_normal.dot( delta_s ) * contact_normal;
    
      const Eigen::Vector2d normal_force = - in_settings.kn * penetration_depth * contact_normal - 0.5 * in_settings.gamman * vn;
    
      Eigen::Vector2d friction_force = - in_settings.kt * delta_s - 0.5 * in_settings.gammat * vt;
      
      // project to respect Coulomb friction
      const double mu_fn = std::max( 0.0, - in_settings.mu * normal_force.norm() * sgn( normal_force.dot( contact_normal ) ) );
      const double ft = friction_force.norm();
    
      // If modifying delta_s so the force lies within the cone is impossible,
      // zero out delta_s and set the force to the maximum possible value opposing the slip direction
      if( 0.5 * in_settings.gammat * vt.norm() > mu_fn )
      {
        // ①の場合の処理をここに書き,
        // friction_force と delta_s を適切に書き換えてください.
          delta_s.setZero();
          friction_force = mu_fn * (- vt / (- vt).norm());
      }
      // Otherwise, shrink delta_s so the force lies within the cone
      else if( ft > mu_fn )
      {
        // ②の場合の処理をここに書き,
        // friction_force と delta_s を適切に書き換えてください.
          double a = (pow(in_settings.kt, 2.0) * delta_s).dot(delta_s);
          double b = (in_settings.kt * in_settings.gammat * vt).dot(delta_s);
          double c = (0.25 * pow(in_settings.gammat, 2.0) * vt).dot(vt) - (pow(in_settings.mu, 2.0) * normal_force).dot(normal_force);
          double x = (- b + sqrt(pow(b, 2.0) - 4 * a * c)) / (2 * a);

          delta_s = x * delta_s;
          friction_force = -in_settings.kt * delta_s - 0.5 * in_settings.gammat * vt;
      }
    
      const Eigen::Vector2d total_force = normal_force + friction_force;
    
      io_state.F.segment<2>( 3 * idx0 ) += total_force;
      io_state.F( 3 * idx0 + 2 ) += cross( arm_r0, total_force );
      io_state.F.segment<2>( 3 * idx1 ) -= total_force;
      io_state.F( 3 * idx1 + 2 ) -= cross( arm_r1, total_force );
    }
  }
}
