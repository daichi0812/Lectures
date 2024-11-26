
float x = 0.0;

void setup()
{
  size(400, 400);
  frameRate(60);
}

void draw()
{
  line(x, y(x), x + 0.5, y(x + 0.5));
  x++;
}

float y(float x){
  return height - x * x / 200.0;
}
