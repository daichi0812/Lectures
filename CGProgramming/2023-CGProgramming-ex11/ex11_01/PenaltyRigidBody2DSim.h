//
//  PenaltyRigidBody2DSim.h
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef PenaltyRigidBody2DSim_h
#define PenaltyRigidBody2DSim_h

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include <Eigen/Core>
#include <Eigen/Dense>

#include "RigidBody2DState.h"

struct DEMSettings
{
  Eigen::Vector2d g;
  double dt;
};

class PenaltyRigidBody2DSim
{
  PenaltyRigidBody2DSim() = delete;
public:
  PenaltyRigidBody2DSim( const DEMSettings& in_settings );
  ~PenaltyRigidBody2DSim();
  
  void setInitialState( const RigidBody2DState& in_state );
  void step();
  
  const RigidBody2DState& getState() const;
  
private:
  RigidBody2DState m_State;
  DEMSettings m_DEMSettings;
};

#endif /* PenaltyRigidBody2DSim_h */
