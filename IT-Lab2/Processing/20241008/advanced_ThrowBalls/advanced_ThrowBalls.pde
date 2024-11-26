float degree = 30.0;
int v1 = 100;
int v2 = 70;
int v3 = 50;
float t = 0.0;
float g = 9.8;

void setup()
{
  size(1300, 400);
  background(255, 255, 255);
  frameRate(10);
}

void draw()
{ 
  int x_line = 0;
  for(int i = 0; i < 13; i++){
    stroke(200, 200, 200);
    line(x_line, 0, x_line, 400);
    x_line += 100;
  }
  
  fill(0, 0, 255);
  ellipse(x(v1, t), y(v1, t), 5, 5);
  
  fill(0, 255, 0);
  ellipse(x(v2, t), y(v2, t), 5, 5);
  
  fill(255, 0, 0);
  ellipse(x(v3, t), y(v3, t), 5, 5);
  
  t += 0.1;
}

float x (int v0, float t){
  float x = 0.0;
  
  x = v0 * cos(degree * PI / 180.0) * t;
  return x;
}

float y (int v0, float t){
  float y = 0.0;
  
  y = v0 * sin(degree * PI / 180.0) * t - 0.5 * g * t * t;
  
  return height - (300 + y);
}
