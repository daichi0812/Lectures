#include <M5Stack.h>

// ledとbuttonという名前の変数を宣言し、今回使用するピン番号を代入
int led = 26;
int button = 5;

void setup() {
  // M5Stackを初期化
  M5.begin();

  // 指定したGPIOピンを出力用として設定
  pinMode(led, OUTPUT);
  // 指定したGPIOピンを入力用として設定
  pinMode(button, INPUT);
}

void loop() {
  // ボタンの状態を読み取る
  int buttonState = digitalRead(button);

  // ボタンが押されている（HIGHの状態）の場合
  if (buttonState == HIGH) {
    digitalWrite(led, HIGH); // LEDを点灯
  } else {
    digitalWrite(led, LOW);  // LEDを消灯
  }

  M5.Lcd.clear(); // 画面をクリアしてから再描画
  M5.Lcd.setCursor(0, 0); // カーソル位置を x = 0, y = 0 で初期化
  M5.Lcd.setTextSize(4);  // テキストの大きさを4倍に設定
  
  if(buttonState == HIGH){
    M5.Lcd.printf("Button Clicked");
  }else{
    M5.Lcd.printf("Button Released");
  }

  delay(100); // 状態の確認を安定させるために少し待機
}
