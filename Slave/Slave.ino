#include <Wire.h>

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int nanoSlave = 2;
#define COMMON_ANODE

void setup()
{
  Serial.begin(9600);
  Wire.begin(nanoSlave);
  Serial.println("\nI2C Slave: I'm arduino Nano");
  Wire.onReceive(receiveEvent);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setColourRgb(0, 0, 0);
}

void loop()
{
}

void receiveEvent(int howMany)
{
  /*
    int numCommands = 3;
    char commands[numCommands];
  */
  char c;
  while (Wire.available())
  {
    Serial.print("\nI2C Slave- Read: ");
    c = Wire.read();
    Serial.println(c);
    if (c == 'R')
    {
      cycleColor('R');
    }
    else if (c == 'G')
    {
      cycleColor('G');
    }
    else if (c == 'B')
    {
      cycleColor('B');
    }
    else if (c == 'O')
    {
      cycleColor('O');
    }
    delay(500);
  }
}

void cycleColor(char color) {
  unsigned int rgbColour[3];
  switch (color) {
    case 'R':
      setColourRgb(255, 0, 0);
      break;
    case 'G':
      setColourRgb(0, 255, 0);
      break;
    case 'B':
      setColourRgb(0, 0, 255);
      break;
    case 'O':
      setColourRgb(0, 0, 0);
      break;
    default:
      break;
  }
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {

#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

