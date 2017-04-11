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

void setup() {
  pixels.begin();
  Serial.begin(9600); // Start serial communication at 9600 bps
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    pixelMessage += inChar;
    if (inChar == '\n') {
      messageComplete = true;
      String parsedMessage = parseMessage(pixelMessage);
      renderPixels(parsedMessage);
    }
  }
}

void loop() {
  if (messageComplete) {
    Serial.println(pixelMessage);
    pixelMessage = "";
    messageComplete = false;
  }
}

String parseMessage(String _pixelMessage) {
  //turn a pixelMessage into a set of instructions
  //does nothing at the moment
  return _pixelMessage;
}

void renderPixels(String _pixelMessage) {
  //output the pixels to the display
  for (int i = 0; i < _pixelMessage.length(); i++) {
    char msgChar = _pixelMessage.charAt(i);
    //ugh
    if (i < NUMPIXELS) {
      switch (msgChar) {
        case 'r':
          pixels.setPixelColor(i, pixels.Color(255, 0, 0));
          break;
        case 'g':
          pixels.setPixelColor(i, pixels.Color(0, 255, 0));
          break;
        case 'b':
          pixels.setPixelColor(i, pixels.Color(0, 0, 255));
          break;
        case 'w':
          pixels.setPixelColor(i, pixels.Color(255, 255, 255));
          break;
        case '8':
          pixels.setPixelColor(i, pixels.Color(200, 200, 200));
          break;
        case '6':
          pixels.setPixelColor(i, pixels.Color(100, 100, 100));
          break;
        default:
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          break;
      }
    }
  }
  pixels.show();
  Serial.println("render");
}

