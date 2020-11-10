#define GIVE_INPUT     'a'  // the byte signalling that the computer wants input
#define ISSUE_COMMAND  'b'  // the byte signalling that the computer issues a command

const int toggleSwitch1 = 23;
const int toggleSwitch2 = 22;
const int toggleSwitch3 = 21;
const int toggleSwitch4 = 20;
const int tempSensor = 19;
const int lightSensor = 18;
//const int rotarySwtich = 
//const int rotaryEncoder = 1;
void setup() {
  Serial.begin(115200);
  pinMode(toggleSwitch1, INPUT_PULLUP);
  pinMode(toggleSwitch2, INPUT_PULLUP);
  pinMode(toggleSwitch3, INPUT_PULLUP);
  pinMode(toggleSwitch4, INPUT_PULLUP);
  pinMode(tempSensor, INPUT);
  pinMode(lightSensor, INPUT);
  //pinMode(rotaryEncoder, INPUT);
  
}

void loop() {
 // DONT FORGET TO UNCOMMENT
  if(Serial.available()) {
    char byteIn = Serial.read();

    if(byteIn == GIVE_INPUT){
      giveInput();
    }
  }
 // giveInput();
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
    
    /*int re = digitalRead(rotaryEncoder);
    sOutput = sOutput + "," + re;
    */
    Serial.println(sOutput);
}
