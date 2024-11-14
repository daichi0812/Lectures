class Fighter extends DisplayObject{
  PImage img;
  int maxHP = 2000;
  int bulletDamage = 1;
  RotatingSword rotatingSword;
  float speed = 10; // Player's movement speed

  int spreadLevel = 0; // Level of spread shot
  boolean hasAreaAttack = false; // Whether area attack is available
  int areaAttackCooldown = 0; // Cooldown for area attack

  boolean hasShield = false; // Whether shield is active
  int shieldHP; // Shield durability

  Fighter(){
    super();
    img = fighterImage;
    position.x = width / 2 - img.width / 2;
    position.y = height - img.height - 10; 
    syurui = 0; // 0 = Player
    HP = maxHP;
  }

  void Draw(){
    super.Draw();
    if(gameState.equals("playing")){ // Update position only during gameplay
      if(moveLeft){
        position.x -= speed;
      }
      if(moveRight){
        position.x += speed;
      }
      if(moveUp){
        position.y -= speed;
      }
      if(moveDown){
        position.y += speed;
      }

      // Constrain within the screen
      position.x = constrain(position.x, 0, width - img.width);
      position.y = constrain(position.y, 0, height - img.height);
    }

    image(img, position.x, position.y);

    // Display HP bar
    float hpBarWidth = img.width * ((float)HP / maxHP);
    fill(0, 200, 0);
    rect(position.x, position.y + img.height + 5, hpBarWidth, 5); 

    // Display shield
    if(hasShield){
      fill(0, 0, 255, 100);
      ellipse(position.x + img.width / 2, position.y + img.height / 2, img.width + 20, img.height + 20);
    }
  }

  void upgradeWeapon(){
    bulletDamage += 1; // Increase bullet damage
  }

  void upgradeSpreadShot(){
    spreadLevel++;
  }

  void fireBullets(){
    int numBullets = 1 + spreadLevel; // Base 1 bullet, increase with level
    float angleStep = PI / 16; // Angle interval
    float startAngle = -PI / 2 - (numBullets - 1) * angleStep / 2; // Starting angle
    for(int i = 0; i < numBullets; i++){
      float angle = startAngle + i * angleStep;
      PVector dir = new PVector(cos(angle), sin(angle));
      Bullet b = new Bullet(this, dir);
      objects.add(b);
    }
  }

  void addAreaAttack(){
    hasAreaAttack = true;
    areaAttackCooldown = 0;
  }

  void updateAreaAttack(){
    if(areaAttackCooldown > 0){
      areaAttackCooldown--;
    } else {
      // Activate area attack
      objects.add(new AreaAttack(this));
      areaAttackCooldown = 600; // Cooldown (~10 seconds)
    }
  }

  void upgradeSpeed(){
    speed += 1; // Increase movement speed
  }

  void addShield(){
    hasShield = true;
    shieldHP = 10; // Shield durability
  }
}
