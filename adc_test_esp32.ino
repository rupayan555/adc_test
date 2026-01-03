#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <WiFi.h>


#define ESP_ADC_PIN 34        // ADC1 (WiFi safe)
#define LED_PIN     2

#define UART_RX 16
#define UART_TX 17

HardwareSerial MegaSerial(2);
Adafruit_ADS1115 ads;

/* ---------- Read Arduino Mega ---------- */
int readMegaADC() {
  MegaSerial.write('R');

  String data = "";
  unsigned long t0 = millis();

  while (millis() - t0 < 25) {
    if (MegaSerial.available()) {
      char c = MegaSerial.read();
      if (c == ';') break;
      data += c;
    }
  }

  // Expected: A1023
  if (data.length() > 1 && data[0] == 'A') {
    return data.substring(1).toInt();
  }

  return -1;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  MegaSerial.begin(9600, SERIAL_8N1, UART_RX, UART_TX);
  Wire.begin(21, 22);

  Serial.println("ESP32 ADC TEST START");

  analogReadResolution(12);
  analogSetPinAttenuation(ESP_ADC_PIN, ADC_11db);
  Serial.println("ESP32 ADC1 OK");

  ads.setGain(GAIN_ONE);
  if (!ads.begin()) {
    Serial.println("ADS1115 NOT FOUND");
    while (1);
  }
  Serial.println("ADS1115 OK");

  /* ---- Disable WiFi & Bluetooth (SAFE WAY) ---- */
  WiFi.mode(WIFI_OFF);
  btStop();

  Serial.println("SYSTEM READY");
}


void loop() {

  /* -------- Arduino Mega -------- */
  int mega_raw = readMegaADC();
  delay(20);

  /* -------- ESP32 ADC -------- */
  int esp_raw = analogRead(ESP_ADC_PIN);
  delay(20);

  /* -------- ADS1115 -------- */
  int16_t ads_raw = ads.readADC_SingleEnded(0);
  delay(20);

  /* -------- Send dataset to PC -------- */
  Serial.print("A");
  Serial.print(mega_raw);
  Serial.print("; ");

  Serial.print("E");
  Serial.print(esp_raw);
  Serial.print("; ");

  Serial.print("D");
  Serial.print(ads_raw);
  Serial.println("; ");



  /*
  // -------- Calculated Voltages -------- 
  float mega_v = mega_raw * 5.0 / 1023.0;  // Mega Vref = 5V
  float esp_v  = esp_raw  * 3.3 / 4095.0;  // ESP32 ADC1 Vref ~3.3V
  float ads_v = ads_raw * 4.096 / 32768.0;


  // -------- Send Voltage Line -------- 
  Serial.print("X");
  Serial.print(mega_v, 3);
  Serial.print("; Y");
  Serial.print(esp_v, 3);
  Serial.print("; Z");
  Serial.print(ads_v, 3);
  Serial.println(";");

*/
  /* -------- LED flash -------- */
  digitalWrite(LED_PIN, HIGH);
  delay(5);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
