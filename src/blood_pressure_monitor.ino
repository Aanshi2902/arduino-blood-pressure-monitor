const int dataPin = 2;  // DOUT
const int clockPin = 3; // SCK

// Calibration (adjusted scale factor for 111 mmHg = measured 157 mmHg)
float scaleFactor = 0.0000252; // corrected
float offset = 0;
const int samples = 20;       // averaging for stability

// Moving average filter
float filteredPressure = 0;
float alpha = 0.2; // smoothing factor (0.1–0.3)

void setup() {
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Continuous Blood Pressure Display (Fast Updates) ===");
  Serial.println("Keep cuff deflated for calibration...");
  delay(2000);

  offset = averageRaw();  // Auto-zero calibration
  Serial.print("Calibration complete. Baseline raw = ");
  Serial.println(offset);
  Serial.println("Now inflate cuff to see stable pressure readings...");
  delay(500);
}

long readHX710B() {
  unsigned long result = 0;
  while (digitalRead(dataPin) == HIGH);  // Wait for data ready

  for (int i = 0; i < 24; i++) {
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(0.1); // reduced from 0.2 for faster reading
    result = (result << 1) | digitalRead(dataPin);
    digitalWrite(clockPin, LOW);
    delayMicroseconds(0.1); // reduced from 0.2
  }

  digitalWrite(clockPin, HIGH);
  delayMicroseconds(0.1);
  digitalWrite(clockPin, LOW);

  if (result & 0x800000) result |= 0xFF000000; // sign extension
  return (long)result;
}

float averageRaw() {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += readHX710B();
    delay(10); // reduced from 20ms for faster averaging
  }
  return (float)sum / samples;
}

void loop() {
  float rawAvg = averageRaw();
  float pressure_mmHg = (rawAvg - offset) * scaleFactor;

  // Clamp realistic range
  if (pressure_mmHg < 0) pressure_mmHg = 0;
  if (pressure_mmHg > 200) pressure_mmHg = 200;

  // Apply smoothing filter
  filteredPressure = alpha * pressure_mmHg + (1 - alpha) * filteredPressure;

  Serial.print("Pressure: ");
  Serial.print(filteredPressure, 1);
  Serial.println(" mmHg");

  delay(100);  // reduced from 200ms → faster updates
}
