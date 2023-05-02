// Servo
#include <Servo.h>
Servo servo;
int pos = 90;

// Moisture sensor
int sensor_pin = A0;
int output_value;

// Ultrasonic sensor
const int trigPin = 4;
const int echoPin = 3;
// Defines variables
long duration;
int distance;

void setup()
{
  Serial.println("Reading from the sensor...");
  delay(2000);
  servo.attach(9);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
}

void garbage_classifier()
{
  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 0, 0, 100);
  Serial.print("Mositure: ");
  Serial.println(output_value);

  delay(4000);

  if (output_value > -80)
  {
    servo.write(150);
    Serial.println("Wet");
  }
  else if (output_value <= -80)
  {
    servo.write(30);
    Serial.println("Dry");
  }
  else
  {
    servo.write(90);
    Serial.println("Neutral");
  }

  delay(2000);
}

void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10)
  {
    garbage_classifier();
  }
  else
  {
    servo.write(90);
  }
}
