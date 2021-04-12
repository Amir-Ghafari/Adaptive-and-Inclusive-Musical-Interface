// This code allows user to connect sensor to ESP32 and send data to serial monitor through Bluetooth connection to phone.
// See 002 for how to connect to phone bluetooth.
// Base code found at https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
// Readouts are into BT monitor and rounded in inches and centimetres.
// The LED switch determines if the readouts appear, if LED is 1, the sensor data is transmitted, vice versa.

#include "BluetoothSerial.h"
BluetoothSerial ESP_BT;

#define LED 13
#define trigPin 12
#define echoPin 27 // GPIO pins next to eachother

int incoming = 0;
int toggle = 0;
long duration, cm, inches; // defining some variables

void setup() {

  //Serial Port begin
  Serial.begin (9600);

  ESP_BT.begin("ESP32_LED_Control");
  Serial.println("Bluetooth device is ready");

  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  if (ESP_BT.available()) {

    incoming = ESP_BT.read();
    Serial.print("recieved");

    if (incoming == 49) {

      digitalWrite(LED, HIGH);
      ESP_BT.println("LED Turned ON");
      toggle = 1;

    }

    if (incoming == 48) {

      digitalWrite(LED, LOW);
      ESP_BT.println("LED Turned Off");
      toggle = 0;

    }
  }

  delay(20);


  if (toggle == 1) {
    
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

    ESP_BT.println(inches);
    ESP_BT.println("in, ");
    ESP_BT.println(cm);
    ESP_BT.println("cm");
    ESP_BT.println();

    delay(250);
  }
}
