const byte buttonPin = 7;
int buttonState = LOW;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

//  TIMER CODE START

const unsigned long timerLength = 3000; // How long we want the timer to run. 3000 ms.
unsigned long finishTime; // When the timer should finish. from millis() + timerLength.
unsigned long timeLeft = 0; // The current number of ticks left on the clock.
bool timerRunning = false;

void start_timer() {
  finishTime = millis() + timerLength;
  Serial.print("Timer Started. Time left:");
  Serial.println(timerLength);
  timerRunning=true;
}

void tick_timer() {
  unsigned long int currentTime = millis();
  if (timerRunning == false) {
    start_timer();
  }
  else if (timerRunning == true) {
    if (currentTime < finishTime) {
        timeLeft =  finishTime - currentTime;
        Serial.print("Time ticked. Time Left:");
        Serial.println(timeLeft);
    }
    else if (currentTime > finishTime) {
      timerRunning = false;
      Serial.print ("unlocked!");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(3000);
    }
}
}

void reset_timer() {
  //digitalWrite(light, HIGH); // turns the light off
  Serial.println("Timer has reset.");
  timerRunning = false;
}

// TIMER CODE END

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.print("Detecting HIGH");
    tick_timer();
    }
  else if (buttonState == LOW) {
    Serial.print("Detected LOW");
    reset_timer();
    digitalWrite(LED_BUILTIN, LOW);
  }
  }
