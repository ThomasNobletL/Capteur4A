
 
// constants won&#039;t change. They&#039;re used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int compteur_filtre; //compteur filtr&eacute;
int compteur_non_filtre; //compteur non filtr&eacute;

// the following variables are long&#039;s because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin (9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you&#039;ve waited
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
     if (reading == 1)
     {
       compteur_non_filtre = compteur_non_filtre + 1;
     }
  }
 
  if ((millis() - lastDebounceTime)> debounceDelay)
  {
    // whatever the reading is at, it&#039;s been there for longer
    // than the debounce delay, so take it as the actual current state:
    
     if ((reading == 1) && (reading != buttonState))
     {
       compteur_filtre = compteur_filtre + 1;
     } 
     buttonState = reading;
  }
 
  // set the LED using the state of the button:
  digitalWrite(ledPin, buttonState);

  // save the reading.  Next time through the loop,
  // it&#039;ll be the lastButtonState:
  lastButtonState = reading;
  
  Serial.print("Compteurs");
  Serial.print(compteur_non_filtre);
  Serial.print(",");
  Serial.println(compteur_filtre);
  
}