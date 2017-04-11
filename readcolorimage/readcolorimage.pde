// edited from http://pushbuttons.io/blog/processing-arduino-adafruit-neo-pixel-rgb-real-time-colour-sampling-from-image

import processing.serial.*;
import java.util.ArrayList;
import java.util.List;

List<Integer> colVl = new ArrayList(); // Colour Value list to store RGB data

PImage someImage; // Image to sample colour
PImage someImage2; // Image to sample colour

Boolean ChngImg;
Boolean sendData; // Toggle send

int val;
int colV; // col value from pixel (processing store data as one long integer)

String serialData;

Serial myPort;  // Create object from Serial class

void setup()
{
    size(600, 600, P2D);
    noStroke();
    someImage2 = loadImage("/Users/Toni/Desktop/insp/grey.jpg");
    someImage = loadImage("/Users/Toni/Desktop/insp/colorpicker.jpg");
    sendData = false;
    ChngImg = false;
    
    String portName = Serial.list()[1];
    myPort = new Serial(this, portName, 9600); // Uncomment to enable serial connection
    printArray(Serial.list()); // List all available serial ports
}

void draw()
{
    if(ChngImg == true)
    {
    image(someImage, 0, 0, 600, 600);
    }
    if(ChngImg == false)
    {
    image(someImage2, 0, 0, 600, 600);
    }
    getCol();
    conv(); // convert to comma seperated string for serial
    fill(colVl.get(0),colVl.get(1),colVl.get(2));
    //println(colVl);
    rect(0, 0, 80, 80);
    //println(serialData);
    
    if (sendData == true)
    {
     myPort.write(serialData);
     println(serialData);
    }
    
  colVl.clear();
  sendData = false;
}

void getCol()
{
    colV = get(mouseX,mouseY);
    int r =(colV>>16)&255;
    int g =(colV>>8)&255;
    int b =colV&255;
    colVl.add(r);
    colVl.add(g);
    colVl.add(b);
}

void conv()
{
  serialData = ("r"+Integer.toString(colVl.get(0)) + "g" + Integer.toString(colVl.get(1)) + "b" +  Integer.toString(colVl.get(2)));
}


 void mouseClicked()
 {
  if (sendData == false)
  {
   sendData = true;
  } 
  else
  {
    sendData = false;
  }
}

void keyPressed()
{
  if (key == 'o')
  {
    if(ChngImg == true)
    {
      ChngImg = false;
    }
    else
    {
     ChngImg = true;
    }
  }
}