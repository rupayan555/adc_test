
---

## 🔧 Test Setup

The following circuit was used for simultaneous voltage measurement by Arduino Uno, ESP32, and ADS1115.

![Circuit Diagram](https://raw.githubusercontent.com/rupayan555/adc_test/main/1_test_setup/circuit_diagram.jpg)

---

## 🧠 Experiment Method

### 🔹 Input Voltage
A controlled input voltage was applied across the ADCs.

### 🔹 Data Collection
For each voltage point:

- Arduino Uno ADC value was collected
- ESP32 ADC value was collected
- ADS1115 ADC value was collected  
- All values were logged into CSV using Python

---

## 💻 Source Codes

### ✅ Arduino Uno Code
📍 Path:  
`2_codes/adc_test_arduino_uno/adc_test_arduino_uno.ino`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_arduino_uno/adc_test_arduino_uno.ino

---

### ✅ ESP32 Code
📍 Path:  
`2_codes/adc_test_esp32/adc_test_esp32.ino`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_esp32/adc_test_esp32.ino

---

### ✅ Python Logger Script
📍 Path:  
`2_codes/python/adc_test_N_samples.py`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/python/adc_test_N_samples.py

---

## 📊 Data Collection Files

### 🔹 CSV Files (Raw Logs)

📍 Folder:  
`3_data_collection_and_analysis/data_collection_csv/`

- `adc_1000_samples_5_points_noise.csv`  
- `adc_log_100_samples_88_points_linearity.csv`

🔗 Folder link:  
https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_collection_csv

---

### 🔹 Excel Analysis Files

📍 Folder:  
`3_data_collection_and_analysis/data_analysis_excel/`

- `adc_log_1000_5_noise_analysis.xlsx`
- `adc_log_100_88_linearity_analysis.xlsx`

🔗 Folder link:  
https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_analysis_excel

---

## 📈 Results — Linearity

📍 Folder:  
`4_Plots/linearity_plots/`

### 🔹 Linearity Comparison Plot
![Linearity Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/linearity_comparison.png)

### 🔹 ESP32 Linearity Correction Plot
![ESP32 Linearity Correction](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/esp32_linearity_correction.png)

---

## 📉 Results — Noise Analysis

📍 Folder:  
`4_Plots/noise_plots/`

### 🔹 ADS1115 Noise
![ADS Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise.png)

### 🔹 Arduino Uno Noise
![Arduino Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise.png)

### 🔹 ESP32 Noise
![ESP32 Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise.png)

---

## 📊 Histogram Comparison

### 🔹 ADS1115 Histogram
![ADS Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise_histogram.png)

### 🔹 Arduino Histogram
![Arduino Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise_histogram.png)

### 🔹 ESP32 Histogram
![ESP32 Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise_histogram.png)

---

## 📌 Standard Deviation Comparison

![SD Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/sd_comparison.png)

---

## ✅ Key Observations

From this practical experiment:

- **ADS1115 performed best** in both linearity and noise.
- **Arduino Uno ADC was stable** but limited due to 10-bit resolution.
- **ESP32 ADC showed high non-linearity**, and calibration is necessary for accuracy.

---

## 📎 Full Report (Blog)

For full explanation, discussion, and methodology:

➡️ https://rupayanhalder.wordpress.com/65-2/

---

## 👤 Author

**Rupayan Halder**  
Electrical Engineer | Automation & Microcontroller Enthusiast  
📌 Blog: https://rupayanhalder.wordpress.com/
