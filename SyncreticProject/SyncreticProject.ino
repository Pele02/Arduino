#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

const int temperaturaPin = A0; 
Adafruit_LiquidCrystal lcd(0);
const int ledPin = 13;

void setup() {
  pinMode(temperaturaPin, INPUT);  // Setam pinul analogic A0 ca intrare pentru temperatura
  pinMode(ledPin, OUTPUT); // Setam pinul LED la iesire
  Serial.begin(9600);  // Se initializeaza comunicarea seriala
  lcd.begin(16, 2);
}

void loop() {
  int temperaturaRaw = analogRead(temperaturaPin);  // Citim valoarea analogica
  
  // Convertim valoarea citita, aproximata
  float temperaturaCelsius = temperaturaRaw * 0.489 - 50; 
  
  // Afisam temperatura pe ecranul LCD
  lcd.setCursor(0, 0); 
  lcd.print("Temp: "); 
  lcd.print(temperaturaCelsius);
  lcd.print(" C");

  // Verifica daca a fost primita o comanda
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    //Aprindem/Stingem Led-ul
    if (command == 'A') {
      digitalWrite(ledPin, HIGH);
    } else if (command == 'S') {
      digitalWrite(ledPin, LOW);  
    }
  }
  
  delay(1000);
}
