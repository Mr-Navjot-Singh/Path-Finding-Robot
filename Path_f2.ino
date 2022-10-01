#include <AFMotor.h>
#include <Servo.h>
#define trigPin A2    // Trigger
#define echoPin A1    // Echo

Servo myservo;
AF_DCMotor motorL(4);
AF_DCMotor motorR(3);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(10);
  motorL.setSpeed(150); // set motors speed
  motorL.run(RELEASE);
  motorR.setSpeed(150);
  motorR.run(RELEASE);
  delay(2000);
}

double cm, leftdis, rightdis;

void loop() { 
 
  double cm = distance();
  myservo.write(90);
    
  if(cm < 30)
  {
    Stop();
    
    leftdis=0, rightdis=0;
    
    //left look
    myservo.write(150); 
    delay(1000);             
    leftdis = distance();
      
    // look straigth
    myservo.write(90);
    delay(500);
    
    // right look
    myservo.write(30);
    delay(1000);          
    rightdis = distance(); 
      
    // look straigth
    myservo.write(90);
    delay(500);
    
    back();
    
    if(rightdis>leftdis)
    {
      turnRight();
      forward();
    }
    else if (rightdis<leftdis)
    {
      turnLeft();
      forward();
    }
    else
    {
      forward();
    }
  }
  else
  {
    forward();
  }
}

double duration, dist;
double distance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration/2) / 29.1;
  return dist;
}
void forward()
{
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}
void turnLeft()
{
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
  delay(1000);
  Stop();
}
void turnRight()
{
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
  delay(1000);
  Stop();
}
void Stop()
{
  motorL.run(RELEASE);
  motorR.run(RELEASE);
  delay(1000);
}
void back()
{
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
  delay(500);
  Stop();
}
