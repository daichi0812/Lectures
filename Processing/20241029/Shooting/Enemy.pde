
class Enemy extends DisplayObject{
  PImage img;

  Enemy(){
    super();
    img = enemyImage;
    syurui = 2; 
    HP = (int)random(1, 10);
    move.x = random(-1, 1);
    move.y = random(0.5, 2); 
    position.x = random(0, width - img.width);
    position.y = -img.height; 
  }

  void Draw(){
    noStroke();
    super.Draw();
    position.add(move);

    if(position.x < 0 || position.x > width - img.width){
      move.x *= -1;
    }

    // Display image
    image(img, position.x, position.y);

    // HP bar
    float hpBarWidth = img.width * ((float)HP / 10);
    fill(255, 0, 0);
    rect(position.x, position.y + img.height + 5, hpBarWidth, 5);
  }
}
