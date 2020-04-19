#include <Stepper.h>
#include <NewPing.h>

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
const int stepsPerRevolution = 1000;  // change this to fit the number of steps per revolution 2048
const int rolePerMinute = 10;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int pingPin = 7;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  
  motor_clockwise();
  delay (100);
  motor_counterClock();
  delay(100);
}

void motor_clockwise() {  
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  for (int i = 0; i <= 16; i++){
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm");
    delay(5);
    }
}

void motor_counterClock() {
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  for (int i = 0; i <= 16; i++){
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm");
    delay(5);
    }
}

  
