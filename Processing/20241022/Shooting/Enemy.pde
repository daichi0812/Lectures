class Enemy extends DisplayObject{
  int size_x;
  int size_y;
  
  Enemy(){
    super();
    // set random size
    size_x = (int)random(30, 50);
    size_y = (int)random(30, 50);
    // set color
    R = (int)random(1, 256);
    G = (int)random(1, 256);
    B = (int)random(1, 256);
    // set syurui
    syurui = 2;
    // set HP
    HP = (int)random(1, 10);
    // set direction
    move.x = random(-1, 1);
    move.y = random(0.1, 1);
    // set initial position
    position.x = random(0, width - size_x);
    position.y = 0.0;
  }
  
  void Draw(){
    noStroke();
    super.Draw();
    
    position.add(move);
    
    // judge collision
    if(position.x < 0 || position.x > width - size_x){
      move.x *= -1;
    }
    
    fill(R, G, B);
    rect(position.x, position.y, size_x, size_y);
  }
}
