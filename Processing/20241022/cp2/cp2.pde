int BallNum = 100;
Ball[] balls = new Ball[BallNum];
int ObjNum = 100;
DisplayObject[] objects = new DisplayObject[ObjNum];

void setup(){
  size(800, 600);
  for(int i = 0; i < objects.length; i++){
    objects[i] = new ColorBall();
  }
}

void draw(){
  fill(0, 0, 0, 100);
  rect(0, 0, width, height);
  
  for(int i = 0; i < objects.length; i++){
    fill(255);
    objects[i].Draw();
  }
}
