#include <M5Stack.h>

/*
  ボタン3を押すことによってモードを1から5まで選択可能
  モード１: Button1を押すとLED1が光る. Button2を押すとLED2が光る
  モード2 : 交互点滅. Button1, Button2どちらかを押すことで片方だけ速い間隔で点滅
  モード3 : 同時点滅. Button1, Button2どちらかを押すことで片方だけ速い間隔で点滅
  モード4 : 波形点滅. Button1, Button2どちらかを押すことで片方だけ速い間隔で点滅
  モード5 : ランダム点滅. Button1, Button2どちらかを押すことで片方だけ速い間隔で点滅
*/

// LEDとボタンのピン番号を宣言
int led1 = 26;
int led2 = 16;
int button1 = 5;
int button2 = 2;
int button3 = 17;

// モードと点滅速度を管理する変数を宣言
int mode = 1;
bool led1State = false;
bool led2State = false;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
int interval1 = 500; // 初期の点滅間隔（ミリ秒）
int interval2 = 1000; // 初期の点滅間隔（ミリ秒）

void setup() {
  // M5Stackを初期化
  M5.begin();
  // LEDを出力モードに設定
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  // ボタンを入力モードに設定
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
}

void loop() {
  // 各ボタンの状態を読み取る
  int button1State = digitalRead(button1);
  int button2State = digitalRead(button2);
  int button3State = digitalRead(button3);

  // Button3でモード切り替え
  if (button3State == HIGH) {
    mode = (mode % 5) + 1; // モード1〜5を循環
    delay(300); // モード変更時のデバウンス用ディレイ
  }

  // モードによって動作を変更
  switch (mode) {
    case 1:
      // モード1: Button1でLED1、Button2でLED2を点灯
      digitalWrite(led1, button1State == HIGH ? HIGH : LOW);
      digitalWrite(led2, button2State == HIGH ? HIGH : LOW);
      break;

    case 2:
      // モード2: LED1とLED2が交互点滅
      handleAlternatingBlink(button1State, button2State);
      break;

    case 3:
      // モード3: LED1とLED2が同時点滅
      handleSimultaneousBlink(button1State, button2State);
      break;

    case 4:
      // モード4: LED1とLED2が波形点滅
      handleWavePattern(button1State, button2State);
      break;

    case 5:
      // モード5: LED1とLED2がランダムに点滅
      handleRandomBlink(button1State, button2State);
      break;
  }

  // 画面にモードとボタンの状態を表示
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("Mode: %d\n", mode);
  M5.Lcd.printf("Button1: %s\n", button1State == HIGH ? "Pressed" : "Released");
  M5.Lcd.printf("Button2: %s\n", button2State == HIGH ? "Pressed" : "Released");

  delay(50); // 安定性のために少し待機
}

// モード2の交互点滅を実行する関数
void handleAlternatingBlink(int button1State, int button2State) {
  unsigned long currentMillis = millis();
  int speed = (button1State == HIGH && button2State == HIGH) ? 100 : interval1;

  if (button1State == HIGH) {
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    delay(200);
  } else if (button2State == HIGH) {
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
  } else {
    if (currentMillis - previousMillis1 >= speed) {
      previousMillis1 = currentMillis;
      led1State = !led1State;
      digitalWrite(led1, led1State ? HIGH : LOW);
      digitalWrite(led2, !led1State ? HIGH : LOW);
    }
  }
}

// モード3の同時点滅を実行する関数
void handleSimultaneousBlink(int button1State, int button2State) {
  unsigned long currentMillis = millis();
  int speed = (button1State == HIGH && button2State == HIGH) ? 100 : interval2;

  if (button1State == HIGH) {
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    delay(200);
  } else if (button2State == HIGH) {
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
  } else {
    if (currentMillis - previousMillis2 >= speed) {
      previousMillis2 = currentMillis;
      led1State = !led1State;
      digitalWrite(led1, led1State ? HIGH : LOW);
      digitalWrite(led2, led1State ? HIGH : LOW);
    }
  }
}

// モード4の波形点滅を実行する関数
void handleWavePattern(int button1State, int button2State) {
  unsigned long currentMillis = millis();
  int speed = (button1State == HIGH && button2State == HIGH) ? 100 : interval2;

  if (button1State == HIGH) {
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);
  } else if (button2State == HIGH) {
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led2, LOW);
    delay(500);
  } else {
    if (currentMillis - previousMillis2 >= speed) {
      previousMillis2 = currentMillis;
      led1State = !led1State;
      digitalWrite(led1, led1State ? HIGH : LOW);
      delay(50); // 波形のための微調整
      digitalWrite(led2, led1State ? HIGH : LOW);
    }
  }
}

// モード5のランダム点滅を実行する関数
void handleRandomBlink(int button1State, int button2State) {
  unsigned long currentMillis = millis();
  int speed = (button1State == HIGH && button2State == HIGH) ? 100 : interval2;

  if (button1State == HIGH) {
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    delay(200);
  } else if (button2State == HIGH) {
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
  } else {
    if (currentMillis - previousMillis2 >= speed) {
      previousMillis2 = currentMillis;
      digitalWrite(led1, random(0, 2) ? HIGH : LOW);
      digitalWrite(led2, random(0, 2) ? HIGH : LOW);
    }
  }
}