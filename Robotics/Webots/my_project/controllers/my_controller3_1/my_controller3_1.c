/*
 * File: e-puck用コントローラ例・3-1
 * Date: 2024/5/7
 * Description: 直進時の移動距離と旋回時の旋回角度を求めるプログラム
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * rob ot.h : ロボットノード
 * motor.h : モータノード
 */

#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include "my_position_sensor_utility.h"

#define TIME_STEP 256  // ロボットの制御周期 [ms]
#define LEFT 0         // 左右を識別するための定数（左を0とする）
#define RIGHT 1        // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28 // 左・右車輪の指令角速度の最大値 [rad/s]

/*
 * main関数。
 * 引数はRobotノードの"controllerArgs" フィールドで設定する。
 */

int main(int argc, char **argv)
{

  /* 変数を宣言する */
  double speed[2];       // 左・右車輪の指令角速度 [rad/s]
  double current_time;   // 現在時刻を格納する
  POS_SENSOR pos_sensor; // 角度センサ用構造体
  double length;         // 走行距離 [m]
  double orientation;    // 旋回角度 [rad]

  /* デバイスタグの宣言…デバイスを取り扱うためのタグを宣言する。 */
  WbDeviceTag motor[2]; // 左・右車輪のモータ

  /* WEBOTSの状態を初期化する */
  wb_robot_init();

  /* デバイス類を初期化する */
  motor[LEFT] = wb_robot_get_device("left wheel motor");   // 左モータのタグの取得
  motor[RIGHT] = wb_robot_get_device("right wheel motor"); // 右モータのタグの取得
  wb_motor_set_position(motor[LEFT], INFINITY);            // 角速度指令モードに設定
  wb_motor_set_position(motor[RIGHT], INFINITY);           // 角速度指令モードに設定
  wb_motor_set_velocity(motor[LEFT], 0.0);                 // 左モータを停止させる
  wb_motor_set_velocity(motor[RIGHT], 0.0);                // 右モータを停止させる
  printf("Initialize motors ... done\n");

  pos_sensor = initialize_position_sensors(); // 角度センサと諸変数の初期化
  printf("Initialize position sensors ... done\n");

  /* シミュレーション開始 ( 以下無限ループ ) */
  /* 1ループにつき、制御の実行周期 (TIME_STEP[ms]) だけ、時間を経過させる。 */
  /* 終了を指示されたらループを終了する */
  while (wb_robot_step(TIME_STEP) != -1)
  {
    /* センサ情報の取得*/
    current_time = wb_robot_get_time();            // 現在時刻を取得する
    pos_sensor = get_position_sensors(pos_sensor); // モータの角度を取得する

    /* 情報処理・制御計算 */
    length = compute_length(pos_sensor);           // 走行距離算出
    orientation = compute_orientation(pos_sensor); // 旋回角度算出
    if (current_time <= 5.0)                       // 0秒から5秒間、前進
    {
      speed[LEFT] = 0.2 * MAX_SPEED;
      speed[RIGHT] = 0.2 * MAX_SPEED;
    }
    else if (current_time <= 5.5) // 5秒から0.5秒間 停止し、角度センサをリセット
    {
      pos_sensor = reset_position_sensors(pos_sensor);
      speed[LEFT] = 0.0;
      speed[RIGHT] = 0.0;
    }
    else if (current_time <= 10.5) // 5.5秒から5秒間、右旋回
    {
      speed[LEFT] = 0.2 * MAX_SPEED;
      speed[RIGHT] = -0.2 * MAX_SPEED;
    }
    else if (current_time <= 11.0) // 10.5秒から0.5秒間停止し、角度センサをリセット
    {
      pos_sensor = reset_position_sensors(pos_sensor);
      speed[LEFT] = 0.0;
      speed[RIGHT] = 0.0;
    }
    else if (current_time <= 16.0) // 16秒から5秒間、前進
    {
      speed[LEFT] = 0.2 * MAX_SPEED;
      speed[RIGHT] = 0.2 * MAX_SPEED;
    }
    else // 16秒以降停止し、角度センサをリセット
    {
      pos_sensor = reset_position_sensors(pos_sensor);
      speed[LEFT] = 0.0;
      speed[RIGHT] = 0.0;
    }

    /* 制御コマンド実行 */
    wb_motor_set_velocity(motor[LEFT], speed[LEFT]);
    wb_motor_set_velocity(motor[RIGHT], speed[RIGHT]);
    printf("TIME: %.3lf, SPEED: %.3lf, %.3lf\n",
           current_time, speed[LEFT], speed[RIGHT]); // 現在時刻を表示する
    printf("POSITION: %.3lf[rad], %.3lf[rad]\n",
           pos_sensor.position[LEFT], pos_sensor.position[RIGHT]);
    printf("LENGTH: %.3lf[m], ORIENTATION: %.3lf[rad]\n", length, orientation);
    printf("\n");
  };

  /* WEBOTSの状態をクリーンアップする ( 終了処理 ) */
  wb_robot_cleanup();

  return 0;
}