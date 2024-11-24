//
//  Light.h
//  gl3d_raytracing_v2
//
//  Created by Yonghao Yue on 2019/11/19.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#ifndef Light_h
#define Light_h

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include <Eigen/Dense>

struct Light
{
  Eigen::Vector3d pos;
  Eigen::Vector3d color;
  double intensity;
};



#endif /* Light_h */
