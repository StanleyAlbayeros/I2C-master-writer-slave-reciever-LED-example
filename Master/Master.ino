#include <Wire.h>

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int nanoSlave = 2;
const int numCommands = 3;
char commands[numCommands];
bool bufferFull = false;
int bufferIndex = 0;
char c;
bool noPC = false;
#define COMMON_ANODE

void setup()
{
  
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setColourRgb(0, 0, 0);
  Wire.begin();
  Serial.println("\nI2C Master: I'm arduino Uno R3");
  
}
void loop()
{
  if (noPC){
  bufferFull = true;
  commands[0] = 'R';
  commands[1] = 'B';
  commands[2] = 'G';
  }
  
  while (!bufferFull)
  {
    if (Serial.available()) {
      c = Serial.read();
      Serial.print(bufferIndex);
      Serial.print(" --- ");
      Serial.println(c);
      if (c != '\n' && c != '\r')
      { 
        commands[bufferIndex] = c;
        bufferIndex++;
        if (bufferIndex >= numCommands) {
          bufferFull = true;
          bufferIndex = 0;
        }
      }

    }
  }
  
  
  Serial.println("I2C Master: buffer is full");
  Serial.print("  I2C Master: buffer contents: (");
  for (int n = 0; n < 3; n++) {

    Serial.print(" buffer[");
    Serial.print(n);
    Serial.print("] = ");
    Serial.print(commands[n]);

    Serial.print(" ");
  }

  Serial.println(")");
  for (int i = 0; i < numCommands ; i++) {
    if (commands[i] == 'R')
    {
      cycleColor('R');
    }
    else if (commands[i] == 'G')
    {
      cycleColor('G');
    }
    else if (commands[i] == 'B')
    {
      cycleColor('B');
    }
    else if (commands[i] == 'O')
    {
      cycleColor('O');
    }
    
    delay(500);
  }

  cycleColor('O');

  if (bufferFull) {
    delay(1000);
    Serial.print("I2C Master: Read ");
    //Serial.println(c);
    for (int i = 0; i < numCommands ; i++) {
      if (commands[i] == 'R')
      {
        Wire.beginTransmission(nanoSlave);
        Wire.write('R');
        Wire.endTransmission();
      }
      else if (commands[i] == 'G')
      {
        Wire.beginTransmission(nanoSlave);
        Wire.write('G');
        Wire.endTransmission();
      }
      else if (commands[i] == 'B')
      {
        Wire.beginTransmission(nanoSlave);
        Wire.write('B');
        Wire.endTransmission();
      }
      else if (commands[i] == 'O')
      {
        Wire.beginTransmission(nanoSlave);
        Wire.write('O');
        Wire.endTransmission();
      }
      delay(500);
    }
    bufferFull = false;
    Wire.beginTransmission(nanoSlave);
    Wire.write('O');
    Wire.endTransmission();    
    Serial.println("done\n-------------");
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

