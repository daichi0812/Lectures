/*
 * File: e-puck用コントローラ例・3-2
 * Date: 2024/5/7
 * Description: 10cm前進して90度旋回する動作を繰り返すプログラム
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * rob ot.h : ロボットノード
 * motor.h : モータノード
 */

#include <stdio.h>
#include <math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include "my_position_sensor_utility.h"

#define TIME_STEP 64         // ロボットの制御周期 [ms]
#define LEFT 0               // 左右を識別するための定数（左を0とする）
#define RIGHT 1              // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28       // 左・右車輪の指令角速度の最大値 [rad/s]
#define PI (4.0 * atan(1.0)) // 円周率

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
  int mode = 0;          // ロボットの動作状態。偶数なら直進モード、奇数なら旋回モード

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

    if (mode % 2 == 0) // modeが偶数なら 直進モード
    {
      speed[LEFT] = 0.1 * MAX_SPEED;
      speed[RIGHT] = 0.1 * MAX_SPEED;
      if (length >= 0.1) // 0.1[m] 以上前進したら
      {
        speed[LEFT] = 0.0;
        speed[RIGHT] = 0.0;                              // 停止
        pos_sensor = reset_position_sensors(pos_sensor); // リセット
        mode++;                                          // 奇数に変更
      }
    }
    else // modeが奇数なら旋回 モード （左旋回）
    {
      speed[LEFT] = -0.1 * MAX_SPEED;
      speed[RIGHT] = 0.1 * MAX_SPEED;
      if (orientation >= PI / 2.0) // π/2[rad] 以上左旋回したら
      {
        speed[LEFT] = 0.0;
        speed[RIGHT] = 0.0;                              // 停止
        pos_sensor = reset_position_sensors(pos_sensor); // リセット
        mode++;                                          // 偶数に変更
      }
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