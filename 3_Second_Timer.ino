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
  Serial.begin(9600);
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
  if (timerRunning == false) {
    start_timer();
  }
  else if (timerRunning == true) {
    if (currentTime < finishTime) {
      timeLeft =  finishTime - currentTime;
      Serial.print("Tick Tock on the Clock. Time Left:");
      Serial.println(timeLeft);
    }
    else if (currentTime > finishTime) {
      unlock_hatbox();
      Switchval = 1;
    }
    }
  }

void reset_timer() {
  digitalWrite(light, HIGH); // turns the light off
  Serial.println("Timer has reset.");
  timerRunning = false;
  timeLeft = 0;
}

void unlock_hatbox() {
  if (Switchval == 1) {
    digitalWrite(hatbox, HIGH);
  }
  if (Switchval == 0) {
    Serial.print ("unlocked!");
    digitalWrite(hatbox, LOW); //unlocks the fucking door
    delay(3000);
  }
}

// TIMER CODE END

void loop() {
  if (digitalRead (wand) == LOW) {
    digitalWrite(light, LOW);
    if (digitalRead (shadow) == LOW) {
      tick_timer(); //TICK TOCK the timer. Also opens the hatbox once time elapsed.
      }
    else if (digitalRead(shadow)) == HIGH) {
      reset_timer();
    }
  }
  else { // If any of the above conditions are not met
    reset_timer();
    Switchval = 0;
  }
}
