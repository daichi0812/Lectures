/*
 * 15822108 情報テクノロジー 堀田大智
 * File: e-puck用コントローラ例
 * Date: 2024/5/13
 * Description: オリジナルロボット
 */

/*
 * ロボットノード用のライブラリ、および各種センサノード用ライブラリの読み込み
 * robot.h : ロボットノード
 * motor.h : モータノード
 /Users/daichi/Documents/my_project/controllers
 * camera.h : カメラノード
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/camera.h>
#include <webots/led.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64         // ロボットの制御周期 [ms]
#define LEFT 0               // 左右を識別するための定数（左を0とする）
#define RIGHT 1              // 左右を識別するための定数（右を1とする）
#define MAX_SPEED 6.28       // 左・右車輪の指令角速度の最大値 [rad/s]
#define CAMERA_TIME_STEP 126 // カメラ画像の更新周期 [ms]
#define NUM_LEDS 10          // LED の数
#define NUM_DIST_SENS 8      // 距離センサの数

/*
 * main関数。
 * 引数はRobotノードの"controllerArgs" フィールドで設定する。
 */

int main(int argc, char **argv)
{
    /* 変数を宣言する */
    double speed[2];                          // 左・右車輪の指令角速度 [rad/s]
    double current_time;                      // 現在時刻を格納する
    double random_speed = 0.0;                // 乱数を保持する変数
    double dist_value[NUM_DIST_SENS] = {0.0}; // 距離センサの測定値
    const unsigned char *image;               // 撮影画像のピクセル色情報を格納するメモリ の ポインタ
    int i;
    int width = 0, height = 0;                                     // 画像の幅と高さを格納する変数
    int pixel_x = 0, pixel_y = 0;                                  // ピクセルのx座標とy座標
    int r = 0, g = 0, b = 0, l = 0;                                // ピクセルの色情報と輝度情報
    int right_count_pixel[4] = {0};                                // 右側の各色のピクセルの数 0:赤 1:緑 2:青 3:黄
    int left_count_pixel[4] = {0};                                 // 左側の各色のピクセルの数
    int center_count_pixel[4] = {0};                               // 真ん中の各色のピクセルの数
    int count_sum_pixel = 0;                                       // 各色のピクセル数の合計 (左+正面+右)
    int display_count_pixel[4] = {0};                              // 表示させるための各色のピクセル数の合計 (左+正面+右)
    int random_num = 0;                                            // 乱数を保持する変数
    int mode = 0;                                                  // 今何色を追うのかというモード
    int reached_color_count = 0;                                   // ロボットが到達した色の数を表す
    int experience = 0;                                            // ロボットがある色を追っている時に貯まる経験値
    bool led_value[NUM_LEDS] = {false};                            // 各LEDの点灯消灯の 指令値 ( 初期値は消灯に設定 )
    bool random_bool = true;                                       // 乱数を更新するかどうかを判断する変数
    char display_color[4][6] = {"red", "green", "blue", "yellow"}; // 現在何色なのかを表示する
    char device_name[13];                                          // デバイス名を格納する文字列

    /* デバイスタグの宣言…デバイスを取り扱うためのタグを宣言する。 */
    WbDeviceTag motor[2];                        // 左・右車輪のモータ
    WbDeviceTag camera;                          // カメラ
    WbDeviceTag led[NUM_LEDS];                   // LED (NUM_LEDS 個　= 10個)
    WbDeviceTag distance_sensors[NUM_DIST_SENS]; // 距離センサ

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

    strcpy(device_name, "led0"); // デバイス名の設定
    for (i = 0; i < 10; i++)     // すべてのLEDについて繰り返す
    {
        device_name[3] = '0' + i;                  // 先頭から4文字目 ( 数字 ) の文字コードを設定
        led[i] = wb_robot_get_device(device_name); // i番目のLEDのタグの取得
        wb_led_set(led[i], led_value[i]);          // LEDを初期状態にする
    }
    printf("Initialize LEDs... done\n");

    strcpy(device_name, "ps0"); // デバイス名の設定
    for (i = 0; i < 8; i++)     // すべての距離センサについて繰り返す
    {
        device_name[2] = '0' + i; // 先頭から3文字目 ( 数字 ) の文字コードを設定
        distance_sensors[i] = wb_robot_get_device(device_name);
        // i番目の距離センサのタグの取得
        wb_distance_sensor_enable(distance_sensors[i], TIME_STEP);
        // TIME_STEP周期で動作開始
    }

    srand((unsigned int)time(NULL));   // 現在時刻の情報で初期化
    random_speed = (rand() % 8) * 0.1; // 0.0 ~ 0.7までの値を取得
    random_num = rand() % 4;           // 0 ~ 4までの乱数を取得
    printf("Initialize Random Number... done\n");

    /* シミュレーション開始 ( 以下無限ループ ) */
    while (wb_robot_step(TIME_STEP) != -1)
    {
        /* センサ情報の取得 */
        current_time = wb_robot_get_time();  // 現在時刻を取得する
        image = wb_camera_get_image(camera); // 画像情報のポインタを取得
        for (i = 0; i < 8; i++)              // すべての距離センサの測定値を取得
        {
            dist_value[i] = wb_distance_sensor_get_value(distance_sensors[i]);
        }

        /* 情報処理・制御計算 */
        right_count_pixel[0] = 0;
        left_count_pixel[0] = 0;
        center_count_pixel[0] = 0;

        /* 乱数を一秒に一回更新する */
        if ((int)current_time % 2 == 0 && random_bool == true)
        {
            random_bool = false;
            random_speed = (rand() % 8) * 0.1; // 0.0 ~ 0.7までの値を取得
            random_num = rand() % 4;
        }
        if ((int)current_time % 2 == 1 && random_bool == false)
        {
            random_bool = true;
        }

        // for文で座標を変化させてカメラ画像の全ピクセルについて調べる
        // x座標はpixel_x, y座標はpixel_y
        // pixel_x = 0, pixel_y = 0が画面左上端、
        // pixel_x=width-1, pixel_y=height-1が画面右下端

        // 画面の左3割を読み取る
        for (pixel_x = 0; pixel_x < width * 0.33; pixel_x++)
        {
            for (pixel_y = 0; pixel_y < height; pixel_y++)
            {
                // r = 赤成分 , g = 緑成分 , b = 青成分 , l = 輝度 , いずれも0～255を返す
                r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
                g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
                b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
                l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

                // たとえばrが40より大きく、g,bが20より小さピクセル を 赤 とする
                if (r > 40 && g < 20 && b < 20 && mode == 0)
                {
                    left_count_pixel[0]++;
                }
                // gが40より大きく、r,bが20より小さピクセル を 緑 とする
                if (r < 20 && g > 40 && b < 20 && mode == 1)
                {
                    left_count_pixel[0]++;
                }
                // bが40より大きく、r,gが20より小さピクセル を 青 とする
                if (r < 20 && g < 20 && b > 40 && mode == 2)
                {
                    left_count_pixel[0]++;
                }
                // r, gが40より大きく、bが20より小さピクセル を 黄 とする
                if (r > 40 && g > 40 && b < 20 && mode == 3)
                {
                    left_count_pixel[0]++;
                }
            }
        }
        // 画面の真ん中3割を読み取る
        for (pixel_x = width * 0.33; pixel_x < width * 0.66; pixel_x++)
        {
            for (pixel_y = 0; pixel_y < height; pixel_y++)
            {
                // r = 赤成分 , g = 緑成分 , b = 青成分 , l = 輝度 , いずれも0～255を返す
                r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
                g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
                b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
                l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

                // rが40より大きく、g,bが20より小さピクセル を 赤 とする
                if (r > 40 && g < 20 && b < 20 && mode == 0)
                {
                    center_count_pixel[0]++;
                }
                // gが40より大きく、r,bが20より小さピクセル を 緑 とする
                if (r < 20 && g > 40 && b < 20 && mode == 1)
                {
                    center_count_pixel[0]++;
                }
                // bが40より大きく、r,gが20より小さピクセル を 青 とする
                if (r < 20 && g < 20 && b > 40 && mode == 2)
                {
                    center_count_pixel[0]++;
                }
                // r, gが40より大きく、bが20より小さピクセル を 黄 とする
                if (r > 40 && g > 40 && b < 20 && mode == 3)
                {
                    center_count_pixel[0]++;
                }
            }
        }
        // 画面の右3割を読み取る
        for (pixel_x = width * 0.6; pixel_x < width; pixel_x++)
        {
            for (pixel_y = 0; pixel_y < height; pixel_y++)
            {
                r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
                g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
                b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
                l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

                // rが40より大きく、g,bが20より小さピクセル を 赤 とする
                if (r > 40 && g < 20 && b < 20 && mode == 0)
                {
                    right_count_pixel[0]++;
                }
                // gが40より大きく、r,bが20より小さピクセル を 緑 とする
                if (r < 20 && g > 40 && b < 20 && mode == 1)
                {
                    right_count_pixel[0]++;
                }
                // bが40より大きく、r,gが20より小さピクセル を 青 とする
                if (r < 20 && g < 20 && b > 40 && mode == 2)
                {
                    right_count_pixel[0]++;
                }
                // r, gが40より大きく、bが20より小さピクセル を 黄 とする
                if (r > 40 && g > 40 && b < 20 && mode == 3)
                {
                    right_count_pixel[0]++;
                }
            }
        }

        count_sum_pixel = left_count_pixel[0] + center_count_pixel[0] + right_count_pixel[0];

        /* ロボットの制動についての if文 */

        if (dist_value[0] > 200 || dist_value[1] > 300 || dist_value[6] > 300 || dist_value[7] > 200) // 前方のセンサのどちらかが100以上なら
        {
            speed[LEFT] = (random_speed - 1.0) * MAX_SPEED; // 左旋回を行う
            speed[RIGHT] = (random_speed + 0.3) * MAX_SPEED;
        }
        else if (count_sum_pixel < 2080 && center_count_pixel[0] > left_count_pixel[0] &&
                 center_count_pixel[0] > right_count_pixel[0] && center_count_pixel[0] > 10) // 左右より正面が赤が強かったら
        {
            experience++; // 経験値が貯まる
            display_count_pixel[0] = right_count_pixel[0];
            speed[LEFT] = random_speed * MAX_SPEED; // 正面に前進する
            speed[RIGHT] = random_speed * MAX_SPEED;
        }
        else if (count_sum_pixel < 2080 && right_count_pixel[0] > left_count_pixel[0] && right_count_pixel[0] > 10) // 右の方が赤が強かったら
        {
            experience++; // 経験値が貯まる
            display_count_pixel[0] = right_count_pixel[0];
            speed[LEFT] = (random_speed + 0.3) * MAX_SPEED; // 右前に前進する
            speed[RIGHT] = random_speed * MAX_SPEED;
        }
        else if (count_sum_pixel < 2080 && left_count_pixel[0] > right_count_pixel[0] && left_count_pixel[0] > 10) // 左の赤が強かったら
        {
            experience++; // 経験値が貯まる
            display_count_pixel[0] = left_count_pixel[0];
            speed[LEFT] = random_speed * MAX_SPEED; // 左前に前進する
            speed[RIGHT] = (random_speed + 0.3) * MAX_SPEED;
        }
        else if (count_sum_pixel > 2080) // 色[mode]が画面いっぱいであるなら
        {
            experience = 0;
            mode++;                // 次の色を追いかけるモードに変更する
            reached_color_count++; // 到達した色が増える
            display_count_pixel[0] = (right_count_pixel[0] + center_count_pixel[0] + left_count_pixel[0] / 3.0);
            speed[LEFT] = -random_speed * MAX_SPEED; // 旋回する
            speed[RIGHT] = random_speed * MAX_SPEED;
        }
        else if (experience > 0) // ある色を追いかけている途中で見失ったら
        {
            experience = 0; // 経験値を失う
            mode = 0;       // 最初の色からやり直す。
            reached_color_count = 0;
            speed[LEFT] = -random_speed * MAX_SPEED; // 旋回する
            speed[RIGHT] = random_speed * MAX_SPEED;
        }
        else if (reached_color_count == 4) // 全ての色を到達できたロボットは
        {
            if (dist_value[0] > 200 || dist_value[1] > 200 || dist_value[6] > 200 || dist_value[7] > 200) // 前方のセンサのどちらかが100以上なら
            {
                speed[LEFT] = -1.0 * MAX_SPEED; // 左旋回を行う
                speed[RIGHT] = 1.0 * MAX_SPEED;
            }
            else if (random_num == 0) // ランダムな動きをする様にする。
            {
                speed[LEFT] = random_speed * MAX_SPEED;
                speed[RIGHT] = random_speed * MAX_SPEED;
            }
            else if (random_num == 1)
            {
                speed[LEFT] = (random_speed + 0.3) * MAX_SPEED;
                speed[RIGHT] = random_speed * MAX_SPEED;
            }
            else if (random_num == 2)
            {
                speed[LEFT] = random_speed * MAX_SPEED;
                speed[RIGHT] = (random_speed + 0.3) * MAX_SPEED;
            }
            else if (random_num == 3)
            {
                speed[LEFT] = -random_speed * MAX_SPEED;
                speed[RIGHT] = random_speed * MAX_SPEED;
            }
        }
        else
        {
            speed[LEFT] = -random_speed * MAX_SPEED; // 旋回する
            speed[RIGHT] = random_speed * MAX_SPEED;
        }

        /* ロボットのLEDについての if文 */

        led_value[9] = true;

        if (reached_color_count == 0) // 到達した色が０個のとき
        {
            if ((int)current_time % 2 == 0)
            {
                led_value[0] = true; // 一秒ごとに点滅させる
            }
            else
            {
                led_value[0] = false;
            }
        }
        else if (reached_color_count == 1) // 到達した色が1個のとき
        {
            if ((int)current_time % 2 == 0) // 一秒ごとに点滅させる
            {
                led_value[0] = true;
                led_value[2] = true;
                led_value[6] = true;
            }
            else
            {
                led_value[2] = false;
                led_value[6] = false;
                led_value[0] = false;
            }
        }
        else if (reached_color_count == 2) // 到達した色が2個のとき
        {
            if ((int)current_time % 2 == 0) // 一秒ごとに点滅させる
            {
                led_value[0] = true;
                led_value[2] = true;
                led_value[3] = false;
                led_value[6] = true;
                led_value[7] = false;
            }
            else
            {
                led_value[0] = false;
                led_value[2] = false;
                led_value[3] = true;
                led_value[6] = false;
                led_value[7] = true;
            }
        }
        else if (reached_color_count == 3) // 到達した色が3個のとき
        {
            if ((int)current_time % 2 == 0) // 一秒ごとに点滅させる
            {
                led_value[0] = true;
                led_value[1] = false;
                led_value[2] = true;
                led_value[3] = false;
                led_value[5] = false;
                led_value[6] = true;
                led_value[7] = false;
            }
            else
            {
                led_value[0] = false;
                led_value[1] = true;
                led_value[2] = false;
                led_value[3] = true;
                led_value[5] = true;
                led_value[6] = false;
                led_value[7] = true;
            }
        }
        else if (reached_color_count == 4) // 到達した色が4個のとき
        {
            if ((int)current_time % 2 == 0) // 一秒ごとに点滅させる
            {
                led_value[0] = true;
                led_value[1] = false;
                led_value[2] = true;
                led_value[3] = false;
                led_value[4] = true;
                led_value[5] = false;
                led_value[6] = true;
                led_value[7] = false;
                led_value[8] = true;
            }
            else
            {
                led_value[0] = false;
                led_value[1] = true;
                led_value[2] = false;
                led_value[3] = true;
                led_value[4] = false;
                led_value[5] = true;
                led_value[6] = false;
                led_value[7] = true;
                led_value[8] = false;
            }
        }

        pixel_x = width * 0.5;
        pixel_y = height * 0.5;

        r = wb_camera_image_get_red(image, width, pixel_x, pixel_y);
        g = wb_camera_image_get_green(image, width, pixel_x, pixel_y);
        b = wb_camera_image_get_blue(image, width, pixel_x, pixel_y);
        l = wb_camera_image_get_gray(image, width, pixel_x, pixel_y);

        /* 制御コマンド実行 */
        for (int i = 0; i < 10; i++) // すべてのLEDについて繰り返す
        {
            wb_led_set(led[i], led_value[i]); // LEDをled_value[] どおりに光らせる
        }

        wb_motor_set_velocity(motor[LEFT], speed[LEFT]);
        wb_motor_set_velocity(motor[RIGHT], speed[RIGHT]);
        printf("TIME: %.3lf, SPEED: %.3lf, %.3lf\n", current_time, speed[LEFT], speed[RIGHT]); // 現在時刻を表示する
        printf("color: %s Pixel: %d\n", display_color[mode], display_count_pixel[0]);          // 色[mode] と判定されたピクセル数
        printf("rgb: %d, %d, %d, l: %d\n", r, g, b, l);                                        // 中心ピクセルのRGB値
        printf("Random Speed: %.1f\n", random_speed);                                          // ランダムスピードの値
        printf("Reached Color Count: %d\n", reached_color_count);                              // 到達した色の数
    };

    // 終了時のカメラ画像を保存する
    printf("wb_camera_save_image = %d\n", wb_camera_save_image(camera, "image.png", 100));

    /* WEBOTSの状態をクリーンアップする ( 終了処理 ) */
    wb_robot_cleanup();

    return 0;
}
