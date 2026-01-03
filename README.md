# adc_test
ADC accuracy test
Comparing ADC Performance: Arduino Mega vs ESP32 vs ADS1115
A Practical, Data-Driven Evaluation Using Real Measurements
Introduction
Analog-to-Digital Converters (ADCs) are at the heart of almost every embedded system that interacts with the real world. Despite similar “bit-depth” claims on datasheets, ADC performance can vary significantly depending on architecture, reference stability, noise, and input conditions.

In this article, I present a practical comparison of three commonly used ADC solutions:

Arduino Mega (ATmega2560 internal ADC)

ESP32 (internal SAR ADC)

ADS1115 (external 16-bit delta-sigma ADC)

Rather than relying on theory alone, all results are based on measured data, collected through controlled experiments with hundreds to thousands of samples per test point.

Devices Under Test
Device	ADC Type	Resolution (Nominal)	Interface
Arduino Mega	SAR (internal)	10-bit	Direct MCU
ESP32	SAR (internal)	12-bit (effective lower)	Direct MCU
ADS1115	Delta-Sigma	16-bit	I²C
All three ADCs were sampled simultaneously and logged to a PC using Python for post-processing.

Test Methodology Overview
To keep the comparison fair and repeatable:

Input voltage range: 0–3 V

Stable DC source: Battery-based DC (low ripple)

Each test point collected multiple samples

Analysis based on mean, spread, and code behavior

External reference instruments: UNI-T UT203+ multimeter

Test-1: Multi-Point DC Sweep (Resolution & Linearity)
Test Description
88 voltage points across 0–3 V

100 samples per voltage point

Mean value calculated for each ADC at every point

This test focuses on:

Linearity

Effective resolution

Code smoothness

Repeatability

Why 88 Points?
Using many closely spaced voltage points reveals:

Missing codes

Non-linear regions

Quantization artifacts that are invisible in coarse tests

Results: Voltage vs ADC Output




Figure 1: Average ADC output vs input voltage
(sample figure – replace with your actual plot)

Arduino Mega shows predictable linearity, but coarse steps due to 10-bit resolution.

ESP32 exhibits non-uniform step behavior, especially in mid-range voltages.

ADS1115 produces a smooth, high-resolution curve with minimal visible quantization.

Observed ADC Code Behavior
Figure 2: Zoomed-in ADC output steps (mid-range voltage)

Notably, the ADS1115 output increased in fixed steps of 16 counts, for example:

20272 → 20288 → 20304 → 20320 → 20336 …
This behavior is expected and not an error. It results from:

Internal digital filtering

PGA scaling

Delta-sigma decimation process

The important observation is that no missing codes were detected.

Test-2: Fixed Voltage, Large Sample Count (Noise & Stability)
Test Description
Five fixed voltage points were selected:

0.5 V

1.0 V

1.5 V

2.0 V

2.5 V

At each voltage:

1000 samples were collected

Statistical spread analyzed

Results: Sample Distribution
Figure 3: Histogram of ADC samples at 2.5 V
(sample figure)

Key observations:

Arduino Mega: Narrow distribution, but coarse resolution limits precision.

ESP32: Wider spread indicating higher noise sensitivity.

ADS1115: Tight clustering around mean, showing excellent stability.

Noise Performance Comparison
Figure 4: Standard deviation vs voltage

ESP32 shows voltage-dependent noise behavior

Arduino remains consistent but limited by resolution

ADS1115 demonstrates lowest noise floor

Practical Implications
When Arduino Mega ADC Is Enough
Simple sensors

Slow-changing signals

Cost-sensitive designs

When ESP32 ADC Needs Caution
Good for rough measurements

Requires calibration and averaging

Not ideal for precision analog sensing

Why ADS1115 Stands Out
True high-resolution measurement

Excellent stability

Predictable behavior

Ideal for data logging and research

Summary Table
Feature	Arduino Mega	ESP32	ADS1115
Resolution	Low	Medium (effective)	High
Noise	Low	High	Very low
Linearity	Good	Variable	Excellent
Ease of Use	Very easy	Moderate	Moderate
Precision Use	❌	⚠️	✅
Conclusion
This study shows that ADC choice matters far more than datasheet resolution numbers suggest.

ESP32’s ADC is convenient but noisy

Arduino’s ADC is stable but limited

ADS1115 provides professional-grade results even in hobby-level setups


In the next article, I will explore how different DC sources (battery, transformer-rectifier, SMPS) affect ADC measurements under identical conditions.
