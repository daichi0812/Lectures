int x = 200;
int vx = 2;
int r = 25; 

void setup(){
  size(400, 300);
}

void draw(){
  background(255, 255, 255);
  
  if(!(x - r <= mouseX && mouseX <= x + r && 150 - r <= mouseY && mouseY <= 150 + r)){
    x = x + vx;
  }
  
  if(x + r > width){
    x = width - r;
    vx = - vx;
  }else if (x - r == 0){
    vx = -vx;
  }
  
  ellipse(x, height / 2, r * 2, r * 2);
}
