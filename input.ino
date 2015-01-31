

// These constants won't change.  They're used to give names
// to the pins used:
  const int y1 = A0;  
  const int x2 = A1;
  const int x1 = A2;
  const int y2 = A3;
//The intial reading values
  int y1Value = 0;
  int x2Value = 0;
  int x1Value = 0;
  int y2Value = 0;
//The final value, from 0 to 255
  int y1Final = 0;
  int x2Final = 0;
  int x1Final = 0;
  int y2Final = 0;
int topSwitch;
//Setup, self explainitory
void setup() {
  // initialize serial communications at 9600 bps:
    Serial.begin(9600); 
    pinMode(12,INPUT);
    pinMode(13,OUTPUT);
    digitalWrite(12, HIGH);
    
  //Starts the gamepad stuff
    Gamepad.begin();
}

void loop() {
  topSwitch = digitalRead(12);
  
  // read the analog in value:
    y2Value =  map(analogRead(y2), 415, 605, 610, 420);
    x2Value =  map(analogRead(x2), 415, 605, 420, 610);  
    x1Value =  map(analogRead(x1), 415, 605, 420, 610);
    y1Value =  map(analogRead(y1), 584, 442, 610, 420);
  //Some math stuff to get it to -128 to 127
    x2Final = constrain(map(x2Value, 420, 610, -128, 127), -128, 127);
    x1Final = constrain(map(x1Value, 420, 610, -128, 127), -128, 127);
    y2Final = constrain(map(y2Value, 420, 610, -128, 127), -128, 127);
    
    if (topSwitch == 0){
    y1Final = constrain(map(y1Value, 610, 420, 0, -128), -128, 0);
  }
    if (topSwitch == 1){
      y1Final = constrain(map(y1Value, 610, 420, 0, 127), 0, 127);
    }
     analogWrite(13, abs(y1Final*2));
  
  //This is the code to print it. Can be removed without gamepad being affected.
    
    /*Serial.print("sensor x2 = " );                       
    Serial.print(x2Final); 
    Serial.print(" sensor x1 = " );                       
    Serial.print(x1Final); 
    Serial.print(" sensor y2= " );                       
    Serial.print(y2Final);  
    Serial.print(" sensor y1= " );                     
    Serial.println(y1Final); 
    //This code sets the current x and y axis, and gamepad.write sends it over usb.
    Serial.println(topSwitch); 
    */
    Gamepad.xAxis(int16_t(x1Final)<<8);
    Gamepad.yAxis(int16_t(y1Final)<<8);
    Gamepad.rxAxis(int16_t(x2Final)<<8);
    Gamepad.ryAxis(int16_t(y2Final)<<8);
    Gamepad.write();
  //30 millisecond delay, because 2 crashed my laptop...
  delay(10);                     
}

