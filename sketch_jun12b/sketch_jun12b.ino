volatile unsigned long timerValue1;
volatile unsigned long timerValue2;
volatile bool wave1RisingEdge = false;
volatile bool wave2RisingEdge = false;

void setup() {
  pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(Pin1), handleWave1Interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(Pin2), handleWave2Interrupt, RISING);
}

void loop() {
  if (wave1RisingEdge && wave2RisingEdge) {
    // Calculate the time difference between the rising edges
    unsigned long timeDifference = timerValue2 - timerValue1;
    // Print the result or perform any further processing
    Serial.print("Time Difference: ");
    Serial.print(timeDifference);
    Serial.println(" microseconds");

    wave1RisingEdge = false;
    wave2RisingEdge = false;
  }
}

void handleWave1Interrupt() {
  timerValue1 = micros();
  wave1RisingEdge = true;
}

void handleWave2Interrupt() {
  timerValue2 = micros();
  wave2RisingEdge = true;
}
