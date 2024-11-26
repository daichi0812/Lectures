import processing.net.*;

ArrayList<DisplayObject> objects = new ArrayList<DisplayObject>();
ArrayList<Explosion> explosions = new ArrayList<Explosion>();
ArrayList<Client> clients = new ArrayList<Client>();
ArrayList<Fighter> fighters = new ArrayList<Fighter>();

Server server;

void setup(){
  size(800, 600);
  // サーバーをポート5204で開始
  server = new Server(this, 5204);
}

void draw(){
  // 新しいクライアントの接続を受け入れる
  Client thisClient = server.available();
  while (thisClient != null) {
    clients.add(thisClient);
    // 新しいFighterを作成し、クライアントに割り当てる
    Fighter newFighter = new Fighter();
    objects.add(newFighter);
    fighters.add(newFighter);
    // クライアントに自身のIDを送信
    int id = fighters.size() - 1;
    thisClient.write("ID " + id + "\n");
    println("新しいクライアントが接続されました。ID: " + id);
    thisClient = server.available();
  }
  
  // クライアントからの入力を読み取る
  for (int i = 0; i < clients.size(); i++) {
    Client c = clients.get(i);
    while (c.available() > 0) {
      String input = c.readStringUntil('\n');
      if (input != null) {
        input = input.trim();
        String[] parts = input.split(" ");
        if (parts.length >= 2) {
          int id = int(parts[0]);
          String command = parts[1];
          if (id >= 0 && id < fighters.size()) {
            Fighter fighter = fighters.get(id);
            if (command.equals("LEFT_PRESSED")) {
              fighter.moveDirection = -1;
            } else if (command.equals("RIGHT_PRESSED")) {
              fighter.moveDirection = 1;
            } else if (command.equals("LEFT_RELEASED")) {
              if (fighter.moveDirection == -1) {
                fighter.moveDirection = 0;
              }
            } else if (command.equals("RIGHT_RELEASED")) {
              if (fighter.moveDirection == 1) {
                fighter.moveDirection = 0;
              }
            } else if (command.equals("SPACE_PRESSED")) {
              // 弾を発射
              objects.add(new Bullet(fighter));
            }
          }
        }
      }
    }
  }
  
  // ゲーム状態を更新
  noStroke();
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  
  if(random(100) < 5){
    objects.add(new Enemy());
  }
  
  for(int i = 0; i < objects.size(); i++){
    objects.get(i).Draw();
    
    if(objects.get(i).syurui == 1 && objects.get(i).position.y < 0){
      objects.remove(i);
      i--;
    }
    
    if(objects.get(i).syurui == 2 && objects.get(i).position.y > height){
      objects.remove(i);
      i--;
    }
  }
  
  for(int i = 0; i < explosions.size(); i++){
    explosions.get(i).Draw();
    if(explosions.get(i).isFinished()){
      explosions.remove(i);
      i--;
    }
  }
  
  Collision();
  
  // クライアントにゲーム状態を送信
  String gameState = serializeGameState();
  for (int i = 0; i < clients.size(); i++) {
    Client c = clients.get(i);
    c.write(gameState);
  }
}

void Collision(){
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).syurui == 1){
      Bullet bullet = (Bullet)objects.get(i);
      for(int j = 0; j < objects.size(); j++){
        if(objects.get(j).syurui == 2){
          Enemy enemy = (Enemy)objects.get(j);
          
          if(enemy.position.x < bullet.position.x && bullet.position.x < enemy.position.x + enemy.size_x &&
             enemy.position.y < bullet.position.y && bullet.position.y < enemy.position.y + enemy.size_y){
               enemy.HP -= bullet.HP;
               bullet.HP--;
               
               if(enemy.HP <= 0){
                 explosions.add(new Explosion(enemy.position.x + enemy.size_x / 2, enemy.position.y + enemy.size_y / 2));
               }
          }
        }
      }
    }
  }
  
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).syurui == 1 || objects.get(i).syurui == 2){
      if(objects.get(i).HP <= 0){
        objects.remove(i);
        i--;
      }
    }
  }
}

String serializeGameState() {
  String state = "";
  // 全てのオブジェクトをシリアライズ
  for (int i = 0; i < objects.size(); i++) {
    DisplayObject obj = objects.get(i);
    String objString = obj.toString();
    state += objString + "\n";
  }
  // 爆発をシリアライズ
  for (int i = 0; i < explosions.size(); i++) {
    Explosion exp = explosions.get(i);
    String expString = exp.toString();
    state += expString + "\n";
  }
  state += "END\n";
  return state;
}

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
  
  String toString() {
    return "OBJECT " + syurui + " " + position.x + " " + position.y + " " + R + " " + G + " " + B + " " + HP;
  }
}

class Fighter extends DisplayObject{
  int size;
  int moveDirection = 0;
  
  Fighter(){
    super();
    size = 20;
    position.x = width / 2 - size / 2;
    position.y = height - 80;
    move.x = 15;
    move.y = 0;
    R = 255;
    G = 255;
    B = 255;
    syurui = 0;
    HP = 20;
  }
  
  void Draw(){
    super.Draw();
    position.x += move.x * moveDirection;
    position.x = constrain(position.x, 0, width - size);
    fill(R, G, B);
    rect(position.x, position.y, size, 40);
  }
  
  String toString() {
    int id = fighters.indexOf(this);
    return "FIGHTER " + id + " " + position.x + " " + position.y + " " + R + " " + G + " " + B + " " + HP + " " + size;
  }
}

class Bullet extends DisplayObject{
  float radius;
  
  Bullet(Fighter _fighter){
    super();
    syurui = 1;
    radius = 10;
    R = 255;
    G = 80;
    B = 0;
    move.x = 0;
    move.y = -30;
    position.x = _fighter.position.x + _fighter.size / 2;
    position.y = _fighter.position.y - radius;
    HP = 1;
  }
  
  void Draw(){
    super.Draw();
    fill(R, G, B);
    ellipse(position.x, position.y, radius, radius);
    position.add(move);
  }
  
  String toString() {
    return "BULLET " + position.x + " " + position.y + " " + R + " " + G + " " + B + " " + HP + " " + radius;
  }
}

class Enemy extends DisplayObject{
  int size_x;
  int size_y;
  
  Enemy(){
    super();
    size_x = (int)random(30, 50);
    size_y = (int)random(30, 50);
    R = (int)random(1, 256);
    G = (int)random(1, 256);
    B = (int)random(1, 256);
    syurui = 2;
    HP = (int)random(1, 10);
    move.x = random(-1, 1);
    move.y = random(0.1, 1);
    position.x = random(0, width - size_x);
    position.y = 0.0;
  }
  
  void Draw(){
    noStroke();
    super.Draw();
    position.add(move);
    if(position.x < 0 || position.x > width - size_x){
      move.x *= -1;
    }
    fill(R, G, B);
    rect(position.x, position.y, size_x, size_y);
  }
  
  String toString() {
    return "ENEMY " + position.x + " " + position.y + " " + R + " " + G + " " + B + " " + HP + " " + size_x + " " + size_y;
  }
}

class Explosion{
  float x, y;
  float radius;
  int maxRadius;
  boolean finished;
  
  Explosion(float _x, float _y){
    x = _x;
    y = _y;
    radius = 10;
    maxRadius = 50;
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
  
  String toString() {
    return "EXPLOSION " + x + " " + y + " " + radius;
  }
}
