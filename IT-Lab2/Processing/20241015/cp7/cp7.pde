float[] posX = new float[10];
float[] speed = new float[10];

void setup(){
  size(400, 300);
  
  for(int i = 0; i < 10; i++){
    posX[i] = random(400);
    speed[i] = random(5);
    
  }
  
}

void draw(){
  int clash = 0;

  for(int j = 0; j < 10; j++){
    posX[j] += speed[j];
    
    if(posX[j] > 400){
      posX[j] -= 400;
    }
    
    if(posX[j] + 10 > mouseX - 10 && posX[j] - 10 < mouseX + 10 && mouseY < 170 && mouseY > 130){
      clash = 1;
    }
  }
  
  if(clash == 0){
    background(255);
  }else {
    background(255, 0, 0);
  }
      
  fill(0, 255, 0);
  ellipse(mouseX, mouseY, 20, 20);
  fill(255, 0, 0);
  for(int k = 0; k < 10; k++){
    ellipse(posX[k], 150, 20, 20);
  }
}
