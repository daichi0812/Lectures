class Bullet extends DisplayObject{
  float radius;
  Enemy ownerEnemy; 

  // Constructor for player's bullet (without direction)
  Bullet(Fighter _fighter){
    super();
    syurui = 1; // 1 is player's bullet
    radius = 5;
    R = 255;
    G = 255;
    B = 0;
    move.x = 0;
    move.y = -10;
    position.x = _fighter.position.x + _fighter.img.width / 2;
    position.y = _fighter.position.y;
    HP = 1;
    ownerEnemy = null;
  }

  // Constructor for player's bullet (with direction)
  Bullet(Fighter _fighter, PVector direction){
    super();
    syurui = 1; // 1 is player's bullet
    radius = 5;
    R = 255;
    G = 255;
    B = 0;
    move = direction.copy();
    move.mult(10); // Adjust speed
    position.x = _fighter.position.x + _fighter.img.width / 2;
    position.y = _fighter.position.y + _fighter.img.height / 2;
    HP = 1;
    ownerEnemy = null;
  }

  // Constructor for enemy's bullet
  Bullet(Fighter _fighter, Enemy _enemy){
    super();
    syurui = 3; // 3 is enemy's bullet
    radius = 5; 
    R = 255;
    G = 0;
    B = 0; 
    position.x = _enemy.position.x + _enemy.img.width / 2;
    position.y = _enemy.position.y + _enemy.img.height;

    // Calculate moving vector
    PVector direction = PVector.sub(_fighter.position.copy(), position.copy());
    direction.normalize();
    direction.mult(5); // Speed
    move = direction;
    HP = 1;
    ownerEnemy = _enemy;
  }

  void Draw(){
    super.Draw();
    fill(R, G, B);
    ellipse(position.x, position.y, radius * 2, radius * 2); 
    position.add(move);
  }
}
