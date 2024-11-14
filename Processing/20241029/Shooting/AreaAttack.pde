class AreaAttack extends DisplayObject{
  float radius;
  float maxRadius;
  float expansionRate;
  Fighter fighter;

  AreaAttack(Fighter _fighter){
    super();
    syurui = 4; // 4 is area attack
    fighter = _fighter;
    position.x = fighter.position.x + fighter.img.width / 2;
    position.y = fighter.position.y + fighter.img.height / 2;
    radius = 0;
    maxRadius = 200; // Maximum radius
    expansionRate = 5; // Expansion speed
    HP = 1;
  }

  void Draw(){
    noFill();
    stroke(255, 165, 0, 255 - (radius / maxRadius) * 255);
    strokeWeight(3);
    ellipse(position.x, position.y, radius * 2, radius * 2);
    radius += expansionRate;
    if(radius > maxRadius){
      HP = 0; // Remove
    }
  }
}
