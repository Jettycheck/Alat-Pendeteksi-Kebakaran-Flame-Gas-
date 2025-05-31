#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LDR_PIN A0         
#define LEDM_PIN 6         
#define LEDB_PIN 7         
#define BUZZER_PIN 4       
#define DHT_PIN 8         
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

// Threshold
const int ldrThreshold = 500;      // Ambang kegelapan
const float tempThreshold = 32.0;  // Suhu maksimal (°C)
const float humThreshold = 50.0;   // Kelembaban ambang (%)

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Farming");
  lcd.setCursor(0, 1);
  lcd.print("UAP EMBEDDED SYSTEMS");
  delay(1000);
  for (int i = 0; i < 22; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
  lcd.clear();

  pinMode(LEDM_PIN, OUTPUT);
  pinMode(LEDB_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Tampilkan nilai ke Serial Monitor
  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  lcd.setCursor(0, 0);
  lcd.print("LDR: ");
  lcd.print(ldrValue);

  lcd.setCursor(0, 1);
   lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");
  lcd.print("H:");
  lcd.print(humidity);
  lcd.println("%");

  // Cek kondisi cahaya
  if (ldrValue < ldrThreshold) {
    digitalWrite(LEDM_PIN, HIGH); // Nyala kalau gelap
  } else {
    digitalWrite(LEDM_PIN, LOW);
  }

  // Cek kelembaban
  if (!isnan(humidity)) {
    if (humidity > humThreshold) {
      digitalWrite(LEDB_PIN, HIGH); // Nyala kalau kelembaban tinggi
    } else {
      digitalWrite(LEDB_PIN, LOW);
    }
  }

  // Cek suhu
  if (!isnan(temperature)) {
    if (temperature > tempThreshold) {
      tone(BUZZER_PIN, 1000);  // Bunyikan buzzer
    } else if (temperature <= tempThreshold) {
      noTone(BUZZER_PIN);      // Matikan buzzer
    }
  }
  delay(2000); // Delay 1 detik
}
