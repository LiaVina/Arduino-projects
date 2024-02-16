#include <Servo.h>
#include <Keypad.h>

//////////////////////////////////////////////////////////////////////////////////////////////

int GREEN = 12; //RGB diode pins
int RED = 13;

Servo servo_gate;  // create servo object to control a servo
int pos = 0;

String gate_password = "1289";
String password = "";

//////////////////////////////////////////////////////////////////////////////////////////////

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the symbols on the buttons of the keypads
char buttons[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad
//initialize an instance of class Keypad
Keypad gate_keypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

//////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600); //communicate with serial monitor, 9600 byte per sec
  servo_gate.attach(2); // attaches the servo on pin 2 to the servo object
  password.reserve(4); //number of digits = 4
  
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT);
}

void open_gate(){
  for(pos = 0; pos <= 100; pos++) // goes from 0 degrees to 100 degrees
    servo_gate.write(pos);
    analogWrite(RED, 0);   //light green diode
    analogWrite(GREEN, 255);
  delay(1000);
}

void close_gate(){
    for(pos = 100; pos >= 0; pos--) // goes from 100 degrees to 0 degrees
    servo_gate.write(pos);
    analogWrite(RED, 255);  //light red diode
    analogWrite(GREEN, 0);
  delay(1000);
}


void loop(){

  analogWrite(RED, 255);

  char key = gate_keypad.getKey();;
  
  if(key){
    Serial.println(key);
    
    if(key == '#') {      
      if(password == gate_password){   // if password is correct open the gate
        open_gate();
        delay(2000); 

        close_gate(); ////***////

      } 
      else {
        Serial.println("Wrong password");
      }
      password = "";   // clear input string
    } 
    else {
      password += key;    
    }
  }
}
