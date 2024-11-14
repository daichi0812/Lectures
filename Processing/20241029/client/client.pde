import processing.net.*;
import javax.swing.JOptionPane;

ArrayList<DisplayObject> objects = new ArrayList<DisplayObject>();
ArrayList<Explosion> explosions = new ArrayList<Explosion>();
int myID = -1;
String buffer = "";

Client client;
String serverIP = "";
int serverPort = 5204;

void setup(){
  size(800, 600);
  serverIP = promptServerIP();
  client = new Client(this, serverIP, serverPort);
}

void draw(){
  receiveGameState();

  noStroke();
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);

  for(int i = 0; i < objects.size(); i++){
    objects.get(i).Draw();
  }

  for(int i = explosions.size() -1; i >= 0; i--){
    Explosion exp = explosions.get(i);
    exp.Draw();
    if (exp.finished) {
      explosions.remove(i);
    }
  }
}

void keyPressed(){
  if (myID == -1) return; // IDを受信するまで待つ
  if (key == ' ') {
    String message = myID + " SPACE_PRESSED\n";
    client.write(message);
  }
  if (keyCode == LEFT) {
    String message = myID + " LEFT_PRESSED\n";
    client.write(message);
  }
  if (keyCode == RIGHT) {
    String message = myID + " RIGHT_PRESSED\n";
    client.write(message);
  }
}

void keyReleased(){
  if (myID == -1) return; // IDを受信するまで待つ
  if (keyCode == LEFT) {
    String message = myID + " LEFT_RELEASED\n";
    client.write(message);
  }
  if (keyCode == RIGHT) {
    String message = myID + " RIGHT_RELEASED\n";
    client.write(message);
  }
}

void receiveGameState(){
  // データを受信
  if (client.available() > 0) {
    String data = client.readString();
    if (data != null) {
      buffer += data;
      String[] lines = split(buffer, '\n');
      // 最後の要素が完全なメッセージでない場合、バッファに残す
      if (!buffer.endsWith("\n")) {
        buffer = lines[lines.length - 1];
        lines = subset(lines, 0, lines.length - 1);
      } else {
        buffer = "";
      }
      // オブジェクトリストをクリア
      objects.clear();
      explosions.clear();
      for (String line : lines) {
        parseGameObject(line.trim());
      }
    }
  }
}

void parseGameObject(String line) {
  if (line.startsWith("ID ")) {
    String[] parts = split(line, ' ');
    if (parts.length == 2) {
      myID = int(parts[1]);
      println("あなたのID: " + myID);
    }
  } else if (line.equals("END")) {
    // ゲーム状態の終了
  } else {
    String[] parts = split(line, ' ');
    if (parts.length == 0) return;
    String type = parts[0];
    if (type.equals("OBJECT")) {
      // この例ではOBJECTタイプは使用していないので無視
    } else if (type.equals("FIGHTER")) {
      if (parts.length >= 9) {
        int id = int(parts[1]);
        float x = float(parts[2]);
        float y = float(parts[3]);
        int R = int(parts[4]);
        int G = int(parts[5]);
        int B = int(parts[6]);
        int HP = int(parts[7]);
        int size = int(parts[8]);

        Fighter fighter = new Fighter();
        fighter.id = id;
        fighter.position.x = x;
        fighter.position.y = y;
        fighter.R = R;
        fighter.G = G;
        fighter.B = B;
        fighter.HP = HP;
        fighter.size = size;
        objects.add(fighter);
      }
    } else if (type.equals("BULLET")) {
      if (parts.length >= 8) {
        float x = float(parts[1]);
        float y = float(parts[2]);
        int R = int(parts[3]);
        int G = int(parts[4]);
        int B = int(parts[5]);
        int HP = int(parts[6]);
        float radius = float(parts[7]);

        Bullet bullet = new Bullet();
        bullet.position.x = x;
        bullet.position.y = y;
        bullet.R = R;
        bullet.G = G;
        bullet.B = B;
        bullet.HP = HP;
        bullet.radius = radius;
        objects.add(bullet);
      }
    } else if (type.equals("ENEMY")) {
      if (parts.length >= 9) {
        float x = float(parts[1]);
        float y = float(parts[2]);
        int R = int(parts[3]);
        int G = int(parts[4]);
        int B = int(parts[5]);
        int HP = int(parts[6]);
        int size_x = int(parts[7]);
        int size_y = int(parts[8]);

        Enemy enemy = new Enemy();
        enemy.position.x = x;
        enemy.position.y = y;
        enemy.R = R;
        enemy.G = G;
        enemy.B = B;
        enemy.HP = HP;
        enemy.size_x = size_x;
        enemy.size_y = size_y;
        objects.add(enemy);
      }
    } else if (type.equals("EXPLOSION")) {
      if (parts.length >= 4) {
        float x = float(parts[1]);
        float y = float(parts[2]);
        float radius = float(parts[3]);

        Explosion explosion = new Explosion(x, y);
        explosion.radius = radius;
        explosions.add(explosion);
      }
    }
  }
}

String promptServerIP() {
  String ip = "";
  while (ip.equals("")) {
    ip = JOptionPane.showInputDialog("接続先のサーバーIPアドレスを入力してください:");
    if (ip == null) {
      exit(); // ユーザーがキャンセルした場合、プログラムを終了
    }
  }
  return ip;
}

// クラス定義

class DisplayObject{
  PVector position;
  PVector move;
  int R, G, B;
  int HP;
  int syurui;

  DisplayObject(){
    position = new PVector(0, 0);
    move = new PVector(0, 0);
  }

  void Draw(){}
}

class Fighter extends DisplayObject{
  int size;
  int moveDirection = 0;
  int id;

  Fighter(){
    super();
    size = 20;
    position.x = width / 2 - size / 2;
    position.y = height - 80;
    move.x = 5; // 移動速度をサーバーと合わせる
    move.y = 0;
    R = 255;
    G = 255;
    B = 255;
    syurui = 0;
    HP = 20;
    // クライアント側ではidをここで割り当てる必要はありません
  }

  void Draw(){
    fill(R, G, B);
    rect(position.x, position.y, size, 40);
  }
}

class Bullet extends DisplayObject{
  float radius;

  Bullet(){
    super();
    syurui = 1;
    // クライアント側ではBulletの位置や色はサーバーから受信したデータで設定します
  }

  void Draw(){
    fill(R, G, B);
    ellipse(position.x, position.y, radius, radius);
  }
}

class Enemy extends DisplayObject{
  int size_x;
  int size_y;

  Enemy(){
    super();
    syurui = 2;
    // クライアント側ではEnemyの位置や色はサーバーから受信したデータで設定します
  }

  void Draw(){
    fill(R, G, B);
    rect(position.x, position.y, size_x, size_y);
  }
}

class Explosion{
  float x, y;
  float radius;
  int maxRadius = 50;
  boolean finished;

  Explosion(float _x, float _y){
    x = _x;
    y = _y;
    radius = 10;
    finished = false;
  }

  void Draw(){
    if(!finished){
      noFill();
      stroke(255, 0, 0, 255 - (radius / maxRadius) * 255);
      strokeWeight(2);
      ellipse(x, y, radius * 2, radius * 2);
      radius += 2;
      if(radius > maxRadius){
        finished = true;
      }
    }
  }

  boolean isFinished() {
    return finished;
  }
}
