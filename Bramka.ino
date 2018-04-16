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
    przygotujIWyslijSms();
//  }
  while(Gsm.available()){
    Serial.write(Gsm.read());
  }
  while(Serial.available()){
    Gsm.write(Serial.read());
  }
  delay(100);
}

void przygotujIWyslijSms(){
  Serial.write("\nRozpoczynam tworzenie wiadomości sms\n\n");
  
  String telefon = 
      WyswietlWiadomoscNaMonitorzePortuSzeregowegoIOczekujNaOdpowiedz("Wprowadz numer telefonu> ");
  Serial.println("telefon>"+telefon+"\n");
  String wiadomosc = 
      WyswietlWiadomoscNaMonitorzePortuSzeregowegoIOczekujNaOdpowiedz("Wprowadz treść wiadomości> ");
  Serial.println("wiadomosc>"+wiadomosc+"\n");

  wiadomosc.trim();
  telefon.trim();
  
  Gsm.print("AT+CMGF=1\r\n");
  delay(100);
  Gsm.print("AT+CMGS=\""+telefon+"\"\r\n");
  delay(100);
  Gsm.print(wiadomosc);
  delay(100);
  Gsm.print((char)26);
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

