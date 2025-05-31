#define BLYNK_TEMPLATE_ID "TMPL65BIvBfmI"
#define BLYNK_TEMPLATE_NAME "SmartFarm"
#define BLYNK_AUTH_TOKEN "1NMrif_Qch78aupDglCMjuXSadexI7g7"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SoilPin A0 
#define relay D6      // Sesuaikan dengan pin ESP8266 (misal: D2, D4, dll)

const char* ssid = "Redmi Note 9";
const char* password = "qwertyui";



BLYNK_WRITE(V3) {
  int switchValue = param.asInt();
  if (switchValue == 1) {
    digitalWrite(relay, HIGH);
  } else {
    digitalWrite(relay, LOW);
  }
}

void setup() {
  Serial.begin(9600);


  pinMode(SoilPin, INPUT);
  pinMode(relay, OUTPUT);


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  Blynk.run();

  int soil = analogRead(SoilPin);
  int persen = map(SoilPin, 0 , 1023, 100, 0);



  if (soil < 500) {
    digitalWrite(relay, HIGH);
    Serial.println("mati");
  } else {
    digitalWrite(relay, LOW);
      Serial.println("hidup");
  }
  Serial.print("Kelembaban: ");
  Serial.print(soil);
  Serial.println("%");
  Blynk.virtualWrite(V0, soil);    

  delay(500);
}