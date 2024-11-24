import ddf.minim.*;
import processing.serial.*;

Minim minim;
AudioPlayer player;
Serial myPort;
int trackNumber = 1;
boolean isPlaying = false;

void setup() {
  size(400, 200);
  minim = new Minim(this);
  player = minim.loadFile("sound/" + trackNumber + ".wav");
  
  myPort = new Serial(this, "/dev/tty.usbserial-57720082111", 115200);
}

void draw() {
  background(0);
  fill(255);
  textSize(24);
  textAlign(CENTER, CENTER);

  text("Track: " + trackNumber, width / 2, height / 2 - 20);
  text(isPlaying ? "playing" : "pause", width / 2, height / 2 + 20);
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    
    if (inString.equals("next")) {
      togglePlayPause();
      changeTrack(trackNumber + 1);
    } else if (inString.equals("prev")) {
      togglePlayPause();
      changeTrack(trackNumber - 1);
    } else if (inString.equals("toggle")) {
      togglePlayPauseOrPlaying();
    }
  }
}

void keyPressed() {
  if (keyCode == RIGHT) {
    togglePlayPause();
    changeTrack(trackNumber + 1);
    myPort.write("next\n");  // M5Stackに通知
  } else if (keyCode == LEFT) {
    togglePlayPause();
    changeTrack(trackNumber - 1);
    myPort.write("prev\n");  // M5Stackに通知
  } else if (key == ' ') {
    togglePlayPauseOrPlaying();
    myPort.write("toggle\n");  // M5Stackに通知
  }
}

void changeTrack(int newTrackNumber) {
  if (newTrackNumber < 1) newTrackNumber = 20;
  if (newTrackNumber > 20) newTrackNumber = 1;
  
  trackNumber = newTrackNumber;
  player.close();
  player = minim.loadFile("sound/" + trackNumber + ".wav");

  if (isPlaying) {
    player.loop();
  }
}

void togglePlayPause() {
  isPlaying = false;
  player.pause();
}

void togglePlayPauseOrPlaying() {
  if (isPlaying) {
    player.pause();
  } else {
    player.loop();
  }
  isPlaying = !isPlaying;
}

void stop() {
  player.close();
  minim.stop();
  super.stop();
}
