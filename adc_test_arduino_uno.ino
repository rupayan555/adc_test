// Arduino Mega - UART0 ADC Slave
// Command: 'R'
// Response: "A<raw>;"

#define ADC_PIN A0
#define LED_PIN LED_BUILTIN

void setup() {

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);   // UART0
}

void loop() {
 
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == 'R') {
      int raw = analogRead(ADC_PIN);



      Serial.print('A');
      Serial.print(raw);
      Serial.print(';');
     

      digitalWrite(LED_PIN, HIGH);
      delay(5);
      digitalWrite(LED_PIN, LOW);
    }
  }

