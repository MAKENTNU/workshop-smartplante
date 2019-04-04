/* We are using a HSR-1425CR continuous rotation servo. 
 *  These have no feedback regarding how far you rotate, so we have to test how long it has to rotate to turn the valve.
 *  One way to turn the servo on is to use writeMicrosecond() and delay().
*/

#include <Servo.h>

// Set up the pins
int moistPin = A5;
int moistPowerPin = 2;
int ledPin = 3;
int servoPin = 4;

// Initialize sensor value
int value = 0;

// Initialize servo object
Servo servo;


void setup() {
  // Initialize pins and attach servo pin to the servo object
  pinMode(moistPin, INPUT);
  pinMode(moistPowerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
  
  Serial.begin(9600);

  // Initialize servo rotation. When set to 1500, the servo will not turn.
  servo.writeMicroseconds(1500);
}

void loop() {
  // To save some power (and output pins), we use a regular digital pin and turn it on right before we 
  // read the sensor value, and then off again right after.
  digitalWrite(moistPowerPin, HIGH);
  value = analogRead(moistPin);
  digitalWrite(moistPowerPin, LOW);
  
  Serial.println(value); 

  // If the sensor value is below some threshold we want to turn on the LED and refill some water.
  if (value < 150){
    Serial.println("Åpne ventil");
    digitalWrite(ledPin, HIGH);
    servo.writeMicroseconds(1300);
    delay(350);
    servo.writeMicroseconds(1500);
    delay(20000);
    
    servo.writeMicroseconds(1300);
    delay(1020);
    servo.writeMicroseconds(1500);
    Serial.println("Lukk ventil");
  } else{
    digitalWrite(ledPin, LOW);  
  }
  
  delay(1000);
  
}
