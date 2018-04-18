#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

const byte PIN_KLAWIATURY_1 = A0,
           PIN_KLAWIATURY_2 = A1,
           PIN_KLAWIATURY_3 = A2,
           PIN_KLAWIATURY_4 = A3,
           PIN_KLAWIATURY_5 = A4,
           PIN_KLAWIATURY_6 = A5,
           PIN_KLAWIATURY_7 = 2,
           PIN_KLAWIATURY_8 = 3;
           
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'#','0','*', 'D'}
};
byte rowPins[ROWS] = {PIN_KLAWIATURY_1, PIN_KLAWIATURY_2, PIN_KLAWIATURY_3, PIN_KLAWIATURY_4};
byte colPins[COLS] = {PIN_KLAWIATURY_5, PIN_KLAWIATURY_6, PIN_KLAWIATURY_7, PIN_KLAWIATURY_8};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int PIN_TXD = 4, PIN_RXD = 5, PIN_AKTYWUJACY = 3, CZESTOTLIWOSC = 9600;
String telefon, wiadomosc;



SoftwareSerial Gsm(PIN_TXD, PIN_RXD);

void setup() {
  //pinMode(PIN_AKTYWUJACY, INPUT);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Gsm.begin(CZESTOTLIWOSC);
  Serial.begin(CZESTOTLIWOSC);
  wyswietlMenu();
}

void loop() {
//  if(digitalRead(PIN_AKTYWUJACY) == HIGH){
//    przygotujIWyslijSms();
//  }
//  while(Gsm.available()){
//    Serial.write(Gsm.read());
//  }
//  while(Serial.available()){
//    Gsm.write(Serial.read());
//  }
//  delay(100);
  

  char jakisKlawisz = keypad.getKey();

//delay(500);
  if(jakisKlawisz){
   Serial.println(jakisKlawisz); 
  
   switch(jakisKlawisz){
      case '0': break;
      case '1': przygotujIWyslijSms(); przygotujIWyslijSms(); break;
      case '2': break;
      case '3': break;
      case '4': break;
      case '5': break;
      case '6': break;
      case '7': break;
      case '8': break;
      case '9': break;
      case 'A': break;
      case 'B': break;
      case 'C': break;
      case 'D': break;
      case '*': break;
      case '#': break;
      default: break;
    }
  }
}

void wyswietlMenu(){
    Serial.println("Bramka SMS  - menu\n");
    Serial.println("Klawisz 1 - Napisz SMS-a");
    Serial.println("Klawisz 2 - Zadzwoń");
    Serial.println("Klawisz 3 - Wykonaj żądanie HTTP");
    Serial.println("Klawisz 4 - Sprawdz stan konta");
    Serial.println("Klawisz 5 - Wiadomości SMS");
    Serial.println("Klawisz 6 - Lista kontaków");
    Serial.println("Klawisz 7 - Menu serwisowe");
    Serial.println("Klawisz 8 - Brak przypisania");
    Serial.println("Klawisz 9 - Brak przypisania");
    Serial.println("Klawisz A - Brak przypisania");
    Serial.println("Klawisz B - Brak przypisania");
    Serial.println("Klawisz C - Brak przypisania");
    Serial.println("Klawisz D - Brak przypisania");
    Serial.println("Klawisz 0 - Wyjscie\n");
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

