
/*
  Scan
  This example scans for BLE peripherals and prints out their advertising details:
  address, local name, advertised service UUID's.
  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  This example code is in the public domain.
*/

#include <ArduinoBLE.h>



void setup() {
  Serial.begin(9600);
  while (!Serial);

    // configure the inputSensor pin as input
  pinMode(inputSensor, INPUT_PULLUP);


  // initialize the BLE hardware
  BLE.begin();
  Serial.println("BLE Central - Base station");

   // start scanning for peripherals (scans for service UUID)
  BLE.scanForUuid("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

  
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();

    if (peripheral.localName() != "sensorInput") {
      return;
    }

       // stop scanning
    BLE.stopScan();

        controlLed(peripheral);

    // peripheral disconnected, start scanning again
    BLE.scanForUuid("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

    void controlLed(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");

  if (peripheral.connect()) {
    Serial.println("Connected");
  } else {
    Serial.println("Failed to connect!");
    return;
  }

    // discover peripheral attributes
  Serial.println("Discovering attributes ...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Attributes discovered");
  } else {
    Serial.println("Attribute discovery failed!");
    peripheral.disconnect();
    return;
  }

    // retrieve the characteristic
  BLECharacteristic controllerCharacteristic = peripheral.characteristic("19B10014-E8F2-537E-4F6C-D104768A1214");
  if (!ledCharacteristic) {


  while (peripheral.connected()) {
    // while the peripheral is connected

        // check if the value of the simple key characteristic has been updated
    if (controllerCharacteristic.valueUpdated()) {
      // yes, get the value, characteristic is 1 byte so use byte value
      byte value = 0;
  //Store in a pin
    controllerCharacteristic.readValue(value);

      }
    }
  }

  Serial.println("Peripheral disconnected");
}
