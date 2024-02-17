
int diodePin = 3;  // set diode, push button and potentiometer pins
int buttonPin = 9;

int potPin = A0;
int pot_value = 0;

int resPin = A1;
int res_value = 0;

byte lastButtonState = LOW;
byte diodeState = LOW;

void setup() {

  Serial.begin(9600);
  pinMode(diodePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  
  pinMode(potPin, INPUT);

}

void loop() {

  byte buttonState = digitalRead(buttonPin);
  pot_value = map(analogRead(potPin), 0, 1023, 0, 255);

  if (buttonState != lastButtonState) {    // change states to make the button turn on or off the diode
     lastButtonState = buttonState;
    if (buttonState == LOW) {
      diodeState = (diodeState == HIGH) ? LOW: HIGH;
      digitalWrite(diodePin, diodeState);
    }
  }

  if(diodeState == HIGH){            // change the brightness with potentiometer
  analogWrite(diodePin, pot_value);
  }
  
  res_value = analogRead(resPin);   // read the value from photoresistor

  Serial.print("Potentiometer value: "); 
  Serial.println(pot_value); 
  Serial.print("Photoresistor value: "); 
  Serial.println(res_value); 
  delay(1000);
}

