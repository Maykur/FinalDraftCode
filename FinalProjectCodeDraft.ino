/*
  Code mixture of projects 9 + 12
    Motor code is from project 9
    Piezo code is from project 12

  Intended design is for the piezo to capture the vibrations of the toilet when flushing,
  allowing the motors inside to rotate key pieces of our device, in order for the air freshener
  to function on its own.
*/

const int piezo = A0;     // pin the piezo is attached to
const int motorPin = 9;  // pin the motor is attached to

int mySerialBaudRate = 9600;

// variable for the piezo value
int knockVal;

// variables for the high and low limits of the knock value
const int quietKnock = 400;
const int loudKnock = 700;

void setup() {
  // set the motor pin as an output
  pinMode(motorPin, OUTPUT);

  // start serial communication for debugging
  Serial.begin(mySerialBaudRate);
}

void loop() {
    // check the value of the piezo
    knockVal = analogRead(piezo);

    Serial.print('Baud rate is: ');
    Serial.println(mySerialBaudRate);

      if (checkForKnock(knockVal) && !digitalRead(motorPin)==HIGH) {
        digitalWrite(motorPin, HIGH); //turn motor on
        delay(2000); //wait time
        digitalWrite(motorPin, LOW); //turn motor off
      }
    delay(1000);
}

// this function checks to see if a detected knock is within max and min range
bool checkForKnock(int value) {
  // if the value of the knock is greater than the minimum, and larger
  // than the maximum
  if (value > quietKnock && value < loudKnock) {
    // print out the status
    Serial.print("Valid knock of value ");
    Serial.println(value);
    // return true
    return true;
  }
  // if the knock is not within range
  else {
    // print status
    Serial.print("Bad knock value ");
    Serial.println(value);
    // return false
    return false;
  }
}
