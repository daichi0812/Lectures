/*
 * File: e-puck用コントローラ例・1-4
 * Date: 2019/4/16
 * Description: e-puck用コントローラ・全てのLEDを点灯する
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * robot.h : ロボットノード
 * motor.h : モータノード
 * camera.h : カメラノード
 * led.h  : LEDノード
 */

#include <stdio.h>
#include <string.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/camera.h>
#include <webots/led.h>

#define TIME_STEP 256         // ロボットの制御周期 [ms]
#define LEFT 0                // 左右を識別するための定数（左を0とする）
#define RIGHT 1               // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28        // 左・右車輪の指令角速度の最大値 [rad/s]
#define CAMERA_TIME_STEP 1024 // カメラ画像の更新周期 [ms]
#define NUM_LEDS 10           // LED の数

/*
 * main関数。
 * 引数はRobotノードの"controllerArgs" フィールドで設定する。
 */

int main(int argc, char **argv)
{
  /* 変数を宣言する */
  double speed[2];     // 左・右車輪の指令角速度 [rad/s]
  double current_time; // 現在時刻を格納する
  int i;
  bool led_value[NUM_LEDS] = {false}; // 各LEDの点灯消灯の 指令値 ( 初期値は消灯に設定 )
  char device_name[13];               // デバイス名を格納する文字列

  /* デバイスタグの宣言…デバイスを取り扱うためのタグを宣言する。 */
  WbDeviceTag motor[2];      // 左・右車輪のモータ
  WbDeviceTag camera;        // カメラ
  WbDeviceTag led[NUM_LEDS]; // LED (NUM_LEDS 個　= 10個)

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

  camera = wb_robot_get_device("camera");     // カメラのタグの取得
  wb_camera_enable(camera, CAMERA_TIME_STEP); // CAMERA_TIME_STEP周期で動作開始
  printf("Initialize camera ... done\n");

  strcpy(device_name, "led0");      // デバイス名の設定
  for (i = 0; i < 10; i++) // すべてのLEDについて繰り返す
  {
    device_name[3] = '0' + i;                  // 先頭から4文字目 ( 数字 ) の文字コードを設定
    led[i] = wb_robot_get_device(device_name); // i番目のLEDのタグの取得
    wb_led_set(led[i], led_value[i]);          // LEDを初期状態にする
  }
  printf("Initialize LEDs... done\n");

  /* シミュレーション開始 ( 以下無限ループ ) */
  while (wb_robot_step(TIME_STEP) != -1)
  {
    /* センサ情報の取得 */
    current_time = wb_robot_get_time(); // 現在時刻を取得する

    /* 情報処理・制御計算 */
    for (i = 0; i < 10; i++) // すべてのLEDについて繰り返す
    {
      led_value[i] = true; // 各LEDの 指令値を 点灯 に設定
    }
    speed[LEFT] = -0.2 * MAX_SPEED;
    speed[RIGHT] = 0.2 * MAX_SPEED;

    /* 制御コマンド実行 */
    for(int i = 0; i < 10; i++) // すべてのLEDについて繰り返す
    {
      wb_led_set(led[i], led_value[i]); // LEDをled_value[] どおりに光らせる
    }
    
    wb_motor_set_velocity(motor[LEFT], speed[LEFT]);
    wb_motor_set_velocity(motor[RIGHT], speed[RIGHT]);
    printf("TIME: %.3lf, SPEED: %.3lf, %.3lf\n", current_time, speed[LEFT], speed[RIGHT]); // 現在時刻を表示する
  };

  /* WEBOTSの状態をクリーンアップする ( 終了処理 ) */
  wb_robot_cleanup();

  return 0;
}