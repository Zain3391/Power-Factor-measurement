// Pin connected to the first input signal
const int inputPin1 = 2;

// Pin connected to the second input signal
const int inputPin2 = 3;

// Variables to store the time of rising edges
volatile unsigned long startTime1 = 0;
volatile unsigned long startTime2 = 0;

// Variables to store the time difference
volatile long timeDifference = 0;

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Configure the input pins as INPUT
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);

  // Attach the interrupts to detect rising edges on the input pins
  attachInterrupt(digitalPinToInterrupt(inputPin1), risingEdge1, RISING);
  attachInterrupt(digitalPinToInterrupt(inputPin2), risingEdge2, RISING);
}

void loop() {
  // Calculate the power factor using the time difference
  if (timeDifference != 0) {
    float period = timeDifference * 0.000001; // Convert time difference from microseconds to seconds
    float frequency = 1.0 / period;
    float powerFactor = cos(2 * PI * frequency * timeDifference * 0.000001);

    // Determine if the power factor is leading or lagging
    String phaseIndicator;
    if (powerFactor > 0) {
      phaseIndicator = "Leading";
    } else if (powerFactor < 0) {
      phaseIndicator = "Lagging";
    } else {
      phaseIndicator = "Unity";
    }
  
    // Print the power factor and phase indicator to the serial console
    Serial.print("Power Factor: ");
    Serial.println(powerFactor);
    Serial.print("Phase: ");
    Serial.println(phaseIndicator);
  
    // Add a delay to observe the results
    delay(1000);
  
    // Reset the time difference for the next measurement
    timeDifference = 0;
  }
}

// Interrupt service routine for rising edge on input pin 1
void risingEdge1() {
  // Record the start time for input signal 1
  startTime1 = micros();
}

// Interrupt service routine for rising edge on input pin 2
void risingEdge2() {
  // Calculate the time difference between input signal 2 and input signal 1
  startTime2 = micros();
  timeDifference = startTime2 - startTime1;
}
