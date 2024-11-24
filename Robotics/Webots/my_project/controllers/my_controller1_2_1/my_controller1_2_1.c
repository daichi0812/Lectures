/*
 * File: e-puck用コントローラ例・1-2
 * Date: 2019/4/16
 * Description: e-puck用コントローラ・10秒前進して停止する
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * rob ot.h : ロボットノード
 * motor.h : モータノード
 */

#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>

#define TIME_STEP 256  // ロボットの制御周期 [ms]
#define LEFT 0         // 左右を識別するための定数（左を0とする）
#define RIGHT 1        // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28 // 左・右車輪の指令角速度の最大値 [rad/s]

/*
 * main関数。
 * 引数はRobotノードの"controllerArgs" フィールドで設定する。
 */

int main(int argc, char **argv){

  /* 変数を宣言する */
  double speed[2];     // 左・右車輪の指令角速度 [rad/s]
  double current_time; // 現在時刻を格納する

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

  /* シミュレーション開始 ( 以下無限ループ ) */
  /* 1ループにつき、制御の実行周期 (TIME_STEP[ms]) だけ、時間を経過させる。 */
  /* 終了を指示されたらループを終了する */
  while (wb_robot_step(TIME_STEP) != -1){
    /* センサ情報の取得*/
    current_time = wb_robot_get_time(); // 現在時刻を取得する

    /* 情報処理・制御計算 */
    if ((int)current_time / 10 % 2 != 0){
      speed[LEFT] = -0.2 * MAX_SPEED;  // 0.2の部分には-1.0～1.0の値を与える
      speed[RIGHT] = -0.2 * MAX_SPEED; // 0.2の部分には-1.0～1.0の値を与える
    }
    else if ((int)current_time / 10 % 2 == 0){
      speed[LEFT] = 0.2 * MAX_SPEED;
      speed[RIGHT] = 0.2 * MAX_SPEED;
    }
    else{
      speed[LEFT] = 0.0;
      speed[RIGHT] = 0.0;
    }

    /* 制御コマンド実行 */
    wb_motor_set_velocity(motor[LEFT], speed[LEFT]);
    wb_motor_set_velocity(motor[RIGHT], speed[RIGHT]);
    printf("TIME: %.3lf, SPEED: %.3lf, %.3lf\n",
           current_time, speed[LEFT], speed[RIGHT]); // 現在時刻を表示する
  };

  /* WEBOTSの状態をクリーンアップする ( 終了処理 ) */
  wb_robot_cleanup();

  return 0;
}