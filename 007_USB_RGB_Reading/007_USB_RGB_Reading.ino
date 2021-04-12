// This code allows user to connect sensor to ESP32 and send data to serial monitor throught USB connection.
// Base code found at https://wiki.dfrobot.com/SEN0187_RGB_and_Gesture_Sensor
// Readouts are into serial monitor.
// Make sure to download proper library before uploading.


#include <Wire.h>
#include <SparkFun_APDS9960.h>

// Pins
#define APDS9960_INT 14 // Needs to be an interrupt pin

SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void setup() {

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

void loop() {
  if( isr_flag == 1 ) {
    handleGesture();
      if(digitalRead(APDS9960_INT) == 0){
      apds.init();
      apds.enableGestureSensor(true);
    }

    isr_flag = 0;
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
