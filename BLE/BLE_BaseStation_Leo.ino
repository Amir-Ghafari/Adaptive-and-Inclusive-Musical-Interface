
#include <SoftwareSerial.h>
SoftwareSerial HM10(10, 11); // RX = 10, TX = 11
char appData;  
String inData = "";
void setup()
{
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(13, OUTPUT); // onboard LED
  digitalWrite(13, LOW); // switch OFF LED

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
     while (HM10.available() > 0) {
      String response = HM10.readString();
}
}
