const byte wand = 2;
const byte shadow = 5;
const byte light = 7;
const byte hatbox = 6;

void setup() {
  pinMode(wand, INPUT_PULLUP);
  pinMode(shadow, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  pinMode(hatbox, OUTPUT);
  digitalWrite (light, HIGH);
  digitalWrite (hatbox, HIGH);
}

//  TIMER CODE START

const unsigned long timerLength = 3000; // How long we want the timer to run. 3000 ms.
unsigned long finishTime; // When the timer should finish. from millis() + timerLength.
unsigned long timeLeft = 0; // The current number of ticks on the clock.
bool timerRunning = true; // y/n if the clock is ticking.


void start_timer() {
  finishTime = millis() + timerLength;
  Serial.print("Timer Started. Time left:");
  Serial.println(timerLength);
  timerRunning=true;
}

void tick_timer() {
  unsigned long int currentTime = millis();
  if (timer_running == false) {
    start_timer();
  }
  else if (timer_running == true) {
    if (currentTime < finishTime) {
      timeLeft =  finishTime - currentTime;
      Serial.print("Tick Tock on the Clock. Time Left:");
      Serial.println(timeLeft);
    }
    else if (currentTime > finishTime) {
      timerRunning = false;
      Serial.print ("unlocked!");
      digitalWrite(hatbox, LOW);
      delay(3000);
    }
    }
  }

void reset_timer() {
  digitalWrite(light, HIGH); // turns the light off
  Serial.println("Timer has reset.");
  timerRunning = false;
}

// TIMER CODE END


void loop() {
  if ((digitalRead (wand) == LOW)) {
    digitalWrite(light, LOW);
  }
  if ((digitalRead (shadow) == LOW) && (digitalRead (light) == LOW) && Switchval == (0)) {
    tick_timer(); //TICK TOCK the timer. Also opens the hatbox once time elapsed.
    }
  else { // If any of the above conditions are not met
    reset_timer();
    digitalWrite(hatbox, HIGH);
  }
}
