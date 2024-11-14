int flag = 0;
int r = 100;
int centerX = 200, centerY = 150;

void setup(){
  size(400, 300);
}

void mousePressed(){

  if(dist(centerX, centerY, mouseX, mouseY) < r && flag == 1){
    flag = 2;
  }else if(dist(centerX, centerY, mouseX, mouseY) < r && flag == 2){
    flag = 3;
  }else if(dist(centerX, centerY, mouseX, mouseY) < r){
    flag = 1;
  }else{
    flag = 0;
  }
}

void draw(){
  background(255, 255, 255);
  if(flag == 1){
    fill(255, 0, 0);
  }else if(flag == 2){
    fill(0, 0, 255);
  }else if(flag == 3){
    fill(255, 255, 0);
  }else{
    fill(255, 255, 255);
  }
  ellipse(centerX, centerY, r*2, r*2);
}
