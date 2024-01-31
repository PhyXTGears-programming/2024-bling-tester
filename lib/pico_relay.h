
#define RELAY_PIN 2 // 

void setupRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Set high to supply power to LED string
}

void ledStringOn() {
  digitalWrite(RELAY_PIN, HIGH); // Set high to supply power to LED string
}

void ledStringOff() {
  digitalWrite(RELAY_PIN, LOW); // Set low remove power to LED string
}

