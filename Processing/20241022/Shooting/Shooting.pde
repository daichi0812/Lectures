ArrayList<DisplayObject> objects = new ArrayList<DisplayObject>();
ArrayList<Explosion> explosions = new ArrayList<Explosion>();
int Counter = 0;
Fighter fighter;
boolean isSpacePressed = false;

void setup(){
  size(800, 600);
  fighter = new Fighter();
  objects.add(fighter);
}

void draw(){
  noStroke();
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  
  /* Display START */
  //if(frameCount < 300){
  //  fill(255, 255, 255);
  //  textAlign(CENTER, CENTER);
  //  text("S T A R T", width / 2, height / 2);
    
  //  return;
  //}
  //textAlign(TOP, LEFT);
  
  if(isSpacePressed){
     objects.add(new Bullet(fighter));
  }
  
  if(random(100) < 5){
    objects.add(new Enemy());
  }
  
  for(int i = 0; i < objects.size(); i++){
    objects.get(i).Draw();
    
    if(objects.get(i).syurui == 1 && objects.get(i).position.y < 0){
      objects.remove(i);
      i--;
    }
    
    if(objects.get(i).syurui == 2 && objects. get(i).position.y > height){
      objects.remove(i);
      i--;
    }
  }
  
  for(int i = 0; i < explosions.size(); i++){
    explosions.get(i).Draw();
    if(explosions.get(i).isFinished()){
      explosions.remove(i);
      i --;
    }
  }
  
  Collision();

}

void Collision(){
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).syurui == 1){
      Bullet bullet = (Bullet)objects.get(i);
      for(int j = 0; j < objects.size(); j++){
        if(objects.get(j).syurui == 2){
          Enemy enemy = (Enemy)objects.get(j);
          
          if(enemy.position.x < bullet.position.x && bullet.position.x < enemy.position.x + enemy.size_x &&
             enemy.position.y < bullet.position.y && bullet.position.y < enemy.position.y + enemy.size_y){
               enemy.HP -= bullet.HP;
               bullet.HP--;
               
               if(enemy.HP <= 0){
                 explosions.add(new Explosion(enemy.position.x + enemy.size_x / 2, enemy.position.y + enemy.size_y / 2));
               }
          }
        }
      }
    }
  }
  
  for(int i = 0; i < objects.size(); i++){
    if(objects.get(i).syurui == 1 || objects.get(i).syurui == 2){
      if(objects.get(i).HP <= 0){
        objects.remove(i);
        i--;
      }
    }
  }
}

void keyPressed(){
  if(key == ' '){
    isSpacePressed = true;
   }
  
  if(fighter.moveDirection == 1 && keyCode == LEFT){
    fighter.moveDirection = -1;
  }else if(fighter.moveDirection == 0 && keyCode == LEFT){
    fighter.moveDirection = -1;
  }else if(fighter.moveDirection == -1 && keyCode == RIGHT){
    fighter.moveDirection = 1;
  }else if(fighter.moveDirection == 0 && keyCode == RIGHT){
    fighter.moveDirection = 1;
  }
}

void keyReleased(){
  if(key == ' '){
    isSpacePressed = false;
  }
  
  if(fighter.moveDirection == 1 && keyCode == RIGHT){
    fighter.moveDirection = 0;
  }else if(fighter.moveDirection == -1 && keyCode == LEFT){
    fighter.moveDirection = 0;
  }
}
