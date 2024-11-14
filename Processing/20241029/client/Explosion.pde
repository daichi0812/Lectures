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
}
