int randomX = 0;
int randomY = 0;
int r = 400;
int countAll = 0;
int countInCircle = 0;
double PI = 0.0;

void setup(){
  size(800, 800);
  background(255);
  frameRate(10000);
  noFill();
  ellipse(400, 400, 800, 800);
  noStroke();
}

void draw(){
  countAll++;
  
  randomX = (int)random(801);
  randomY = (int)random(801);
  if((randomX - 400) * (randomX - 400) + (randomY - 400) * (randomY - 400) <= r * r){
    countInCircle++;
    fill(255, 0, 0);
    ellipse(randomX, randomY, 3, 3);
  }else{
    fill(0, 0, 255);
    ellipse(randomX, randomY, 3, 3);
  }
  
  PI = (double)countInCircle / (double)countAll * 4.0;
  
  println("count: " + countAll);
  println("value: " + PI);
  println("");
  
}
