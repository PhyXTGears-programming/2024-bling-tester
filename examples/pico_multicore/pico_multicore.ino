git
bool core0_status = false;

// Rnning on core0
void setup() {
  Serial.begin(115200);
  delay(5000);
}

void loop() {
  if (core0_status == false)
    Serial.printf("C0: Status is true\n");
  else
    Serial.printf("C0: Status is false\n");
  delay(2000);
}

// Running on core1
void setup1() {
}

void loop1() {
  core0_status = !core0_status;
  Serial.printf("C1: changing Core0 status\n");
  delay(5050);
}
