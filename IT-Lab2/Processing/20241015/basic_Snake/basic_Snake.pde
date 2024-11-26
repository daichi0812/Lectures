int[] cursorX = new int[100];
int[] cursorY = new int[100];

void setup(){
  size(400, 400);
}

void draw(){
  background(255);

  drawSnake(mouseX, mouseY);
  
  for(int i = 0; i < 100; i++){
    ellipse(cursorX[i], cursorY[i], 20, 20);
  }
}

void drawSnake(int X, int Y){
  for(int i = 99; i > 0; i--){
    cursorX[i] = cursorX[i - 1];
    cursorY[i] = cursorY[i - 1];
  }
  
  cursorX[0] = X;
  cursorY[0] = Y;
}
