#define GIVE_INPUT     'a'  // the byte signalling that the computer wants input
#define ISSUE_COMMAND  'b'  // the byte signalling that the computer issues a command
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

#include <FastLED.h>

const int toggleSwitch1 = 23;
const int toggleSwitch2 = 22;
const int toggleSwitch3 = 21;
const int toggleSwitch4 = 20;
const int tempSensor = 19;
const int lightSensor = 18;
const int rotarySwitch = 17;
const int ledStrip = 16;

//Output from the sensor:
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

//Formatted color values:
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

//Values used for calibration
int redMin;
int redMax;
int greenMin;
int greenMax;
int blueMin;
int blueMax;

int color = 0;

void setup() {
  Serial.begin(115200);
  pinMode(toggleSwitch1, INPUT_PULLUP);
  pinMode(toggleSwitch2, INPUT_PULLUP);
  pinMode(toggleSwitch3, INPUT_PULLUP);
  pinMode(toggleSwitch4, INPUT_PULLUP);
  pinMode(tempSensor, INPUT);
  pinMode(lightSensor, INPUT);
  pinMode(rotarySwitch, INPUT);
  pinMode(ledStrip, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Set frequency scaling to 20%:
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  calibrate();//calibrate sensor (look at serial monitor)
} 

void loop() {
  readColor();//read sensor
  decideColor();//format color values
  if(Serial.available()) {
    char byteIn = Serial.read();
    if(byteIn == GIVE_INPUT){
      
      giveInput();
    }
  }
 
 
  // giveInput();
  //digitalWrite(ledStrip, HIGH); 
  delay(20);
  
}

void giveInput(){
  String sOutput = "";

  // add value analog A9  
  int ts1 = digitalRead(toggleSwitch1);
  sOutput = sOutput + ts1;
                
  // add value analog A8 
  int ts2 = digitalRead(toggleSwitch2);
  sOutput = sOutput + ","+ ts2;
                
  // add value analog A7  
  int ts3 = digitalRead(toggleSwitch3);
  sOutput = sOutput + ","+ ts3;

  // add value analog A6  
  int ts4 = digitalRead(toggleSwitch4);
  sOutput = sOutput + ","+ ts4;

  // add value analog A5
  int tempS = analogRead(tempSensor);
  sOutput = sOutput + ","+ tempS;
    
  // add value analog A4
  int ls = analogRead(lightSensor);
  sOutput = sOutput + "," + ls;
    
  //add value analog A3
  int rs = analogRead(rotarySwitch);
  sOutput = sOutput + "," + rs; 
    
  //add value Color Sensor
  int cs;
  switch (color) {
    //white
    case 1: cs = 1; break;
    //yellow
    case 2: cs = 2; break;  
    //red
    case 3: cs = 3; break;
    //green
    case 4: cs = 4; break;
    //blue
    case 5: cs = 5; break;
    //unknown
    default: cs = 6; break;
  }
    analogRead(cs);
    sOutput = sOutput + "," + cs; 
    Serial.println(sOutput);
}

void decideColor() {//format color values
  //Limit possible values:
  
  redColor = constrain(redColor, 0, 255);
  greenColor = constrain(greenColor, 0, 255);
  blueColor = constrain(blueColor, 0, 255);
  //find brightest color:
  
  int maxVal = max(redColor, blueColor);
  maxVal = max(maxVal, greenColor);
  //map new values
  redColor = map(redColor, 0, maxVal, 0, 255);
  greenColor = map(greenColor, 0, maxVal, 0, 255);
  blueColor = map(blueColor, 0, maxVal, 0, 255);
  redColor = constrain(redColor, 0, 255);
  greenColor = constrain(greenColor, 0, 255);
  blueColor = constrain(blueColor, 0, 255);
  //light led
  
  //decide which color is present (you may need to change some values here):
  if (redColor > 250 && greenColor > 250 && blueColor > 250) {
    color = 1;//white
  }
  else if (redColor > 200 &&  greenColor > 200 && blueColor < 100) {
    color = 2;//yellow
  }
  else if (redColor > 250 && greenColor < 200 && blueColor < 200) {
    color = 3;//red
  }
  else if (redColor < 200 && greenColor > 250 && blueColor < 200) {
    color = 4;//green
  }
  else if (redColor < 200 /*&& greenColor < 200*/ && blueColor > 250) {
    color = 5;//blue
  }
  else {
    color = 0;//unknown
  }
}
void calibrate() {
 
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redMin = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenMin = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueMin = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(13, LOW);
  delay(2000);
  //set calibration values:
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redMax = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenMax = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueMax = pulseIn(sensorOut, LOW);
  delay(100);
  digitalWrite(13, LOW);
}


void readColor() {//get data from sensor
  //red:
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, redMin, redMax, 255, 0);
  delay(100);
  //green:
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, greenMin, greenMax, 255, 0);
  delay(100);
  //blue:
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, blueMin, blueMax, 255, 0);
  delay(100);
}
