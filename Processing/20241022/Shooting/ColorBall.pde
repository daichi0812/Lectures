class ColorBall extends Ball{
  int R, G, B;
  
  ColorBall(){
    R = (int)random(1, 256);
    G = (int)random(1, 256);
    B = (int)random(1, 256);
  }
  
  void Draw(){
    fill(R, G, B);
    super.Draw();
  }
}
