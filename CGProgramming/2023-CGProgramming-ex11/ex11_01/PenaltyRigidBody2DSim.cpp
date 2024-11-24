//
//  PenaltyRigidBody2DSim.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#include "PenaltyRigidBody2DSim.h"
#include <iostream>

#include "system.h"

// Constructor
PenaltyRigidBody2DSim::PenaltyRigidBody2DSim( const DEMSettings& in_settings )
 : m_DEMSettings( in_settings )
{
}

// Destructor
PenaltyRigidBody2DSim::~PenaltyRigidBody2DSim()
{
}

// Copy initial state
void PenaltyRigidBody2DSim::setInitialState( const RigidBody2DState& in_state )
{
  m_State = in_state;
  m_State.num_bodies = in_state.q.size() / 3;
}

const RigidBody2DState& PenaltyRigidBody2DSim::getState() const
{
  return m_State;
}

void PenaltyRigidBody2DSim::step()
{
  // update forces
  for( int i=0; i<m_State.num_bodies; i++ )
  {
    if( m_State.fixed[i] )
      m_State.F.segment<3>( 3 * i ) << 0.0, 0.0, 0.0;
    else
    {
      m_State.F.segment<2>( 3 * i ) = m_State.M.segment<2>( 3 * i ).cwiseProduct( m_DEMSettings.g );
      m_State.F( 3 * i + 2 ) = 0.0;
    }
  }

  // update velocities and positions
  for( int i=0; i<m_State.num_bodies; i++ )
  {
    if( m_State.fixed[i] )
      continue;
    
    m_State.v.segment<3>( 3 * i ) += m_DEMSettings.dt * m_State.Minv.segment<3>( 3 * i ).cwiseProduct( m_State.F.segment<3>( 3 * i ) );
    m_State.q.segment<3>( 3 * i ) += m_DEMSettings.dt * m_State.v.segment<3>( 3 * i );
  }
}
