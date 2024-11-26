int x = 0;
int y = 0;

void setup(){
  size(800, 600);
}

void draw(){
  
  while(y <= height){
    while(x <= width){
      fill(random(256), random(256), random(256));
      ellipse(x, y, 50, 50);
      x = x + 50;
    }
    y = y + 50;
    x = 0;
  }  
}
