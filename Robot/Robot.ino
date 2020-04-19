

#include <AccelStepper.h>
#include <AFMotor.h>

AF_Stepper motor1(200, 1); //grabber
AF_Stepper motor2(200, 2); // grapper angle

const int trigPin = A0;
const int echoPin = A1;
// Variables for the duration and the distance
long duration;
int distance;

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
void forwardstep() {  
  motor1.onestep(FORWARD, SINGLE); //open
  motor2.onestep(FORWARD, SINGLE); // up
}
void backwardstep() {  
  motor1.onestep(BACKWARD, SINGLE); // close
  motor2.onestep(BACKWARD, SINGLE); // down 
}

AccelStepper stepper(forwardstep, backwardstep); // use functions to step

void setup()
{  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!"); 
  stepper.setSpeed(50);	
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop()
{  
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.println(".");
  delay(100);
  if (distance < 10) {
    grab();
  }
   stepper.runSpeed();
}

void grab(){
  motor2.onestep(FORWARD, SINGLE); 
}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
