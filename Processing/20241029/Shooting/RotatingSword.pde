class RotatingSword{
  Fighter fighter;
  float angle;
  float speed;
  float radius;
  int damage;
  int numSwords = 1;

  RotatingSword(Fighter _fighter){
    fighter = _fighter;
    angle = 0;
    speed = 0.05;
    radius = 50;
    damage = 1;
  }

  void update(){
    angle += speed;
  }

  void draw(){
    for(int i = 0; i < numSwords; i++){
      float angleOffset = TWO_PI / numSwords * i;
      float currentAngle = angle + angleOffset;
      float x = fighter.position.x + fighter.img.width / 2 + cos(currentAngle) * radius;
      float y = fighter.position.y + fighter.img.height / 2 + sin(currentAngle) * radius;
      fill(100, 100, 255);
      ellipse(x, y, 20, 20); // Draw the sword
    }
  }

  boolean hit(Enemy enemy){
    for(int i = 0; i < numSwords; i++){
      float angleOffset = TWO_PI / numSwords * i;
      float currentAngle = angle + angleOffset;
      float x = fighter.position.x + fighter.img.width / 2 + cos(currentAngle) * radius;
      float y = fighter.position.y + fighter.img.height / 2 + sin(currentAngle) * radius;
      if(x > enemy.position.x && x < enemy.position.x + enemy.img.width &&
         y > enemy.position.y && y < enemy.position.y + enemy.img.height){
        // Remove enemy's bullets
        removeEnemyBullets(enemy);
        return true;
      }
    }
    return false;
  }

  // Method to remove enemy's bullets
  void removeEnemyBullets(Enemy enemy){
    for(int i = objects.size() - 1; i >= 0; i--){
      DisplayObject obj = objects.get(i);
      if(obj.syurui == 3){ // Enemy's bullet
        Bullet bullet = (Bullet)obj;
        if(bullet.ownerEnemy == enemy){
          objects.remove(i);
        }
      }
    }
  }

  void upgrade(){
    damage += 1;
    speed += 0.02;
    radius += 10;
    numSwords += 1; // Increase number of swords
  }
}
