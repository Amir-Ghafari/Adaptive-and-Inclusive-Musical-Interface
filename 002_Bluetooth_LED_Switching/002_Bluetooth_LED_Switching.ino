// This Code allows the user to turn the LED on and off on the ESP32 featherboard. Uses the Bluetooth Terminal on a phone to test. 
// Base code is found at https://circuitdigest.com/microcontroller-projects/using-classic-bluetooth-in-esp32-and-toogle-an-led
// However, this can be repurposed to a computer as well.  
// Step 1: Compile and upload code to ESP32.
// Step 2: Download "Bluetooth Terminal" App.
// Step 3: Through the app, pair and connect to the ESP32, in this code it is called "ESP32_LED_Control".
// Step 4: Enter 1 to turn LED on and 0 to turn LED off.   

#include "BluetoothSerial.h"
BluetoothSerial ESP_BT;
#define LED 13

int incoming = 0;


void setup() {

  
  Serial.begin(9600);
  ESP_BT.begin("ESP32_LED_Control");
  Serial.println("Bluetooth device is ready");

  pinMode(LED, OUTPUT);

}

void loop() {

  if(ESP_BT.available()) {

    incoming = ESP_BT.read();
    Serial.print("recieved");

        if(incoming == 49) {

      digitalWrite(LED,HIGH);
      ESP_BT.println("LED Turned ON");
      
    }

    if(incoming == 48) {

      digitalWrite(LED,LOW);
      ESP_BT.println("LED Turned Off");
      
    }
  }

  delay(20);
  
}
