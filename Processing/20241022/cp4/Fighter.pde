class Fighter extends DisplayObject{
  int size;
  int moveDirection = 0; // -1 is left, 1 is right, 0 is no moving
  
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
    syurui = 0; // 0 = Fighter
    HP = 20;
  }
  
  void Draw(){
    super.Draw();
    position.x += move.x * moveDirection;
    
    // no collision on the wall
    position.x = constrain(position.x, 0, width - size);
    
    fill(R, G, B);
    rect(position.x, position.y, size, 40);
  }
}
