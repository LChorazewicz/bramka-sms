#include <SoftwareSerial.h>

const int PIN_TXD = 4, PIN_RXD = 5, PIN_AKTYWUJACY = 3, CZESTOTLIWOSC = 9600;
String telefon, wiadomosc;

SoftwareSerial Gsm(PIN_TXD, PIN_RXD);

void setup() {
  pinMode(PIN_AKTYWUJACY, INPUT);
  Gsm.begin(CZESTOTLIWOSC);
  Serial.begin(CZESTOTLIWOSC);
}

void loop() {
//  if(digitalRead(PIN_AKTYWUJACY) == HIGH){
    wyslijSms();
//  }
  while(Gsm.available()){
    Serial.write(Gsm.read());
  }
  while(Serial.available()){
    Gsm.write(Serial.read());
  }
  delay(500);
}

void wyslijSms(){
  Serial.write("\nRozpoczynam tworzenie wiadomości sms\n\n");
  
  String telefon = 
      WyswietlWiadomoscNaMonitorzePortuSzeregowegoIOczekujNaOdpowiedz("Wprowadz numer telefonu> ");
  Serial.println(">"+telefon+"\n");
  String wiadomosc = 
      WyswietlWiadomoscNaMonitorzePortuSzeregowegoIOczekujNaOdpowiedz("Wprowadz treść wiadomości> ");
  Serial.println(">"+wiadomosc+"\n");
  Gsm.println("AT+CMGF=1\r\n");
  delay(100);

  Gsm.write("AT+CMGS=\"+48513210196\"\r\n");

  delay(100);
  Gsm.println(wiadomosc);
  delay(100);
  Gsm.write((char)26);
  delay(100);
}

String WyswietlWiadomoscNaMonitorzePortuSzeregowegoIOczekujNaOdpowiedz(String wiadomosc){
  Serial.println(wiadomosc);
  czekajNaOdpowiedz();
  return Serial.readString();
}

void czekajNaOdpowiedz(){
  while(Serial.available() == 0){} 
}

void writeString(String stringData) {
  for (int i = 0; i < stringData.length(); i++)
  {
    Gsm.write(stringData[i]);
  }
}

