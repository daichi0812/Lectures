int x = 0;

void setup(){
  size(400, 400);
}

void draw(){
  if( mouseX <= 200){
    background(255, 255, 255);
  }else{
    background(255, 0, 0);
  }
}
