class Fighter extends DisplayObject{
  int size;
  int moveDirection = 0;
  int id; // ユニークなID

  Fighter(){
    super();
    size = 20;
    position.x = width / 2 - size / 2;
    position.y = height - 80;
    move.x = 5; // 移動速度を調整
    move.y = 0;
    R = 255;
    G = 255;
    B = 255;
    syurui = 0;
    HP = 20;
    id = nextFighterID++; // ユニークなIDを割り当て
  }

  void Draw(){
    super.Draw();
    position.x += move.x * moveDirection;
    position.x = constrain(position.x, 0, width - size);
    fill(R, G, B);
    rect(position.x, position.y, size, 40);
  }

  String toString() {
    return "FIGHTER " + id + " " + position.x + " " + position.y + " " + R + " " + G + " " + B + " " + HP + " " + size;
  }
}
