// This code allows user to connect sensor to ESP32 and send data to serial monitor throught USB connection.
// Base code found at https://wiki.dfrobot.com/PIR_Motion_Sensor_V1.0_SKU_SEN0171
// Readouts are into serial monitor.

#define sensorPin 15
#define indicator 13 // Uses microcontroller light as an indicator for the sensor, optional.
long state; // defining some variables

void setup()
{
  pinMode(sensorPin,INPUT);
  pinMode(indicator,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  state = digitalRead(sensorPin);
  digitalWrite(indicator,state);
  if(state == 1)Serial.println("Somebody is in this area!");
  else if(state == 0)Serial.println("No one!");
  delay(500);
}
