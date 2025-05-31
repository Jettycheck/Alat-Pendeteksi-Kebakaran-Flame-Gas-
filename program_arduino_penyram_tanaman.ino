int soil_sensor = 0;

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  soil_sensor = analogRead(A0);
  Serial.println(soil_sensor);
  if (soil_sensor < 40) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
  delay(10);
}

