class Ball extends DisplayObject{
  PVector move;
  float radius;

  Ball(){
    super();
    position.x = (int)random(0, width);
    position.y = (int)random(0, height);
    move = new PVector(random(3, 10), random(3, 10));
    radius = random(10, 30);
  }

  void Draw(){
    super.Draw();
    position.add(move);
    if(position.x < radius || position.x > width - radius){
      position.x = constrain(position.x, radius, width - radius);
      move.x *= -1;
    }
    if(position.y < radius || position.y > height- radius){
      position.y = constrain(position.y, radius, height - radius);
      move.y *= -1;
    }
    
    ellipse(position.x, position.y, radius, radius);
  }
}
