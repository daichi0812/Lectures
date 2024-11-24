// led という名前の変数を宣言し、今回使用するピン番号を代入
int led = 26;

void setup() {
  // 指定したGPIOピンを出力用として設定
  pinMode(led, OUTPUT);

}

void loop() {
  // 指定したピンをHIGHに設定
  digitalWrite(led, HIGH);
  // 1000ミリ秒待機
  delay(1000);
  // 指定したピンをLOWに設定
  digitalWrite(led, LOW);
  // 1000ミリ秒待機
  delay(1000);

}
