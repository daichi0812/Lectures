

int x2 = 0;

void setup()
{
  size(600, 300);
  background(255, 255, 255);
  noStroke();
  frameRate(30);
}

void draw()
{
  background(255, 255, 255);
  
  int x1 = 300;
  
  for(int i = 0; i < 600; i++){
    fill(0, 0, 0);
    rect(x1, 0, 10, 300);
    x1 += 20;
  }
 
  fill(0, 0, 0);
  rect(0 + x2 % width, 50, 20, 100);
  
  fill(255, 255, 255);
  rect(0 + x2 % width, 150, 20, 100);
  
  x2++;
}
