// Arduino UNO - UART0 ADC Slave
// ----------------------------------------------------
// Purpose:
// This Arduino sketch acts as a UART-controlled ADC slave.
// A master device sends a command over Serial.
// When UNO receives 'R', it reads ADC from A0 and replies:
//
// Command:  'R'
// Response: "A<raw>;"
//
// Example: A512;
//
// This is used for ADC noise and linearity testing and comparison
// ----------------------------------------------------

#define ADC_PIN A0                // Analog input pin for ADC reading
#define LED_PIN LED_BUILTIN       // Built-in LED for activity indication

void setup() {

  pinMode(LED_PIN, OUTPUT);       // Configure LED pin as output
  Serial.begin(9600);             // UART0 over USB Serial (Baud = 9600)
}

void loop() {

  // Check if any serial data is available from master
  if (Serial.available()) {

    // Read one incoming byte (command)
    char cmd = Serial.read();

    // If command is 'R', perform ADC reading
    if (cmd == 'R') {

      // Read analog value from ADC pin (10-bit result: 0 to 1023)
      int raw = analogRead(ADC_PIN);

      // Send response in defined format:
      // A<raw>;
      Serial.print('A');
      Serial.print(raw);
      Serial.print(';');

      // Blink LED briefly to indicate successful response
      digitalWrite(LED_PIN, HIGH);
      delay(5);
      digitalWrite(LED_PIN, LOW);
    }
  }
}

