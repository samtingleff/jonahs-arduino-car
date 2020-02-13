#include <AFMotor.h>
#include <Servo.h>

// ultrasonic
#define ultrasonicTrigPin A2
#define ultrasonicEchoPin A1

// motors
AF_DCMotor frontLeftMotor(1, MOTOR12_1KHZ);
AF_DCMotor frontRightMotor(4, MOTOR34_1KHZ);
AF_DCMotor backLeftMotor(2, MOTOR12_1KHZ);
AF_DCMotor backRightMotor(3, MOTOR34_1KHZ);

int frontLeftMotorDirection = FORWARD;
int frontRightMotorDirection = FORWARD;
int backLeftMotorDirection = FORWARD;
int backRightMotorDirection = FORWARD;

// servo
Servo myservo;
int servoPosition = 90;

void setup() {
  Serial.begin(115200);           // set up Serial library at 115200 
  // setup distance sensor
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);

  // setup motors
  frontLeftMotor.setSpeed(0);
  frontRightMotor.setSpeed(0);
  backLeftMotor.setSpeed(0);
  backRightMotor.setSpeed(0);

  // setup servo
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  rawMotor ( 250, 250, 250, 250 );
  long ultrasonicDistance = distanceToObject();
  if (ultrasonicDistance < 20) {
    rawMotor ( 0, 0, 0, 0 );
    delay(1000);
    rawMotor( -250, -250 ,-250 ,-250);
    delay(2000);
    rawMotor (0, 0, 0, 0 );
    delay(1000);
  }
}

void setServoAngle(int angle) {
  myservo.write(angle);
}

/**
 * Return the distance to nearest object in cm
 */
long distanceToObject() {
  long ultrasonicDuration = 0, ultrasonicDistance = 0;
  // this stuff appears necessary to keep the sensor warm
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  ultrasonicDuration = pulseIn(ultrasonicEchoPin, HIGH);
  ultrasonicDistance = (ultrasonicDuration/2) / 29.1;
  return ultrasonicDistance;
}

/**
 * Set raw motor speed on all four motors.
 * Use negative values for backwards, positive values for forwards.
 */
void rawMotor(int fl, int fr, int bl, int br) {
  frontLeftMotorDirection = (fl > 0) ? FORWARD : BACKWARD;
  frontLeftMotor.setSpeed(abs(fl));
  frontLeftMotor.run(frontLeftMotorDirection);

  frontRightMotorDirection = (fr > 0) ? FORWARD : BACKWARD;
  frontRightMotor.setSpeed(abs(fr));
  frontRightMotor.run(frontRightMotorDirection);

  backLeftMotorDirection = (bl > 0) ? FORWARD : BACKWARD;
  backLeftMotor.setSpeed(abs(bl));
  backLeftMotor.run(backLeftMotorDirection);

  backRightMotorDirection = (br > 0) ? FORWARD : BACKWARD;
  backRightMotor.setSpeed(abs(br));
  backRightMotor.run(backRightMotorDirection);
}
