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
  // put your main code here, to run repeatedly:

}
