#include <M5Stack.h>

void setup() {
  // M5Stack を初期化
  M5.begin();
  // テキストの大きさを4倍に設定
  M5.Lcd.setTextSize(4);
  // M5Stackの画面に文字を表示
  M5.Lcd.println("Hello World!!");
}

void loop() {
  // M5Stackのボタンやスピーカなどの状態を更新
  M5.update();

    // ボタンB (中央) が1000ミリ秒押された時
  if (M5.BtnB.pressedFor(1000)) {
    M5.Lcd.clear(); // 画面をクリア（Hello Worldも消える）
  } 

   // ボタンA (左側) が押された時
  if (M5.BtnA.wasPressed()){
    M5.Lcd.fillScreen(RED);   // 背景を赤に設定
    M5.Lcd.setCursor(0, 0);       // カーソル位置をリセット
    M5.Lcd.println("Hello World!!");
  }

  // ボタンB (中央) が押された時
  if (M5.BtnB.wasPressed()) {
    M5.Lcd.fillScreen(GREEN); // 背景を緑に設定
    M5.Lcd.setCursor(0, 0);       // カーソル位置をリセット
    M5.Lcd.println("Hello World!!");
  }

  // ボタンC (右側) が押された時
  if (M5.BtnC.wasPressed()) {
    M5.Lcd.fillScreen(BLUE);  // 背景を青に設定
    M5.Lcd.setCursor(0, 0);       // カーソル位置をリセット
    M5.Lcd.println("Hello World!!");
  }

}
