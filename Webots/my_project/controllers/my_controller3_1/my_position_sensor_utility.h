/*
 * File:         e-puck用コントローラ例・3-1用ヘッダファイル
 * Date:         2019/5/7
 * Description:  角度センサおよびそれに関わる諸関数の宣言
 */

/* 左右の車輪の角度センサ用構造体の宣言 */
typedef struct{
  WbDeviceTag tag[2];	// デバイスタグ
  double position[2];	// 角度センサの測定値[rad]
  double pre_pos[2];	// 前回取得した角度センサの値[rad]
  WbRobotMode mode;		// ロボットの動作モード
} POS_SENSOR;

/* 角度センサを初期化 */
POS_SENSOR initialize_position_sensors(void);

/* 角度センサの測定値を取得 */
POS_SENSOR get_position_sensors(POS_SENSOR pos_sensor);

/* 角度センサの測定値をリセット */
POS_SENSOR reset_position_sensors(POS_SENSOR pos_sensor);

/* 角度センサの測定値を元にロボットの移動距離を計算 */
double compute_length(POS_SENSOR pos_sensor);

/* 角度センサの測定値を元にロボットの旋回角度を計算 */
double compute_orientation(POS_SENSOR pos_sensor);

