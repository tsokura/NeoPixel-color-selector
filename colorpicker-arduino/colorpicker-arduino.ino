//from http://pushbuttons.io/blog/processing-arduino-adafruit-neo-pixel-rgb-real-time-colour-sampling-from-image

#define PIN            6
#define NUMPIXELS      16
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

boolean messageComplete = false;
String pixelMessage = "";

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int delayval = 50; // delay for half a second
int ColVal[] = {50,0,0,0};

int cnt;

void setup()
{
  Serial.begin(9600);
  pixels.begin();
}

void loop()
{
  if (Serial.available())
  {
   char chan = Serial.read(); //channel
   int val = Serial.parseInt();//value
   setval(chan, val);
   String data = (String(ColVal[0]) + " "+ String(ColVal[1]) +" " + String(ColVal[2]));
   Serial.println(data); 
  }
}

void setval(char col, int dataV)
{ 
  if (col == 'r')
  {
   ColVal[0] = dataV;
   cnt ++;
  }
  if (col == 'g')
  {
    ColVal[1] = dataV;
    cnt ++;
  }
  if (col == 'b')
  {
   ColVal[2] = dataV;
   cnt ++;
  }
  ;
  if (cnt % 3 == 0)
  {
    go();
  }
}

void go()
{
  ;
  for(int i=0;i<NUMPIXELS;i++) //Climb LED with received colour value
  {
    pixels.setPixelColor(i, pixels.Color(ColVal[0],ColVal[1],ColVal[2]));
    pixels.show(); // This sends the updated pixel color to the hardware
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
