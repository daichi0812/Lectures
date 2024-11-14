float[] posX = new float[10];
void setup(){
  size(400, 400);  
}

void drawEye(int x, int y, int mx, int my){
  strokeWeight(3);
  fill(255, 255, 255);
  ellipse(x, y, 60, 70);
  fill(0);
  int eyeX, eyeY;
  eyeY = y;
  
  if(mx <= x + 20 && x - 20 <= mx){
    eyeX = mx;
  }else if(mx <= x - 20){
    eyeX = x - 20;
  }else{
    eyeX = x + 20;
  }
  
  ellipse(eyeX, eyeY, 10, 10);
}

void drawHuman(int x, int y){
  ellipse(x, y, 20, 20);
  line(x, y + 10, x, y + 40);
  line(x - 20, y + 10, x + 20, y + 10);
  line(x, y + 40, x - 20, y + 60);
  line(x, y + 40, x + 20, y + 60);
}

void draw(){
  background(255);
  drawHuman(mouseX, mouseY);
  drawEye(160, 200, mouseX, mouseY);
  drawEye(240, 200, mouseX, mouseY);
}
