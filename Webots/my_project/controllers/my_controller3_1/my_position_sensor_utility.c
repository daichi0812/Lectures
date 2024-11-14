/*
 * File:         e-puck用コントローラ例・3-1用分割ソースファイル
 * Date:         2019/5/7
 * Description:  角度センサおよびそれに関わる諸関数の実装
 */
/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * robot.h				: ロボットノード
 * position_sensor.h	: 角度センサノード
 */
#include <math.h>
#include <webots/robot.h>
#include <webots/position_sensor.h>
#include "my_position_sensor_utility.h"

#define TIME_STEP	256		// ロボットの制御周期[ms]
#define LEFT	 	0		// 左右を識別するための定数（左を0とする）
#define RIGHT	 	1		// 左右を識別するための定数（右を1とする）

#define WL_R_SIMU	0.02	// ロボットの車輪半径(WEBOTS上)[m]
#define AX_L_SIMU	0.052	// ロボットの車軸長(WEBOTS上)[m]

#define WL_R_REAL	0.02	// ロボットの車輪半径(実機上)[m]
#define AX_L_REAL	0.052	// ロボットの車軸長(実機上)[m]

#define MAX_POS_VALUE	205.78304	// 角度センサから取得する値の最大[rad](=0.00628*pow(2,15))

/* 角度センサを初期化 */
POS_SENSOR initialize_position_sensors(void)
{
  POS_SENSOR ret;	// 戻り値としての角度センサ用構造体

  ret.mode = wb_robot_get_mode();
  ret.tag[LEFT]  = wb_robot_get_device("left wheel sensor");	// タグの取得
  ret.tag[RIGHT] = wb_robot_get_device("right wheel sensor");	// タグの取得
  wb_position_sensor_enable(ret.tag[LEFT],  TIME_STEP);	// TIME_STEP周期で動作開始
  wb_position_sensor_enable(ret.tag[RIGHT], TIME_STEP);	// TIME_STEP周期で動作開始
  ret = reset_position_sensors(ret);	// 測定値をリセット

  return ret;
}

/* 角度センサの測定値を取得 */
POS_SENSOR get_position_sensors(POS_SENSOR pos_sensor)
{
  POS_SENSOR ret = pos_sensor;	// 戻り値としての角度センサ用構造体
  double value[2];	// 角度センサの測定値（未加工）

  ret.mode = wb_robot_get_mode();	// ロボットの動作モードの取得
  if(ret.mode != pos_sensor.mode			// 動作モードが切り替わったら、
		|| isnan(ret.pre_pos[LEFT]) ){	// または、position0[]がNaNだったら、
    ret = reset_position_sensors(ret);		// 測定値をリセット
  }

  // 角度センサの生データを取得
  value[LEFT]  = wb_position_sensor_get_value(ret.tag[LEFT]);
  value[RIGHT] = wb_position_sensor_get_value(ret.tag[RIGHT]);

  // オーバーフローの処理（測定値が-205.78304から+205.78304になるとき）
  if(value[LEFT] - ret.pre_pos[LEFT] >  MAX_POS_VALUE)
	ret.pre_pos[LEFT]  += 2.0 * MAX_POS_VALUE;
  else if(value[LEFT] - ret.pre_pos[LEFT] < -MAX_POS_VALUE)
	ret.pre_pos[LEFT]  -= 2.0 * MAX_POS_VALUE;
  if(value[RIGHT] - ret.pre_pos[RIGHT] >  MAX_POS_VALUE)
	ret.pre_pos[RIGHT] += 2.0 * MAX_POS_VALUE;
  else if(value[RIGHT] - ret.pre_pos[RIGHT] < -MAX_POS_VALUE)
	ret.pre_pos[RIGHT] -= 2.0 * MAX_POS_VALUE;

  // 角度センサの基準の角度からの回転角度を計算
  ret.position[LEFT]  += value[LEFT]  - ret.pre_pos[LEFT];
  ret.position[RIGHT] += value[RIGHT] - ret.pre_pos[RIGHT];
  ret.pre_pos[LEFT]  = value[LEFT];
  ret.pre_pos[RIGHT] = value[RIGHT];

  return ret;
}

/* 角度センサの測定値をリセット */
POS_SENSOR reset_position_sensors(POS_SENSOR pos_sensor)
{
  POS_SENSOR ret = pos_sensor;	// 戻り値としての角度センサ用構造体

  // 現在の角度を基準の角度に設定
  ret.pre_pos[LEFT]  = wb_position_sensor_get_value(ret.tag[LEFT]);
  ret.pre_pos[RIGHT] = wb_position_sensor_get_value(ret.tag[RIGHT]);
  ret.position[LEFT]  = 0.0;
  ret.position[RIGHT] = 0.0;

  return ret;
}

/* 角度センサの測定値を元にロボットの移動距離を計算 */
double compute_length(POS_SENSOR pos_sensor)
{
  double length;
  double avr_position; // 角度センサの測定値の平均

  avr_position = (pos_sensor.position[LEFT] + pos_sensor.position[RIGHT]) / 2.0;
  // 移動距離の計算。動作モードがWEBOTSか実機かでパラメータを変更
  if(pos_sensor.mode == WB_MODE_SIMULATION){
    length = avr_position * WL_R_SIMU;
  }
  else{
    length = avr_position * WL_R_REAL;
  }

  return length;
}

/* 角度センサの測定値を元にロボットの旋回角度を計算 */
double compute_orientation(POS_SENSOR pos_sensor)
{
  double orientation;
  double half_diff_pos; // 角度センサの測定値の差の半分

  half_diff_pos = (pos_sensor.position[RIGHT] - pos_sensor.position[LEFT]) / 2.0;
  // 旋回角度の計算。動作モードがWEBOTSか実機かでパラメータを変更
  if(pos_sensor.mode == WB_MODE_SIMULATION){
    orientation = (half_diff_pos*WL_R_SIMU)/(AX_L_SIMU/2.0);
  }
  else{
    orientation = (half_diff_pos*WL_R_REAL)/(AX_L_REAL/2.0);
  }

  return orientation;
}
