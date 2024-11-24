/*
  Read me
  1. You can move with the arrow keys (→ ↑ ← ↓)
  2. Every time you accumulate 100 scores, you will be presented with options to upgrade your status.
  3. Click on the one you want to select from the options to level it up.
*/

import ddf.minim.*;
Minim minim;
AudioSample bullet_sound, damage_sound, explosion_sound;
PImage fighterImage;
PImage enemyImage;

Fighter fighter;
ArrayList<DisplayObject> objects = new ArrayList<DisplayObject>();
ArrayList<Explosion> explosions = new ArrayList<Explosion>();
int Score = 0;
int startFrameCount = 0;
int nextLevelScore = 100; // Next score milestone for level-up
boolean isSpacePressed = false;
boolean gameover = false;
String gameState = "playing"; // Game states: 'playing', 'level-up', 'game-over'

boolean moveLeft = false;
boolean moveRight = false;
boolean moveUp = false;
boolean moveDown = false;

// Upgrade options
String[] allUpgrades = {"Full HP Recovery", "Weapon Upgrade", "Enhance Rotating Sword", "Add Spread Shot", "Add Area Attack", "Increase Movement Speed", "Add Shield"};
String[] upgrades = new String[3]; // Three options displayed at level-up
int selectedUpgrade = -1; // Index of the selected upgrade

void setup(){
  size(1440, 720);

  // Load images
  fighterImage = loadImage("fighter.png");
  enemyImage = loadImage("enemy.png");

  // Resize images
  fighterImage.resize(50, 50);
  enemyImage.resize(40, 40);

  fighter = new Fighter();
  objects.add(fighter);

  minim = new Minim(this);
  bullet_sound = minim.loadSample("Bullet.mp3");
  explosion_sound = minim.loadSample("Explosion.mp3");
  damage_sound = minim.loadSample("Damage.mp3");
}

void draw(){
  noStroke();
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);

  // Start screen
  if(frameCount < 300 && gameState.equals("playing")){
    fill(255, 255, 255);
    textAlign(CENTER, CENTER);
    text("S T A R T", width / 2, height / 2);
    return;
  }

  if(gameState.equals("game-over")){
    // Game over screen
    fill(255);
    textAlign(CENTER, CENTER);
    textSize(32);
    text("Game Over", width / 2, height / 2);
    textSize(16);
    text("Press any key to restart", width / 2, height / 2 + 40);
    return;
  } else if(gameState.equals("level-up")){
    // Upgrade selection screen
    displayUpgradeMenu();
    return;
  }

  // Game playing state
  playGame();
}

void playGame(){
  textAlign(TOP, LEFT);

  // Adjust difficulty over time
  int elapsedTime = frameCount - startFrameCount;
  float enemySpawnRate = min(20, 5 + elapsedTime / 600.0);
  float enemyFireRate = min(10, 2 + elapsedTime / 1200.0);  

  // Display score and HP
  fill(255);
  textAlign(RIGHT, TOP);
  text("Score: " + Score, width - 10, 10);

  textAlign(LEFT, TOP);
  text("HP: " + fighter.HP, 10, 10);

  // Check for level-up
  if(Score >= nextLevelScore){
    selectRandomUpgrades();
    gameState = "level-up";
    return;
  }

  // Player shooting
  if(isSpacePressed){
    fighter.fireBullets();
  }

  // Update area attack if available
  if(fighter.hasAreaAttack){
    fighter.updateAreaAttack();
  }

  // Spawn enemies
  if(random(100) < enemySpawnRate){
    objects.add(new Enemy());
  }

  // Update and draw objects
  for(int i = 0; i < objects.size(); i++){
    objects.get(i).Draw();

    // Remove player bullets that go off-screen
    if(objects.get(i).syurui == 1 && (objects.get(i).position.y < 0 || objects.get(i).position.y > height)){
      objects.remove(i);
      i--;
    }

    // Enemy behavior
    if(objects.get(i).syurui == 2){
      Enemy enemy = (Enemy)objects.get(i);
      // Remove enemies that go off-screen
      if(enemy.position.y > height){
        objects.remove(i);
        i--;
      }else{
        // Enemies shoot at the player
        if(random(100) < enemyFireRate){
          objects.add(new Bullet(fighter, enemy));
        }
      }
    }

    // Remove enemy bullets that go off-screen
    if(objects.get(i).syurui == 3){
      Bullet bullet = (Bullet)objects.get(i);
      if(bullet.position.y > height || bullet.position.y < 0 || bullet.position.x < 0 || bullet.position.x > width){
        objects.remove(i);
        i--;
      }
    }
  }

  // Update and draw explosions
  for(int i = 0; i < explosions.size(); i++){
    explosions.get(i).Draw();
    if(explosions.get(i).isFinished()){
      explosions.remove(i);
      i --;
    }
  }

  // Update rotating swords if any
  if(fighter.rotatingSword != null){
    fighter.rotatingSword.update();
    fighter.rotatingSword.draw();
  }

  // Collision detection
  Collision();

  if(fighter.HP <= 0){
    gameState = "game-over";
  }
}

void selectRandomUpgrades(){
  ArrayList<String> upgradePool = new ArrayList<String>();
  for(String u : allUpgrades){
    upgradePool.add(u);
  }
  upgrades = new String[3];
  for(int i = 0; i < 3; i++){
    int index = (int)random(upgradePool.size());
    upgrades[i] = upgradePool.get(index);
    upgradePool.remove(index);
  }
}

void displayUpgradeMenu(){
  fill(0, 0, 0, 200);
  rect(0, 0, width, height);

  fill(255);
  textAlign(CENTER, CENTER);
  textSize(24);
  text("Choose Your Upgrade", width / 2, height / 2 - 100);

  // Display upgrade options
  for(int i = 0; i < upgrades.length; i++){
    if(i == selectedUpgrade){
      fill(200, 200, 0); // Highlight selected option
    } else {
      fill(255);
    }
    text(upgrades[i], width / 2, height / 2 - 50 + i * 40);
  }
}

void applyUpgrade(){
  String selected = upgrades[selectedUpgrade];

  if(selected.equals("Full HP Recovery")){
    fighter.HP = fighter.maxHP;
  } else if(selected.equals("Weapon Upgrade")){
    fighter.upgradeWeapon();
  } else if(selected.equals("Enhance Rotating Sword")){
    if(fighter.rotatingSword == null){
      fighter.rotatingSword = new RotatingSword(fighter);
    } else {
      fighter.rotatingSword.upgrade();
    }
  } else if(selected.equals("Add Spread Shot")){
    fighter.upgradeSpreadShot();
  } else if(selected.equals("Add Area Attack")){
    fighter.addAreaAttack();
  } else if(selected.equals("Increase Movement Speed")){
    fighter.upgradeSpeed();
  } else if(selected.equals("Add Shield")){
    fighter.addShield();
  }

  // Prepare for the next level-up
  nextLevelScore += 100;
  selectedUpgrade = -1;
  gameState = "playing";
}

void mousePressed(){
  if(gameState.equals("level-up")){
    // Check which upgrade is selected
    for(int i = 0; i < upgrades.length; i++){
      float yPosition = height / 2 - 50 + i * 40;
      if(mouseY > yPosition - 10 && mouseY < yPosition + 10){
        selectedUpgrade = i;
        applyUpgrade();
        break;
      }
    }
  }
}

void GameStart(){
  Score = 0;
  nextLevelScore = 100;
  gameState = "playing";
  gameover = false;
  objects.clear();
  explosions.clear();
  fighter = new Fighter();
  objects.add(fighter);
  startFrameCount = frameCount;

  // Reset movement flags
  moveLeft = false;
  moveRight = false;
  moveUp = false;
  moveDown = false;
}

void Collision(){
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).syurui == 1){
      // Collision between player bullets and enemies
      Bullet bullet = (Bullet)objects.get(i);
      for(int j = 0; j < objects.size(); j++){
        if(objects.get(j).syurui == 2){
          Enemy enemy = (Enemy)objects.get(j);

          if(enemy.position.x < bullet.position.x && bullet.position.x < enemy.position.x + enemy.img.width &&
             enemy.position.y < bullet.position.y && bullet.position.y < enemy.position.y + enemy.img.height){
               enemy.HP -= fighter.bulletDamage; // Apply upgraded bullet damage
               // Add score
               Score += 1;
               bullet.HP--;
               // Play damage sound
               damage_sound.trigger();

               // When enemy is destroyed
               if(enemy.HP <= 0){
                 explosions.add(new Explosion(enemy.position.x + enemy.img.width / 2, enemy.position.y + enemy.img.height / 2));
                 explosion_sound.trigger(); // Play explosion sound
               }
          }
        }
      }
    } else if(objects.get(i).syurui == 2){
      // Collision between enemy and player
      Enemy enemy = (Enemy)objects.get(i);
      if(enemy.position.x < fighter.position.x + fighter.img.width &&
         enemy.position.x + enemy.img.width > fighter.position.x &&
         enemy.position.y < fighter.position.y + fighter.img.height &&
         enemy.position.y + enemy.img.height > fighter.position.y){

           // If shield is active
           if(fighter.hasShield && fighter.shieldHP > 0){
             fighter.shieldHP -= enemy.HP;
             if(fighter.shieldHP <= 0){
               fighter.hasShield = false;
             }
           } else {
             // Decrease player's HP
             fighter.HP -= enemy.HP;
           }

           // Explosion effects and sound
           explosions.add(new Explosion(enemy.position.x + enemy.img.width / 2, enemy.position.y + enemy.img.height / 2));
           explosion_sound.trigger();

           // Remove collided enemy
           objects.remove(i);
           i--;
         }
    } else if (objects.get(i).syurui == 3){
      // Collision between enemy bullets and player
      Bullet bullet = (Bullet)objects.get(i);
      if(fighter.position.x < bullet.position.x && bullet.position.x < fighter.position.x + fighter.img.width &&
         fighter.position.y < bullet.position.y && bullet.position.y < fighter.position.y + fighter.img.height){
           
           if(fighter.hasShield && fighter.shieldHP > 0){
             fighter.shieldHP -= bullet.HP;
             if(fighter.shieldHP <= 0){
               fighter.hasShield = false;
             }
           } else {
             fighter.HP -= bullet.HP;
           }
           
           bullet.HP -= 1;
           damage_sound.trigger();
           if(fighter.HP <= 0){
             gameState = "game-over";
           }
         }
    } else if(objects.get(i).syurui == 4){
      // Collision between area attack and enemies
      AreaAttack areaAttack = (AreaAttack)objects.get(i);
      for(int j = 0; j < objects.size(); j++){
        if(objects.get(j).syurui == 2){ // Enemy
          Enemy enemy = (Enemy)objects.get(j);
          float d = dist(areaAttack.position.x, areaAttack.position.y, enemy.position.x + enemy.img.width / 2, enemy.position.y + enemy.img.height / 2);
          if(d < areaAttack.radius){
            enemy.HP -= 5; // Damage from area attack
            if(enemy.HP <= 0){
              explosions.add(new Explosion(enemy.position.x + enemy.img.width / 2, enemy.position.y + enemy.img.height / 2));
              explosion_sound.trigger();
            }
          }
        }
      }
    }
  }

  // Collision between rotating swords and enemies
  if(fighter.rotatingSword != null){
    for(int i = 0; i < objects.size(); i++){
      if(objects.get(i).syurui == 2){ // Enemy
        Enemy enemy = (Enemy)objects.get(i);
        if(fighter.rotatingSword.hit(enemy)){
          enemy.HP -= fighter.rotatingSword.damage;
          if(enemy.HP <= 0){
            explosions.add(new Explosion(enemy.position.x + enemy.img.width / 2, enemy.position.y + enemy.img.height / 2));
            explosion_sound.trigger();
          }
        }
      }
    }
  }

  // Remove objects with HP <= 0
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).HP <= 0){
      objects.remove(i);
      i--;
    }
  }
}

void keyPressed(){
  if(gameState.equals("game-over")){
    GameStart();
    return;
  }

  if(keyCode == LEFT){
    moveLeft = true;
  } else if(keyCode == RIGHT){
    moveRight = true;
  } else if(keyCode == UP){
    moveUp = true;
  } else if(keyCode == DOWN){
    moveDown = true;
  }

  if(key == ' '){
    isSpacePressed = true;
    bullet_sound.trigger();
  }
}

void keyReleased(){
  if(keyCode == LEFT){
    moveLeft = false;
  } else if(keyCode == RIGHT){
    moveRight = false;
  } else if(keyCode == UP){
    moveUp = false;
  } else if(keyCode == DOWN){
    moveDown = false;
  }

  if(key == ' '){
    isSpacePressed = false;
  }
}
