import processing.serial.*;

// serial communication object
Serial myPort;

int r = 0;
int g = 0;
int b = 0;

void setup(){
  size(400, 400);
  // get available serial port
  //println(Serial.list());
  
  // open serial port connected with M5Stack
  myPort = new Serial(this, "/dev/tty.usbserial-57720082111", 115200);
}

void draw(){
  background(0);
  
  // rect based on integer of red
  fill(r, 0, 0);
  rect(50, 50, 100, 300);
  
  // rect based on integer of green
  fill(0, g, 0);
  rect(150, 50, 100, 300);
  
  // rect based on integer of blue
  fill(0, 0, b);
  rect(250, 50, 100, 300);
  
  // display RGB
  fill(255);
  textSize(20);
  text("R: " + r, 50, 380);
  text("G: " + g, 150, 380);
  text("B: " + b, 250, 380);
}

// process of receiving serial data
void serialEvent(Serial myPort){
  // road data from serial
  String inString = myPort.readStringUntil('\n');
  
  if(inString != null){
    // divide string that was received with ','
    String[] rgbValues = split(inString.trim(), ',');
    
    // convert RGB integer
    if(rgbValues.length == 3){
      r = int(rgbValues[0]);
      g = int(rgbValues[1]);
      b = int(rgbValues[2]);
    }
  }
}
