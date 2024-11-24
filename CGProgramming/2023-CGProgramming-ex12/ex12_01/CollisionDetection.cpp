//
//  CollisionDetection.cpp
//  penalty_rigidbody_2d
//
//  Created by Yonghao Yue on 2019/09/13.
//  Copyright © 2019 Yonghao Yue. All rights reserved.
//

#include "CollisionDetection.h"
#include <iostream>

double secondRootOfQuadratic(const double& a, const double& b, const double& c, const double& dscr_sqrt)
{
	double root;
	if (b > 0.0)
	{
		assert((-b - dscr_sqrt) != 0.0);
		root = (2.0 * c) / (-b - dscr_sqrt);
		assert(root == root);
	}
	else
	{
		assert(a != 0.0);
		root = (-b + dscr_sqrt) / (2.0 * a);
		assert(root == root);
	}
	return root;
}

bool circleCircleCollisionHappens(const Eigen::Vector2d& q0, double r0, const Eigen::Vector2d& q1, double r1)
{

	double x0 = q0.x();
	double x1 = q1.x();
	double y0 = q0.y();
	double y1 = q1.y();
	double d = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));

	if (r0 + r1 >= d) {
		return true;
	}
	if (r0 + r1 < d) {
		return false;
	}
}

void computeActiveSet(const RigidBody2DState& in_state, ActiveSet& out_active_set)
{
	out_active_set.clear();

	for (int i = 0; i < in_state.r.size(); i++)
	{
		for (int j = i + 1; j < in_state.r.size(); j++)
		{
			if (circleCircleCollisionHappens(in_state.q.segment<2>(3 * i), in_state.r(i), in_state.q.segment<2>(3 * j), in_state.r(j)))
			{
				out_active_set.collision_pairs[i].insert(j);
			}
		}
	}
}

void computeCollisionForce(const DEMSettings& in_settings, const double dt, const ActiveSet& in_active_set, RigidBody2DState& io_state)
{
	Eigen::Matrix2d R90;
	R90 << 0.0, -1.0, 1.0, 0.0;

	for (int idx0 = 0; idx0 < in_active_set.collision_pairs.size(); idx0++)
	{
		for (auto& idx1 : in_active_set.collision_pairs[idx0])
		{
			const Eigen::Vector2d q0 { io_state.q.segment<2>(3 * idx0) };
			const Eigen::Vector2d q1 { io_state.q.segment<2>(3 * idx1) };
			const double r0 = io_state.r(idx0);
			const double r1 = io_state.r(idx1);

			double penetration_depth = 0.0;
			Eigen::Vector2d arm_r0 = Eigen::Vector2d(0.0, 0.0);
			Eigen::Vector2d arm_r1 = Eigen::Vector2d(0.0, 0.0);
			Eigen::Vector2d contact_normal = Eigen::Vector2d(0.0, 0.0);
			double vrel_n = 0.0;

			/* ここに penetration_depth (double 型),
			 arm_r0 (Eigen::Vector2d 型), arm_r1 (Eigen::Vector2d 型),
			 contact_normal (Eigen::Vector2d 型),
			 vrel_n (double 型) を求めるプログラムを書いてください
			*/
			double x0 = q0.x();
			double x1 = q1.x();
			double y0 = q0.y();
			double y1 = q1.y();
			double d = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));

			penetration_depth = r0 + r1 - d;
			contact_normal = (q1 - q0).normalized();
			arm_r0 = contact_normal * (r0 - penetration_depth / 2.0);
			arm_r1 = - contact_normal * (r1 - penetration_depth / 2.0);

			const Eigen::Vector2d v0 {io_state.v.segment<2>(3 * idx0)};
			const Eigen::Vector2d v1 {io_state.v.segment<2>(3 * idx1)};
			double ohm0 = io_state.v(3 * idx0 + 2);
			double ohm1 = io_state.v(3 * idx1 + 2);

			const Eigen::Vector2d v01 = v0 - v1 + ohm0 * R90 * arm_r0 - ohm1 * R90 * arm_r1;
			vrel_n =  v01.dot(contact_normal);
			
			const Eigen::Vector2d normal_force = -in_settings.kn * penetration_depth * contact_normal - 0.5 * in_settings.gamman * vrel_n * contact_normal;

			const Eigen::Vector2d total_force = normal_force;

			io_state.F.segment<2>(3 * idx0) += total_force;
			io_state.F(3 * idx0 + 2) += cross(arm_r0, total_force);
			io_state.F.segment<2>(3 * idx1) -= total_force;
			io_state.F(3 * idx1 + 2) -= cross(arm_r1, total_force);
		}
	}
}
