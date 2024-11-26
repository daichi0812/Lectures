ArrayList<DisplayObject> objects = new ArrayList<DisplayObject>();
int Counter = 0;
Fighter fighter;

void setup(){
  size(800, 600);
  fighter = new Fighter();
  objects.add(fighter);
}

void draw(){
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  
  if(frameCount < 300){
    fill(255, 255, 255);
    textAlign(CENTER, CENTER);
    text("S T A R T", width / 2, height / 2);
    
    return;
  }
  textAlign(TOP, LEFT);
  
  for(int i = 0; i < objects.size(); i++){
    objects.get(i).Draw();
    if(objects.get(i).syurui == 1 && objects.get(i).position.y < 0){
      objects.remove(i);
      i--;
    }
  }
}

void keyPressed(){
  if(key == ' '){
    objects.add(new Bullet(fighter));
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
  if(fighter.moveDirection == 1 && keyCode == RIGHT){
    fighter.moveDirection = 0;
  }else if(fighter.moveDirection == -1 && keyCode == LEFT){
    fighter.moveDirection = 0;
  }
}
