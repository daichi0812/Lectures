class Bullet extends DisplayObject{
  float radius;
  
  Bullet(Fighter _fighter){
    super();
    syurui = 1; // 1 is Bullet;
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
}
