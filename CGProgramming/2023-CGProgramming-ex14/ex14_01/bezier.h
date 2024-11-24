//
//  bezier.h
//  Bezier_for_class
//
//  Created by Yonghao Yue on 2021/01/12.
//

#ifndef bezier_h
#define bezier_h

#include <Eigen/Core>

struct CubicBezier
{
  Eigen::Vector2d P[4];
};

inline Eigen::Vector2d evaluateLinearBezier( const Eigen::Vector2d& in_P0, const Eigen::Vector2d& in_P1, const double t )
{
  return t * in_P1 + ( 1.0 - t ) * in_P0;
}

inline Eigen::Vector2d evaluateQuadraticBezier( const Eigen::Vector2d& in_P0, const Eigen::Vector2d& in_P1, const Eigen::Vector2d& in_P2, const double t )
{
  return evaluateLinearBezier( evaluateLinearBezier( in_P0, in_P1, t ), evaluateLinearBezier( in_P1, in_P2, t ), t );
}

inline Eigen::Vector2d evaluateCubicBezier( const CubicBezier& in_Bezier, const double t )
{
  return evaluateLinearBezier( evaluateQuadraticBezier( in_Bezier.P[0], in_Bezier.P[1], in_Bezier.P[2], t ), evaluateQuadraticBezier( in_Bezier.P[1], in_Bezier.P[2], in_Bezier.P[3], t ), t );
}

void splitCurve( const CubicBezier& in_Curve, const double t, CubicBezier& out_C1, CubicBezier& out_C2 );

#endif /* bezier_h */
