#include <SoftwareSerial.h>

const int PIN_TXD = 4, PIN_RXD = 5, PIN_AKTYWUJACY = 3, CZESTOTLIWOSC = 9600;

SoftwareSerial Gsm(PIN_TXD, PIN_RXD);

void setup() {
  pinMode(PIN_AKTYWUJACY, INPUT);
  Gsm.begin(CZESTOTLIWOSC);
  Serial.begin(CZESTOTLIWOSC);
}

void loop() {
  if(digitalRead(PIN_AKTYWUJACY) == HIGH){
    Serial.write("\nWyslalem Smsa\n");
    wyslijSms();
  }
  while(Gsm.available()){
    Serial.write(Gsm.read());
  }
  while(Serial.available()){
    Gsm.write(Serial.read());
  }
}

void wyslijSms(){
  Gsm.write("AT+CMGF=1\r\n");
  delay(100);
  Gsm.write("AT+CMGS=\"+48xxxxxxxxx\"\r\n");
  delay(100);
  Gsm.write("Test bramki sms");
  delay(100);
  Gsm.write((char)26);
  delay(100);   
}
