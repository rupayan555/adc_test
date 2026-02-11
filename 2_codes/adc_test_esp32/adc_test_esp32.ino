// ----------------------------------------------------
// ESP32 ADC Test Master
// ----------------------------------------------------
// Reads ADC values from 3 sources:
// 1) Arduino uno ADC via UART (Slave protocol: send 'R' → receive "A<raw>;")
// 2) ESP32 internal ADC1 (GPIO34)
// 3) ADS1115 external ADC via I2C
//
// Output to PC (Serial Monitor):
// A<uno_raw>; E<esp_raw>; D<ads_raw>;
//
// Example:
// A512; E2033; D16000;
//
// WiFi + Bluetooth are disabled to reduce ADC noise.
// ----------------------------------------------------


#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFi.h>

// -------- ESP32 ADC Pin --------
#define ESP_ADC_PIN 34        // ADC1 channel (WiFi safe pin)
#define LED_PIN     2         // ESP32 onboard LED (usually GPIO2)


// -------- UART2 Pins (ESP32 ↔ Arduino uno) --------
#define UART_RX 16
#define UART_TX 17


// Create UART2 serial object for uno communication
HardwareSerial unoSerial(2);

// Create ADS1115 object
Adafruit_ADS1115 ads;


// ----------------------------------------------------
// Function: readunoADC()
// ----------------------------------------------------
// Sends command 'R' to Arduino uno over UART.
// uno responds with: A<raw>;
// Example: A1023;
//
// Returns:
//   raw ADC value (0–1023) if valid
//   -1 if timeout / invalid response
// ----------------------------------------------------
int readunoADC() {

  // Request ADC reading from uno
  unoSerial.write('R');

  String data = "";
  unsigned long t0 = millis();

  // Wait up to 25ms for response
  while (millis() - t0 < 25) {

    if (unoSerial.available()) {
      char c = unoSerial.read();

      // End of packet detected
      if (c == ';') break;

      // Store incoming characters
      data += c;
    }
  }

  // Expected response format: A1023
  if (data.length() > 1 && data[0] == 'A') {
    return data.substring(1).toInt();
  }

  // Invalid / timeout
  return -1;
}


// ----------------------------------------------------
// Setup
// ----------------------------------------------------
void setup() {

  pinMode(LED_PIN, OUTPUT);

  // PC Serial Monitor
  Serial.begin(115200);

  // UART2 for Arduino uno communication
  unoSerial.begin(9600, SERIAL_8N1, UART_RX, UART_TX);

  // I2C for ADS1115 (ESP32 default pins: SDA=21, SCL=22)
  Wire.begin(21, 22);

  Serial.println("ESP32 ADC TEST START");

  // Configure ESP32 ADC resolution (12-bit)
  analogReadResolution(12);

  // Set ADC attenuation to allow higher voltage range (~3.3V)
  analogSetPinAttenuation(ESP_ADC_PIN, ADC_11db);

  Serial.println("ESP32 ADC1 OK");


  // ADS1115 gain configuration
  // GAIN_ONE = +/- 4.096V range (1 bit = 0.125mV)
  ads.setGain(GAIN_ONE);

  // Initialize ADS1115
  if (!ads.begin()) {
    Serial.println("ADS1115 NOT FOUND");
    while (1);  // Stop here if ADS not detected
  }
  Serial.println("ADS1115 OK");


  // Disable WiFi + Bluetooth to reduce ADC noise
  WiFi.mode(WIFI_OFF);
  btStop();

  Serial.println("SYSTEM READY");
}


// ----------------------------------------------------
// Main Loop
// ----------------------------------------------------
void loop() {

  // -------- Arduino uno ADC (via UART) --------
  int uno_raw = readunoADC();
  delay(20);

  // -------- ESP32 ADC (GPIO34) --------
  int esp_raw = analogRead(ESP_ADC_PIN);
  delay(20);

  // -------- ADS1115 ADC (Channel 0) --------
  int16_t ads_raw = ads.readADC_SingleEnded(0);
  delay(20);

  // -------- Send raw dataset to PC --------
  // Format:
  // A<uno_raw>; E<esp_raw>; D<ads_raw>;
  Serial.print("A");
  Serial.print(uno_raw);
  Serial.print("; ");

  Serial.print("E");
  Serial.print(esp_raw);
  Serial.print("; ");

  Serial.print("D");
  Serial.print(ads_raw);
  Serial.println("; ");



  // -------- LED flash to show activity --------
  digitalWrite(LED_PIN, HIGH);
  delay(5);
  digitalWrite(LED_PIN, LOW);

  delay(20);
}
