# ADC Linearity & Noise Test — Arduino Uno vs ESP32 vs ADS1115

This repository contains the complete **hardware setup, source codes, logged data, Excel analysis, and plots** for my practical ADC performance evaluation project, focusing on **linearity and noise testing**.


📌 **Full detailed report (Blog version):**  
➡️ https://rupayanhalder.wordpress.com/65-2/

---

## 📑 Table of Contents

- [1. Project Goal & Tested ADC Devices](#1-project-goal--tested-adc-devices)
- [2. Test Setup](#2-test-setup)
- [3. Data Collection Method](#3-data-collection-method)
- [4. Source Codes](#4-source-codes)
- [5. Logged Data Files](#5-logged-data-files)
- [6. Linearity Results](#6-linearity-results)
- [7. Noise Results (Noise + Histogram)](#7-noise-results-noise--histogram)
- [8. Standard Deviation Comparison](#8-standard-deviation-comparison)
- [9. Results Summary Table](#9-results-summary-table)
- [10. Key Observations](#10-key-observations)
- [11. Full Report Link](#11-full-report-link)
- [12. Author](#12-author)

---

## 1. Project Goal & Tested ADC Devices

The goal of this project is to evaluate **real-world ADC performance**, mainly focusing on **linearity and noise**, for three popular ADC sources:

- **Arduino Uno** — Internal **10-bit** ADC (0–1023)
- **ESP32** — Internal **12-bit** ADC (0–4095)
- **ADS1115** — External **16-bit** I²C ADC

---

## 2. Test Setup

The following circuit was used to apply the same voltage to all ADCs simultaneously.  
This ensures that the comparison is fair and each ADC measures the identical input signal.

![Circuit Diagram](https://raw.githubusercontent.com/rupayan555/adc_test/main/1_test_setup/circuit_diagram.jpg)

📍 Setup file location:  
`1_test_setup/circuit_diagram.jpg`

---

## 3. Data Collection Method

A controlled voltage source (potentiometer) was used to generate different voltage levels.  
For each test point, all ADCs were sampled and the results were logged for analysis.

Two main experiments were performed:

### ✅ Linearity Test
- **88 voltage points**
- **100 samples per point**
- Used for linearity curve plotting and correction comparison.

### ✅ Noise Test
- **5 fixed voltage points**
- **1000 samples per point**
- Used for noise, histogram, and standard deviation evaluation.

---

## 4. Source Codes

All source codes are available in 📍 `2_codes/`.

- **Arduino Uno**: [`adc_test_arduino_uno.ino`](https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_arduino_uno/adc_test_arduino_uno.ino)  
- **ESP32**: [`adc_test_esp32.ino`](https://github.com/rupayan555/adc_test/blob/main/2_codes/adc_test_esp32/adc_test_esp32.ino)  
- **Python Logger**: [`adc_test_N_samples.py`](https://github.com/rupayan555/adc_test/blob/main/2_codes/python/adc_test_N_samples.py)  

---

## 5. Logged Data Files

All raw logs and analysis files are included in 📍 `3_data_collection_and_analysis/` for full verification and plot reproduction.

- **CSV logs**: [`data_collection_csv/`](https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_collection_csv)  
  - `adc_1000_samples_5_points_noise.csv`  
  - `adc_log_100_samples_88_points_linearity.csv`

- **Excel analysis**: [`data_analysis_excel/`](https://github.com/rupayan555/adc_test/tree/main/3_data_collection_and_analysis/data_analysis_excel)  
  - `adc_log_1000_5_noise_analysis.xlsx`  
  - `adc_log_100_88_linearity_analysis.xlsx`


---

## 6. Linearity Results

Linearity plots show how closely each ADC follows the ideal voltage-to-code relationship.

📍 Folder: `4_Plots/linearity_plots/`

### 🔹 Linearity Comparison

After plotting the results, **Arduino Uno and ADS1115 appear almost perfectly linear** across the full range.  
However, the **ESP32 ADC is clearly non-linear** over the full range. It shows relatively better linearity only within **~0.15V to 2.5V**, but with an offset.  
Also, ESP32 shows a **dead zone below ~0.13V** and it **tops out around ~3.18V**.

![Linearity Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/linearity_comparison.png)

---
### 🔹 ESP32 Linearity Correction (2-Point Calibration)

The ESP32 ADC data was calibrated using a practical **2-point calibration** method based on **0.501V** and **2.000V**.  
This approach is simple and realistic for real-world projects. After calibration, the ESP32 result improves significantly, and in my opinion it becomes usable within the range of **~0.15V to 2.5V**.

![ESP32 Linearity Correction](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/linearity_plots/esp32_linearity_correction.png)

---

## 7. Noise Results (Noise + Histogram)

Noise plots show how much the ADC output fluctuates when the input voltage is fixed.  
Histograms help visualize the distribution of ADC values and stability.

📍 Plot folder:  
`4_Plots/noise_plots/`

---

### 🔹 ESP32 Noise + Histogram

ESP32 showed the highest fluctuation and wider distribution compared to the other ADCs.  
This confirms the need for filtering and calibration in real applications.

![ESP32 Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise.png)

![ESP32 Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/esp32_noise_histogram.png)

---

### 🔹 Arduino Uno Noise + Histogram

Arduino Uno ADC was more stable than ESP32 but limited by 10-bit resolution.  
The distribution shows quantization steps, which is expected for a 10-bit ADC.

![Arduino Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise.png)

![Arduino Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/arduino_noise_histogram.png)

---

### 🔹 ADS1115 Noise + Histogram

ADS1115 showed the best stability and the lowest noise in the experiment.  
This makes it the best option for precision voltage and sensor measurement.

![ADS Noise](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise.png)

![ADS Histogram](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/ads_noise_histogram.png)

---

## 8. Standard Deviation Comparison

Standard deviation (SD) gives a numeric comparison of noise level.  
Lower SD means better stability and more repeatable measurement.

![SD Comparison](https://raw.githubusercontent.com/rupayan555/adc_test/main/4_Plots/noise_plots/sd_comparison.png)

---

## 9. Results Summary Table

This table summarizes the practical findings from this experiment.

> ⚠️ Note: Exact numerical SD/error values depend on voltage point and sampling count.  
> The comparison below is based on the overall trend from the collected plots and analysis.

| ADC Device | Type | Resolution | Linearity (Practical) | Noise (Practical) | Best Use Case |
|-----------|------|------------|------------------------|-------------------|--------------|
| **Arduino Uno** | Internal ADC | 10-bit | Good (mostly linear) | Medium | General sensing, basic voltage monitoring |
| **ESP32** | Internal ADC | 12-bit | Poor without correction | High | IoT monitoring where calibration is acceptable |
| **ADS1115** | External ADC | 16-bit | Excellent | Very Low | Precision sensing, data logging, stable measurement |

---

## 10. Key Observations

From this practical ADC evaluation:

- **ADS1115 performed best** in both linearity and noise.
- **Arduino Uno ADC was stable**, but limited due to 10-bit resolution.
- **ESP32 ADC showed high non-linearity**, and calibration is necessary for accuracy.
- ESP32 noise was also higher compared to ADS1115 and Arduino.

---

## 11. Full Report Link

📌 Full detailed report with discussion and methodology:  
➡️ https://rupayanhalder.wordpress.com/65-2/

---

## 12. Author

**Rupayan Halder**  
Electrical Engineer | Automation & Microcontroller Enthusiast  

🌐 Blog: https://rupayanhalder.wordpress.com/  
📌 GitHub: https://github.com/rupayan555/
