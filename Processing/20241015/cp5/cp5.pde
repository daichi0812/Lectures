void setup(){
  size(400, 400);
}

void draw(){
  background(255, 255, 255);
  noFill();
  
  int diameter = 400;
  
  while(diameter > 0){
    ellipse(200, 200, diameter, diameter);
    diameter -= 10;
  }
}
