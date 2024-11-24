//
//  bezier.cpp
//  Bezier_for_class
//
//  Created by Yonghao Yue on 2021/01/12.
//

#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define EIGEN_DONT_VECTORIZE

#include "bezier.h"

void splitCurve( const CubicBezier& in_Curve, const double t, CubicBezier& out_C1, CubicBezier& out_C2 )
{
  const Eigen::Vector2d P01 = evaluateLinearBezier( in_Curve.P[0], in_Curve.P[1], t );
  const Eigen::Vector2d P12 = evaluateLinearBezier( in_Curve.P[1], in_Curve.P[2], t );
  const Eigen::Vector2d P23 = evaluateLinearBezier( in_Curve.P[2], in_Curve.P[3], t );
  const Eigen::Vector2d P012 = evaluateLinearBezier( P01, P12, t );
  const Eigen::Vector2d P123 = evaluateLinearBezier( P12, P23, t );
  const Eigen::Vector2d Pt = evaluateLinearBezier( P012, P123, t );
  
  out_C1.P[0] = in_Curve.P[0];
  out_C1.P[1] = P01;
  out_C1.P[2] = P012;
  out_C1.P[3] = Pt;
  out_C2.P[0] = Pt;
  out_C2.P[1] = P123;
  out_C2.P[2] = P23;
  out_C2.P[3] = in_Curve.P[3];
}

