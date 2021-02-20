#include <Servo.h>
Servo servo;
Servo servoSwitch;
int pressureReading;
int waterReading;
int counter;

void setup() {
  Serial.begin(9600);
  
  // first servo
  servo.attach(9);
  servo.write(25);

  // second servo
  servoSwitch.attach(10);
  servoSwitch.write(180);

  counter = 0;
}

void loop() {
  // reads the pressure sensor 
  pressureReading = analogRead(A0);
  Serial.print("Sensor value = ");
  Serial.println(pressureReading);

  // reads the water level sensor 
  waterReading = analogRead(A1);
  //Serial.print("Water sensor value = ");
  //Serial.println(waterReading);

  // water sensor
  // if the water level is low, pump water
  if (waterReading <= 300)
  {
    // this will move the servo to push the button which will trigger the pump
    servoSwitch.write(0);
    servoSwitch.write(105); 
    delay(10000);
    servoSwitch.write(0);
  }

  // pressure sensor 
  // if the bowl is empty and the dog hasn't eaten in the last 6 hours 
  if (pressureReading <= 300 && (counter == 216000) || (counter == 0))
  {
    servo.write(150);
    delay(600);
    servo.write(25);

    counter = 1;
  }

  else 
  {
    Serial.println(counter);

    counter++;
  }

  delay(100);
}
