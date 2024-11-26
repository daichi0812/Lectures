int cellX = 3;
int cellY = 3;
boolean isKeyPressed = false;

void setup(){
  size(500, 500);  
}

void draw(){
  background(255);
  
  for(int i = 0; i < 5; i++){
    line(100 * (i + 1), 0, 100 * (i + 1), height);
    line(0, 100 * (i + 1), width, 100 * (i + 1));
  }
  
  if(!isKeyPressed){
    ellipse(100 * cellX - 50, 100 * cellY - 50, 60, 60);
  }
  
}

void keyPressed(){
  if(keyCode == UP && cellY != 1){
    cellY--;
  }
  
  if(keyCode == DOWN && cellY != 5){
    cellY++;
  }

  if(keyCode == LEFT && cellX != 1){
    cellX--;
  }
  
  if(keyCode == RIGHT && cellX != 5){
    cellX++;
  }
  
  ellipse(100 * cellX - 50, 100 * cellY - 50, 60, 60);
    
}
