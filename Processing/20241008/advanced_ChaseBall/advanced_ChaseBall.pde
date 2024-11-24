float x = 400.0;
float y = 400.0;
float x1 = 0.0;
float y1 = 0.0;

void setup()
{
  size(800, 800);
  background(255, 255, 255);
  frameRate(10);
}

void draw()
{ 
  background(255, 255, 255);

  x = tracking_x(x);
  y = tracking_y(y);
  
  fill(255, 0, 0);
  ellipse(x, y, 30, 30);
  
  x1 = trackingLine_x(x);
  y1 = trackingLine_y(x, y);
  
  fill(0, 0, 0);
  line(x, y, x1, y1);
}

float tracking_x(float x){
  x += (mouseX - x) * 0.2;
  
  return x;
}
  
float tracking_y(float y){
  y += (mouseY - y) * 0.2;
  
  return y;
}

float trackingLine_x(float x){
  float theta = atan2(mouseY - y, mouseX - x);
  
  x += 30 * cos(theta);
  
  //if(mouseX < x){
  //  x -= 10;
  //}else if (mouseX > x){
  //  x += 10;
  //}
  
  return x;
}
  
float trackingLine_y(float x, float y){
  float theta = atan2(mouseY - y, mouseX - x);
  
  y += 30 * sin(theta);
  
  
  //if(mouseY < y && mouseX > x){
  //  y += 10 * sin(theta);
  //}else if(mouseY < y && mouseX < x){
  //  y += 10 * sin(theta);
  //}else if (mouseY > y){
    //y += 10 * sin(theta) / cos(theta);;
  //}
  
  return y;
}
