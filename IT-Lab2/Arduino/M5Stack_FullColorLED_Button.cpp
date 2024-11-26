#include <M5Stack.h>

// RGB LEDのピン番号を指定
int redPin = 17;  // 赤色
int greenPin = 2;  //緑色
int bluePin = 5; //青色

// ボタンのピン番号を指定
int button1 = 26; // 赤色調整ボタン
int button2 = 35; // 緑色調整ボタン
int button3 = 36; // 青色調整ボタン

void setup(){
  // RGB LEDピンを出力に設定
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // ボタンピンを入力に設定
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  // LEDを初期状態で消灯
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void loop(){
  // ボタンの状態を取得
  bool button1State = digitalRead(button1);
  bool button2State = digitalRead(button2);
  bool button3State = digitalRead(button3);

  // ボタン1が押されている時だけ赤色LEDを点灯
  if (button1State == HIGH) { // ボタン1が押された時
    digitalWrite(redPin, HIGH); // 赤色LEDを点灯
  } else {
    digitalWrite(redPin, LOW);  // 赤色LEDを消灯
  }

  // ボタン2が押されている時だけ緑色LEDを点灯
  if (button2State == HIGH) { // ボタン2が押された時
    digitalWrite(greenPin, HIGH); // 緑色LEDを点灯
  } else {
    digitalWrite(greenPin, LOW);  // 緑色LEDを消灯
  }

  // ボタン3が押されている時だけ青色LEDを点灯
  if (button3State == HIGH) { // ボタン2が押された時
    digitalWrite(bluePin, HIGH); // 青色LEDを点灯
  } else {
    digitalWrite(bluePin, LOW);  // 青色LEDを消灯
  }

  delay(10);
}