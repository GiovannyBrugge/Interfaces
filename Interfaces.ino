#define GIVE_INPUT     'a'  // the byte signalling that the computer wants input
#define ISSUE_COMMAND  'b'  // the byte signalling that the computer issues a command
#include <FastLED.h>

const int toggleSwitch1 = 23;
const int toggleSwitch2 = 22;
const int toggleSwitch3 = 21;
const int toggleSwitch4 = 20;
const int tempSensor = 19;
const int lightSensor = 18;
const int rotarySwitch = 17;
const int ledStrip = 16;
const int colorSensor1 4;
const int colorSensor2 5;
const int colorSensor3 6;
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
}

void loop() {
 
  if(Serial.available()) {
    char byteIn = Serial.read();

    if(byteIn == GIVE_INPUT){
      giveInput();
    }
  }
 // giveInput();
  digitalWrite(ledStrip, HIGH); 
  delay(20);
  //digitalWrite(ledStrip, HIGH);  
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

     
      
    
    Serial.println(sOutput);
}
