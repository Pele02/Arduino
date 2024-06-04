
#include <DHT11.h> // Library to use the sensor DHT11
#include <Adafruit_LiquidCrystal.h> //Library to use lcd
#include <EEPROM.h> 
#include <ZP4510.h>

DHT11 dht11(A0);
Adafruit_LiquidCrystal lcd(0);
const int ledPin = 13;
ZP4510 waterLevelSensor(12);

void setup() {
  pinMode(ledPin, OUTPUT); //Set the LED pin as output
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  //Variables
  int temperature = 0;
  int humidity = 0;
  int waterLevel = waterLevelSensor.WaterLevel();

  //Read data
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if (result == 0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\nHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    } else {
    //Print error message based on the error code.
    Serial.println(DHT11::getErrorString(result));
    }

  //Print temp on LCD
  lcd.setCursor(0, 0); 
  lcd.print("Temp: "); 
  lcd.print(temperature);
  lcd.print(" C");


 //Check the command
 if (Serial.available() > 0) {
    char command = Serial.read();

    //ON/OFF LED
    if (command == 'A') {
      digitalWrite(ledPin, HIGH);
    } else if (command == 'S') {
      digitalWrite(ledPin, LOW);
    } else if (command == 'M'){
      saveMessage();
    }
  }

  //Print the water level to the Serial Monitor
  if (waterLevel) {
    Serial.println("Flood");
  } else {
    Serial.println("Normal");
  }

  delay(2000);
}

void saveMessage() {
  String message = Serial.readStringUntil('\n'); //Read messages
  int messageLength = message.length(); 


  if (messageLength > EEPROM.length() - 1) {
    messageLength = EEPROM.length() - 1;
  }

  //write messages to EEPROM
  for (int i = 0; i < messageLength; i++) {
    EEPROM.write(i, message.charAt(i));
  }

  //
  EEPROM.write(messageLength, '\0');

  Serial.println("Message saved to EEPROM");
}