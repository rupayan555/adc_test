# ADC Test Report — Arduino Uno vs ESP32 vs ADS1115

This repository contains the complete **hardware setup, source codes, logged data, Excel analysis, and plots** for my ADC performance test project.

📌 **Full detailed report (Blog version):**  
➡️ https://rupayanhalder.wordpress.com/65-2/

---

## 📑 Table of Contents

- [1. Project Goal](#1-project-goal)
- [2. Tested ADC Devices](#2-tested-adc-devices)
- [3. Test Setup](#3-test-setup)
- [4. Data Collection Method](#4-data-collection-method)
- [5. Source Codes](#5-source-codes)
- [6. Logged Data Files](#6-logged-data-files)
- [7. Linearity Results](#7-linearity-results)
- [8. Noise Results](#8-noise-results)
- [9. Histogram Comparison](#9-histogram-comparison)
- [10. Standard Deviation Comparison](#10-standard-deviation-comparison)
- [11. Key Observations](#11-key-observations)
- [12. Full Report Link](#12-full-report-link)
- [13. Author](#13-author)

---

## 1. Project Goal

The goal of this project is to evaluate the **real-world ADC performance** of commonly used ADCs in embedded systems.

This test focuses on practical performance parameters such as:

✅ Linearity  
✅ Noise  
✅ Stability  
✅ Standard deviation (SD) comparison  
✅ Real voltage conversion accuracy  

---

## 2. Tested ADC Devices

This project compares three ADC sources:

### 🔹 Arduino Uno (Internal ADC)
- Resolution: **10-bit**
- ADC range: **0–5V**
- Output: **0–1023**

### 🔹 ESP32 (Internal ADC)
- Resolution: **12-bit (0–4095)**
- Known issue: **non-linear behavior**
- Requires calibration for accurate results

### 🔹 ADS1115 (External ADC)
- Resolution: **16-bit**
- High precision external ADC
- Excellent stability and noise performance

---

## 3. Test Setup

The following circuit was used to apply the same voltage to all ADCs simultaneously.

![Circuit Diagram](https://raw.githubusercontent.com/rupayan555/adc_test/main/1_test_setup/circuit_diagram.jpg)

📍 Setup file location:  
`1_test_setup/circuit_diagram.jpg`

---

## 4. Data Collection Method

### 🔹 Voltage Input
A controlled voltage source (potentiometer) was used to generate different input levels.

### 🔹 Sampling Strategy
Two main experiments were performed:

### ✅ Linearity Test
- **88 voltage points**
- **100 samples per point**
- Used for linearity curve and correction comparison

### ✅ Noise Test
- **5 fixed voltage points**
- **1000 samples per point**
- Used for noise analysis and standard deviation evaluation

---

## 5. Source Codes

All codes are stored in the folder:

📍 `2_codes/`

---

### ✅ Arduino Uno Code
📌 Path:  
`2_codes/adc_test_arduino_uno/adc_test_arduino_uno.ino`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_arduino_uno/adc_test_arduino_uno.ino

---

### ✅ ESP32 Code
📌 Path:  
`2_codes/adc_test_esp32/adc_test_esp32.ino`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_esp32/adc_test_esp32.ino

---

### ✅ Python Logger Script
📌 Path:  
`2_codes/python/adc_test_N_samples.py`

🔗 Direct link:  
https://github.com/rupayan555/adc_test/blob/main/2_codes/python/adc_test_N_samples.py

---

## 6. Logged Data Files

All raw and processed data are stored in:

📍 `3_data_collection_and_analysis/`

---

### 🔹 CSV Files (Raw Logs)
📍 Folder:  
`3_data_collection_and_analysis/data_collection_csv/`

Files:
- `adc_1000_samples_5_points_noise.csv`
- `adc_log_100_samples_88_points_linearity.csv`

🔗 Folder link:  
https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_collection_csv

---

### 🔹 Excel Analysis Files
📍 Folder:  
`3_data_collection_and_analysis/data_analysis_excel/`

Files:
- `adc_log_1000_5_noise_analysis.xlsx`
- `adc_log_100_88_linearity_analysis.xlsx`

🔗 Folder link:  
https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_analysis_excel

---

## 7. Linearity Results

📍 Plot folder:  
`4_Plots/linearity_plots/`

---

### 🔹 Linearity Comparison
This plot compares linearity across Arduino Uno, ESP32, and ADS1115.

![Linearity Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/linearity_comparison.png)

---

### 🔹 ESP32 Linearity Correction
This plot shows how ESP32 ADC improves after correction/calibration.

![ESP32 Linearity Correction](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/esp32_linearity_correction.png)

---

## 8. Noise Results

📍 Plot folder:  
`4_Plots/noise_plots/`

---

### 🔹 ADS1115 Noise
![ADS Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise.png)

---

### 🔹 Arduino Uno Noise
![Arduino Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise.png)

---

### 🔹 ESP32 Noise
![ESP32 Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise.png)

---

## 9. Histogram Comparison

Histograms show ADC sample distribution at fixed voltage points.

### 🔹 ADS1115 Histogram
![ADS Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise_histogram.png)

---

### 🔹 Arduino Uno Histogram
![Arduino Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise_histogram.png)

---

### 🔹 ESP32 Histogram
![ESP32 Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise_histogram.png)

---

## 10. Standard Deviation Comparison

This plot compares standard deviation across all devices.

![SD Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/sd_comparison.png)

---

## 11. Key Observations

From this practical ADC evaluation:

- **ADS1115 performed best** in both linearity and noise.
- **Arduino Uno ADC was stable**, but limited by 10-bit resolution.
- **ESP32 ADC showed high non-linearity**, and calibration is necessary for accuracy.
- ESP32 noise was also higher compared to ADS1115 and Arduino.

---

## 12. Full Report Link

📌 Blog version with full explanation:  
➡️ https://rupayanhalder.wordpress.com/65-2/

---

## 13. Author

**Rupayan Halder**  
Electrical Engineer | Automation & Microcontroller Enthusiast  

🌐 Blog: https://rupayanhalder.wordpress.com/  
📌 GitHub: https://github.com/rupayan555/
