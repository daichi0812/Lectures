float t = 0.0;

void setup()
{
  size(500, 500);
  background(255, 255, 255);
}

void draw()
{
  background(255, 255, 255);
  
  int h = hour();
  int m = minute();
  int s = second();
  
  noFill();
  stroke(0, 0, 0);
  strokeWeight(1);
  ellipse(250.0, 250.0, 400, 400);
  
  fill(0, 0, 0);
  stroke(0,0,0);
  strokeWeight(7);
  line(250.0, 250.0, h_x(h), h_y(h));
  
  fill(0, 0, 0);
  stroke(0,0,0);
  strokeWeight(5);
  line(250.0, 250.0, m_x(m), m_y(m));
  
  fill(0, 0, 0);
  stroke(0,0,0);
  strokeWeight(3);
  line(250.0, 250.0, s_x(s), s_y(s));
}

float h_x(int h){
  float degree = 0.0;
  
  if(h > 12){
    h = h - 12;
  }
  
  degree = h * 30.0;
  
  return (250 + 100 * sin(degree * PI / 180.0));
}

float h_y(int h){
  float degree = 0.0;
  
  if(h > 12){
    h = h - 12;
  }
  
  degree = h * 30.0;
  
  return (250 - 100 * cos(degree * PI / 180.0));
}

float m_x(int m){
  float degree = 0.0;
  
  degree = m * 6.0;
  
  return (250 + 150 * sin(degree * PI / 180.0));
}

float m_y(int m){
  float degree = 0.0;
  
  degree = m * 6.0;
  
  return (250 - 150 * cos(degree * PI / 180.0));
}

float s_x(int s){
  float degree = 0.0;
  
  degree = s * 6.0;
  
  return (250 + 180 * sin(degree * PI / 180.0));
}

float s_y(int s){
  float degree = 0.0;
  
  degree = s * 6.0;
  
  return (250 - 180 * cos(degree * PI / 180.0));
}
