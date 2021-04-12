// This code allows user to connect sensor to ESP32 and send data to serial monitor throught USB connection.
// Base code found at https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/
// Readouts are into serial monitor and rounded in inches and centimetres.

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>



// IMU
/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to SCL pin (analog 5 on Arduino UNO)
   Connect SDA to SDA pin (analog 4 on Arduino UNO)
   Connect VDD to 3-5V DC (depending on your board's logic level)
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
   2015/AUG/27  - Added calibration and system status helpers
*/

/* Set the delay between fresh samples */

// #define BNO055_SAMPLERATE_DELAY_MS (100)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
// Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);



// RGB
/*
// Pins
#define APDS9960_INT 14 // Needs to be an interrupt pin

SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
*/



// Ultrasonic
#define trigPin 27
#define echoPin 33 // GPIO pins next to eachother
long duration, cm, inches; // defining some variables



// PIR
#define sensorPin 15
#define indicator 13 // Uses microcontroller light as an indicator for the sensor, optional.
long state; // defining some variables



// Piezo as Knock
/*
#define ledPin 13;      // LED connected to digital pin 13
#define knockSensor 32; // the piezo is connected to analog pin 0
const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light
*/



// Functions:
/*
void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
*/
// void displayCalStatus(void)
// {
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  // uint8_t system, gyro, accel, mag;
  // system = gyro = accel = mag = 0;
  // bno.getCalibration(&system, &gyro, &accel, &mag);
  /* The data should be ignored until the system calibration is > 0 */
  // Serial.print("\t");
  // if (!system)
  // {
  //   Serial.print("! ");
  // }
  /* Display the individual values */
  // Serial.print("Sys:");
  // Serial.print(system, DEC);
  // Serial.print(" G:");
  // Serial.print(gyro, DEC);
  // Serial.print(" A:");
  // Serial.print(accel, DEC);
  // Serial.print(" M:");
  // Serial.print(mag, DEC);
// }



void setup() {


  
  // Serial Begin here
  Serial.begin (9600);



  // IMU
  // Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  // if(!bno.begin())
  // {
    /* There was a problem detecting the BNO055 ... check your connections */
  //  Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  //  while(1);
  // }

  // delay(1000);

  /* Display some basic information on this sensor */
  // displaySensorDetails();

  /* Optional: Display current status */
  // displaySensorStatus();

  // bno.setExtCrystalUse(true);


 
  // RGB
  /*
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
  */


  
  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);



  // PIR
  pinMode(sensorPin,INPUT);
  pinMode(indicator,OUTPUT);



  // Piezo as Knock
  /*
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
  */
}


 
void loop() {



  // IMU:
  /* Get a new sensor event */
  // sensors_event_t event;
  // bno.getEvent(&event);

  /* Display the floating point data */
  // Serial.print("X: ");
  // Serial.print(event.orientation.x, 4);
  // Serial.print("\tY: ");
  // Serial.print(event.orientation.y, 4);
  // Serial.print("\tZ: ");
  // Serial.print(event.orientation.z, 4);

  /* Optional: Display calibration status */
  // displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  /* New line for the next sample */
  // Serial.println("");

  /* Wait the specified delay before requesting nex data */
  // delay(BNO055_SAMPLERATE_DELAY_MS);



  // RGB:
  /*
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
   */


   
  // Ultrasonic:
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
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();



  // PIR:
  state = digitalRead(sensorPin);
  digitalWrite(indicator,state);
  if(state == 1)Serial.println("Somebody is in this area!");
  else if(state == 0)Serial.println("No one!");



  // Piezo as Knock:
  /*
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // toggle the status of the ledPin:
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");
  } 
  */


  
  delay(1000);
}
