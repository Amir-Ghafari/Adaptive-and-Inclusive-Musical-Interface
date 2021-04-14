
#include <SoftwareSerial.h>
SoftwareSerial HM10(10, 11); // RX = 10, TX = 11
char appData;  
String inData = "";
void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate

  Serial.begin(115200);
  Serial.setTimeout(50);
  HM10.begin(115200); //open BLE connection
  HM10.setTimeout(50); //set timeout
  HM10.write("AT+ROLE1");
  delay(50);
  HM10.write("AT+NOTI1");
  delay(50);
  HM10.write("AT+CONc5c9c331914b");
  delay(50);
}
void loop()
{
  String c;
  if (HM10.available()) {
    //What is sent back from the BT module
    c = HM10.readStringUntil();
}
}
