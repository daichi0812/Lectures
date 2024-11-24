//
//  PenaltyRigidBody2DSim.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#include "PenaltyRigidBody2DSim.h"
#include "CollisionDetection.h"
#include <iostream>

#include "system.h"

// Constructor
PenaltyRigidBody2DSim::PenaltyRigidBody2DSim( const DEMSettings& in_settings )
 : m_CollisionCache( nullptr ), m_CollisionCache_old( nullptr ), m_DEMSettings( in_settings )
{
  m_CollisionCache = new CollisionCache();
  m_CollisionCache_old = new CollisionCache();
}

//Destructor
PenaltyRigidBody2DSim::~PenaltyRigidBody2DSim()
{
  if( m_CollisionCache != nullptr )
    delete m_CollisionCache;
  if( m_CollisionCache_old != nullptr)
    delete m_CollisionCache_old;
}

// Copy initial state
void PenaltyRigidBody2DSim::setInitialState( const RigidBody2DState& in_state )
{
  m_ActiveSet.clear();
  m_CollisionCache->clear();
  m_CollisionCache_old->clear();
  
  m_State = in_state;
  m_State.num_bodies = in_state.q.size() / 3;
  
  m_ActiveSet.setSize( m_State.num_bodies );
  m_CollisionCache->setSize( m_State.num_bodies );
  m_CollisionCache_old->setSize( m_State.num_bodies );
}

const RigidBody2DState& PenaltyRigidBody2DSim::getState() const
{
  return m_State;
}

void PenaltyRigidBody2DSim::step()
{
  // update forces
  // clear force and apply gravitational acceleration
  for( int i=0; i<m_State.r.size(); i++ )
  {
    if( m_State.fixed[i] )
      m_State.F.segment<3>( 3 * i ) << 0.0, 0.0, 0.0;
    else
    {
      m_State.F.segment<2>( 3 * i ) = m_State.M.segment<2>( 3 * i ).cwiseProduct( m_DEMSettings.g );
      m_State.F( 3 * i + 2 ) = 0.0;
    }
  }
  
  // compute collision
  computeActiveSet( m_State, m_ActiveSet );
  updateCollisionCache( m_State, m_ActiveSet, m_CollisionCache_old, m_CollisionCache );
  
  // compute collision force
  computeCollisionForce( m_DEMSettings, m_DEMSettings.dt, *m_CollisionCache, m_State );
  
  // update velocities and positions
  for( int i=0; i<m_State.r.size(); i++ )
  {
    if( m_State.fixed[i] )
      continue;
    
    m_State.v.segment<3>( 3 * i ) += m_DEMSettings.dt * m_State.Minv.segment<3>( 3 * i ).cwiseProduct( m_State.F.segment<3>( 3 * i ) );
    m_State.q.segment<3>( 3 * i ) += m_DEMSettings.dt * m_State.v.segment<3>( 3 * i );
  }
}
