int BallNum = 100;
Ball[] balls = new Ball[BallNum];

void setup(){
  size(800, 600);
  for(int i = 0; i < 10; i++){
    balls[i] = new Ball();
  }
  for(int i = 10; i < balls.length; i++){
    PVector pos = new PVector(random(0, width), random(0, height));
    PVector mov = new PVector(random(3, 10), random(3, 10));
    balls[i] = new Ball(pos, mov, 20, 200, 200, 200);
  }
}

void draw(){
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  for(int i = 0; i < balls.length; i++){
    balls[i].Draw((int)random(10, 255), (int)random(10, 255), (int)random(10, 255));
  }
}

class Ball{
  PVector position;
  PVector move;
  float radius;
  int R, G, B;

  Ball(){
    position = new PVector(random(0, width), random(0, height));
    move = new PVector(random(3, 10), random(3, 10));
    R = (int)random(10, 256);
    G = (int)random(10, 256);
    B = (int)random(10, 256);
    radius = random(10, 30);
  }
  
  Ball(PVector _position, PVector _move, float _radius, int _R, int _G, int _B){
    position = _position;
    move = _move;
    radius = _radius;
    R = _R;
    G = _G;
    B = _B;
  }

  void Draw(){
    position.add(move);
    if(position.x < radius || position.x > width - radius){
      position.x = constrain(position.x, radius, width - radius);
      move.x *= -1;
    }
    if(position.y < radius || position.y > height- radius){
      position.y = constrain(position.y, radius, height - radius);
      move.y *= -1;
    }
    
    fill(R, G, B);
    ellipse(position.x, position.y, radius, radius);
  }
  
    void Draw(int _R, int _G, int _B){
    R = _R;
    G = _G;
    B = _B;
    
    this.Draw();
  }
}
