
const int buttonPin = 14;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

bool ledStatus = true;

void setupButton() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
}

void checkButton() {
  // read the state of the pushbutton value:
  if(digitalRead(buttonPin)==true){
    ledStatus = !ledStatus;
  } while(digitalRead(buttonPin)==true);
    digitalWrite(ledPin, ledStatus);
    delay(50);
  }
 
