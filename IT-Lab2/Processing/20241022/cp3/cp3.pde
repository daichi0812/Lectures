Fighter fighter;

void setup(){
  size(800, 600);
  fighter = new Fighter();
}

void draw(){
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  
  fighter.Draw();
}

void keyPressed(){
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
