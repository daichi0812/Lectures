#include <M5Stack.h>
#include <Wire.h>

int trackNumber = 1;
bool isPlaying = false;

void setup() {
  M5.begin();
  Serial.begin(115200);
  
  // 初期表示
  displayStatus();
}

void loop() {
  M5.update();

  // ボタンA: 次のトラック
  if (M5.BtnA.wasPressed()) {
    trackNumber = (trackNumber < 20) ? trackNumber + 1 : 1;
    isPlaying = false;  // Pauseにする
    displayStatus();
    Serial.println("next");
  }

  // ボタンB: 前のトラック
  if (M5.BtnB.wasPressed()) {
    trackNumber = (trackNumber > 1) ? trackNumber - 1 : 20;
    isPlaying = false;  // Pauseにする
    displayStatus();
    Serial.println("prev");
  }

  // ボタンC: 再生/一時停止切り替え
  if (M5.BtnC.wasPressed()) {
    isPlaying = !isPlaying;  // 再生状態を切り替える
    displayStatus();
    Serial.println("toggle");
  }
}

void displayStatus() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(3);
  
  M5.Lcd.printf("Track: %d\n", trackNumber);
  M5.Lcd.printf(isPlaying ? "playing" : "pause");
}