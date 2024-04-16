
#include <DHT11.h> //Librarie pentru a putea fi folosit senzorul DHT11
#include <Adafruit_LiquidCrystal.h> //Librarie pentru lcd

DHT11 dht11(A0);
Adafruit_LiquidCrystal lcd(0);
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT); // Setam pinul LED la iesire
  Serial.begin(9600);  // Se initializeaza comunicarea seriala
  lcd.begin(16, 2);
}

void loop() {
  //Variabile
  int temperature = 0;
  int humidity = 0;

  //Citire date senzor
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" °C\t Umiditate: ");
    Serial.print(humidity);
    Serial.println(" %");
    } else {
    // Print error message based on the error code.
    Serial.println(DHT11::getErrorString(result));
    }

  // Afisam temperatura pe ecranul LCD
  lcd.setCursor(0, 0); 
  lcd.print("Temp: "); 
  lcd.print(temperature);
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
