#include <M5Stack.h>

// RGB LEDのピン番号を指定
int redPin = 17;  // 赤色
int greenPin = 2;  // 緑色
int bluePin = 5;   // 青色

// ボタンのピン番号を指定
int button1 = 26;  // 赤色調整ボタン
int button2 = 35;  // 緑色調整ボタン
int button3 = 36;  // 青色調整ボタン

// RGB値
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// 増加値
const int increment = 50;

void setup(){
  M5.begin();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
}

void loop(){
  M5.update();

  // ボタンの状態を取得
  bool button1State = digitalRead(button1);
  bool button2State = digitalRead(button2);
  bool button3State = digitalRead(button3);

  // 本体ボタンでRGB値を50ずつ増やす
  if (M5.BtnA.wasPressed()) {
    if(redValue >= 250){
      redValue -= 250;
    } else{
      redValue += increment;
    }
  }
  if (M5.BtnB.wasPressed()) {
    if(greenValue >= 250){
      greenValue -= 250;
    } else{
      greenValue += increment;
    }
  }
  if (M5.BtnC.wasPressed()) {
    if(blueValue >= 250){
      blueValue -= 250;
    } else{
      blueValue += increment;
    }
  }

  // ボタン1が押されている時だけ赤色LEDを点灯
  if (button1State == HIGH) { // ボタン1が押された時
    analogWrite(redPin, redValue);  // 赤色LEDを点灯
  } else {
    analogWrite(redPin, 0);  // 赤色LEDを消灯
  }

  // ボタン2が押されている時だけ緑色LEDを点灯
  if (button2State == HIGH) { // ボタン2が押された時
    analogWrite(greenPin, greenValue); // 緑色LEDを点灯
  } else {
    analogWrite(greenPin, 0);  // 緑色LEDを消灯
  }

  // ボタン3が押されている時だけ青色LEDを点灯
  if (button3State == HIGH) { // ボタン2が押された時
    analogWrite(bluePin, blueValue); // 青色LEDを点灯
  } else {
    analogWrite(bluePin, 0);  // 青色LEDを消灯
  }

  // RGB値を本体画面に表示（該当部分をクリアしてから表示）
  M5.Lcd.fillRect(0, 0, 320, 20, BLACK); // 上部の表示エリアをクリア
  M5.Lcd.setCursor(10, 10);
  // RGB値を本体画面に表示
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("R: %d \n", redValue);
  M5.Lcd.printf("G: %d \n", greenValue);
  M5.Lcd.printf("B: %d", blueValue);

  delay(100);
}