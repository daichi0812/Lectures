/*
 * 15822108 情報テクノロジー 堀田大智
 * File: e-puck用コントローラ例・1-3
 * Date: 2019/4/16
 * Description: e-puck用コントローラ・その場旋回しながらカメラを使用する
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * robot.h : ロボットノード
 * motor.h : モータノード
 * camera.h : カメラノード
 */

#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/camera.h>

#define TIME_STEP 256        // ロボットの制御周期 [ms]
#define LEFT 0                // 左右を識別するための定数（左を0とする）
#define RIGHT 1               // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28        // 左・右車輪の指令角速度の最大値 [rad/s]
#define CAMERA_TIME_STEP 1024 // カメラ画像の更新周期 [ms]

/*
 * main関数。
 * 引数はRobotノードの"controllerArgs" フィールドで設定する。
 */

int main(int argc, char **argv)
{
  /* 変数を宣言する */
  double speed[2];                // 左・右車輪の指令角速度 [rad/s]
  double current_time;            // 現在時刻を格納する
  const unsigned char *image;     // 撮影画像のピクセル色情報を格納するメモリ の ポインタ
  int width = 0, height = 0;      // 画像の幅と高さを格納する変数
  int pixel_x = 0, pixel_y = 0;   // ピクセルのx座標とy座標
  int r = 0, g = 0, b = 0, l = 0; // ピクセルの色情報と輝度情報
  int right_count_red_pixel = 0;  // 右側の赤いピクセルの数
  int left_count_red_pixel = 0;   // 左側の赤いピクセルの数
  int count_red_pixel = 0;

  /* デバイスタグの宣言…デバイスを取り扱うためのタグを宣言する。 */
  WbDeviceTag motor[2]; // 左・右車輪のモータ
  WbDeviceTag camera;   // カメラ

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
  width = wb_camera_get_width(camera);        // カメラ画像の幅を取得 (52になるはず )
  height = wb_camera_get_height(camera);      // カメラ画像の高さを取得 (39になるはず )
  printf("Initialize camera ... done\n");

  /* シミュレーション開始 ( 以下無限ループ ) */
  while (wb_robot_step(TIME_STEP) != -1)
  {
    /* センサ情報の取得 */
    current_time = wb_robot_get_time();  // 現在時刻を取得する
    image = wb_camera_get_image(camera); // 画像情報のポインタを取得

    /* 情報処理・制御計算 */
    right_count_red_pixel = 0;
    left_count_red_pixel = 0;

    // for文で座標を変化させてカメラ画像の全ピクセルについて調べる
    // x座標はpixel_x, y座標はpixel_y
    // pixel_x = 0, pixel_y = 0が画面左上端、
    // pixel_x=width-1, pixel_y=height-1が画面右下端

    // 左半分だけの画面を読み取る
    for (pixel_x = 0; pixel_x < width * 0.5; pixel_x++)
    {
      for (pixel_y = 0; pixel_y < height; pixel_y++)
      {
        // r = 赤成分 , g = 緑成分 , b = 青成分 , l = 輝度 , いずれも0～255を返す
        r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
        g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
        b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
        l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

        // たとえばrが100より大きく、g,bが80より小さピクセル を赤 とする
        if (r > 200 && g < 80 && b < 80)
        {
          left_count_red_pixel++;
        }
      }
    }
    // 右半分だけの画面を読み取る
    for (pixel_x = width * 0.5; pixel_x < width; pixel_x++)
    {
      for (pixel_y = 0; pixel_y < height; pixel_y++)
      {
        r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
        g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
        b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
        l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

        if (r > 200 && g < 80 && b < 80)
        {
          right_count_red_pixel++;
        }
      }
    }

    if (right_count_red_pixel > left_count_red_pixel && right_count_red_pixel > 10) // 右の方が赤が強かったら
    {
      count_red_pixel = right_count_red_pixel;
      speed[LEFT] = 0.8 * MAX_SPEED; //右前に前進する
      speed[RIGHT] = 0.5 * MAX_SPEED;
    }
    else if(left_count_red_pixel > right_count_red_pixel && left_count_red_pixel > 10) // 左の赤が強かったら
    {
      count_red_pixel = left_count_red_pixel;
      speed[LEFT] = 0.5 * MAX_SPEED; // 左前に前進する
      speed[RIGHT] = 0.8 * MAX_SPEED;
    }else{
      count_red_pixel = 0.5 * (right_count_red_pixel + left_count_red_pixel);
      speed[LEFT] = -0.2 * MAX_SPEED; // 旋回する
      speed[RIGHT] = 0.2 * MAX_SPEED;
    }

    pixel_x = width * 0.5;
    pixel_y = height * 0.5;

    r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
    g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
    b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
    l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

    /* 制御コマンド実行 */
    wb_motor_set_velocity(motor[LEFT], speed[LEFT]);
    wb_motor_set_velocity(motor[RIGHT], speed[RIGHT]);
    printf("TIME: %.3lf, SPEED: %.3lf, %.3lf\n", current_time, speed[LEFT], speed[RIGHT]); // 現在時刻を表示する
    printf("width:%d, height:%d\n", width, height);                                        // 画像の縦横の大きさ
    printf("RedPixel: %d\n", count_red_pixel);                                             // 「赤」と判定されたピクセル数
    printf("rgb: %d, %d, %d, l: %d\n", r, g, b, l);                                        // 中心ピクセルのRGB値
  };

  // 終了時のカメラ画像を保存する
  printf("wb_camera_save_image = %d\n", wb_camera_save_image(camera, "image.png", 100));

  /* WEBOTSの状態をクリーンアップする ( 終了処理 ) */
  wb_robot_cleanup();

  return 0;
}