//TODO: Add more button stuff, when Mike adds mure buttonz. Also, clean up the math stuff. I know that it can be done better
// These constants won't change.  They're used to give names
// to the pins used:
const int y1 = A0;
const int x2 = A1;
const int x1 = A2;
const int y2 = A3;
const int switchPin = 12;
const int LED = 13;
//The intial reading values
int y1Value = 0;
int x2Value = 0;
int x1Value = 0;
int y2Value = 0;
//This is the state of the top switch
int topSwitch = 1;
//Setup, self explainitory
void setup() {
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
    //Sets Pin 12 to input for the top switch
    pinMode(switchPin,INPUT);
    digitalWrite(switchPin, HIGH);
    //Sets the LED pin on the Arduino to output.
    pinMode(LED,OUTPUT);
    //Starts the gamepad stuff
    Gamepad.begin();
}
void loop() {
    //As y1 input increases, increase LED brightness
    analogWrite(13, abs(y1Value*2));
    //Gets the state of the switch
    topSwitch = digitalRead(12);
    // read the analog in value:
    y2Value =  map(analogRead(y2), 415, 605, 610, 420);
    x2Value =  map(analogRead(x2), 415, 605, 420, 610);
    x1Value =  map(analogRead(x1), 415, 605, 420, 610);
    y1Value =  map(analogRead(y1), 584, 442, 610, 420);
    //Some math stuff to get it to -128 to 127
    y2Value = constrain(map(x2Value, 420, 610, -128, 127), -128, 127);
    x1Value = constrain(map(x1Value, 420, 610, -128, 127), -128, 127);
    y2Value = constrain(map(y2Value, 420, 610, -128, 127), -128, 127);
    //For reverse
    if (topSwitch == 0){
        y1Value = constrain(map(y1Value, 610, 420, 0, -128), -128, 0);
    }
    if (topSwitch == 1){
        y1Value = constrain(map(y1Value, 610, 420, 0, 127), 0, 127);
    }
    //Function that prints joystick info over usb when the reverse button is held.
    printValues(topSwitch);
    //This stuff sets the gamepad object to numbers, and converts them to 16 bit. Then, it is sent over USB.
    Gamepad.xAxis(int16_t(x1Value)<<8);
    Gamepad.yAxis(int16_t(y1Value)<<8);
    Gamepad.rxAxis(int16_t(x2Value)<<8);
    Gamepad.ryAxis(int16_t(y2Value)<<8);
    Gamepad.write();
    //10 millisecond delay, because 2 crashed my laptop...
    delay(10);
}
void printValues(int a){
  if ( a==0){
    Serial.print("sensor x2 = " );
    Serial.print(x2Value);
    Serial.print(" sensor x1 = " );
    Serial.print(x1Value);
    Serial.print(" sensor y2= " );
    Serial.print(y2Value);
    Serial.print(" sensor y1= " );
    Serial.println(y1Value);
    Serial.println(topSwitch);
  }
}
