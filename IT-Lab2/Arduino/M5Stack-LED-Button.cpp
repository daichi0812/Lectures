#include <M5Stack.h>

// ledという名前の変数を宣言し、今回使用するピン番号を代入
int led = 26;
int blinkDelay = 1000; // 初期の点滅間隔（1000ms）

void setup() {
  // M5Stackの初期化
  M5.begin();
  // 指定したGPIOピンを出力用として設定
  pinMode(led, OUTPUT);
}

void loop() {
  // ボタンの状態を更新
  M5.update();

  // Aボタンが押された場合、点滅速度を早くする
  if(M5.BtnA.wasPressed() && blinkDelay > 500){
    blinkDelay -= 500;
  }

  // Bボタンが押された場合、点滅速度を遅くする
  if(M5.BtnB.wasPressed()){
    blinkDelay += 500;
  }

  // Cボタンが押された場合、点滅速度をリセットする
  if(M5.BtnC.wasPressed()){
    blinkDelay = 1000;
  }

  // 指定したピンをHIGHに設定
  digitalWrite(led, HIGH);
  // blinkDelay ms待機
  delay(blinkDelay);
  // 指定したピンをLOWに設定
  digitalWrite(led, LOW);
  // blinkDelay ms待機
  delay(blinkDelay);

  M5.Lcd.clear(); // 画面をクリアしてから再描画
  M5.Lcd.setCursor(0, 0); // カーソル位置を x = 0, y = 0 で初期化
  M5.Lcd.setTextSize(4);  // テキストの大きさを4倍に設定
  M5.Lcd.printf("Blink Delay: %d ms", blinkDelay);  // 遅延を表示
}
