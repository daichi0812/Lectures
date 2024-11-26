float t = 0.0;

void setup()
{
  size(800, 800);
  noStroke();
}

void draw()
{
  fill(0, 0, 0);
  ellipse(x(t), y(t), 5, 5);
  
  t += 0.01;
}

float x (float t) {
  return 300.0 * sin(5.0 * t) + 400.0;
}

float y (float t) {
  return 300.0 * sin(6.0 * t) + 400.0;
}
