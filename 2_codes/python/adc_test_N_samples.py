"""
PC Serial Logger for ADC Test (ESP32 Master Output)

This script reads ADC dataset lines from ESP32 over Serial (USB)
and saves them into a CSV file on the Desktop.

ESP32 expected serial line format:
    A<mega_raw>; E<esp_raw>; D<ads_raw>;

Example:
    A436; E1857; D13296;

Workflow:
1) Ask once: number of samples per voltage step (SAMPLES)
2) For each voltage step:
   - User enters UT203+ measured voltage manually
   - Script collects SAMPLES serial lines
   - Stores them as one row in CSV

Output CSV structure:
[Index, Date, Time, UT203, ADS(0..N-1), ARD(0..N-1), ESP(0..N-1)]
"""

import serial
import time
import csv
from datetime import datetime
import os


# ---------------- SERIAL CONFIG ----------------
PORT = "COM5"          # Change this according to your system (Windows: COMx)
BAUD = 115200          # Must match ESP32 Serial.begin()
TIMEOUT = 1            # Seconds


# ---------------- ASK SAMPLE COUNT (ONCE) ----------------
while True:
    try:
        SAMPLES = int(input("Enter number of samples per voltage (once): ").strip())
        if SAMPLES <= 0:
            raise ValueError
        break
    except ValueError:
        print("❌ Invalid number, try again")


# ---------------- OPEN SERIAL PORT ----------------
ser = serial.Serial(PORT, BAUD, timeout=TIMEOUT)

# Give ESP32 time to reset after opening serial
time.sleep(2)

print("Serial monitoring started...")


# ---------------- CSV OUTPUT SETUP ----------------
# Save file on Desktop automatically
desktop_path = os.path.join(os.path.expanduser("~"), "Desktop")

csv_filename = os.path.join(
    desktop_path,
    f"adc_log_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv"
)

file = open(csv_filename, "w", newline="")
writer = csv.writer(file)


# ---------------- CSV HEADER ----------------
# First basic columns
header = ["Index", "Date", "Time", "UT203"]

# Then add sample columns
for i in range(SAMPLES):
    header.append(f"ADS({i})")   # ADS1115 samples
for i in range(SAMPLES):
    header.append(f"ARD({i})")   # Arduino Mega samples
for i in range(SAMPLES):
    header.append(f"ESP({i})")   # ESP32 ADC samples

writer.writerow(header)

# Row index counter
index = 1


# ---------------- PARSE FUNCTION ----------------
def parse_line(line: str):
    """
    Parses one dataset line from ESP32.

    Expected input format:
        A436; E1857; D13296;

    Returns:
        (a, e, d)
        a = Arduino Mega raw ADC
        e = ESP32 raw ADC
        d = ADS1115 raw ADC

    If parsing fails, values remain None.
    """
    a = e = d = None

    # Remove whitespace, remove last ';', split by ';'
    parts = line.strip().rstrip(";").split(";")

    for p in parts:
        p = p.strip()

        if p.startswith("A"):
            try:
                a = int(p[1:])
            except:
                pass

        elif p.startswith("E"):
            try:
                e = int(p[1:])
            except:
                pass

        elif p.startswith("D"):
            try:
                d = int(p[1:])
            except:
                pass

    return a, e, d


# ---------------- MAIN LOOP ----------------
try:
    while True:

        # User enters voltage measured by UT203+ multimeter
        ut = input("\nEnter UT203+ voltage (or 'q' to quit): ").strip()

        # Exit condition
        if ut.lower() == "q":
            break

        # Pre-allocate sample arrays
        ads = [None] * SAMPLES
        ard = [None] * SAMPLES
        esp = [None] * SAMPLES

        # Clear old serial data before starting new capture
        ser.reset_input_buffer()

        print(f"Logging {SAMPLES} samples...")

        count = 0
        while count < SAMPLES:

            # Read one line from serial
            line = ser.readline().decode(errors="ignore").strip()

            # Skip empty lines
            if not line:
                continue

            # Parse the dataset line
            a, e, d = parse_line(line)

            # Skip invalid lines
            if a is None and e is None and d is None:
                continue

            # Store each sample
            ads[count] = d
            ard[count] = a
            esp[count] = e

            count += 1
            print(f"Sample {count:03d}: A:{a} | E:{e} | D:{d}")

        # Timestamp for this row
        now = datetime.now()

        # Base row fields
        row = [
            index,
            now.strftime("%d.%m.%Y"),
            now.strftime("%H.%M.%S.%f")[:-3],  # milliseconds precision
            ut
        ]

        # Append all sample arrays in order
        row.extend(ads)
        row.extend(ard)
        row.extend(esp)

        # Write row to CSV
        writer.writerow(row)
        file.flush()

        print(f"✔ Row {index} saved")
        index += 1


except KeyboardInterrupt:
    print("\nStopped by user")


finally:
    # Always close resources properly
    file.close()
    ser.close()
    print("Serial closed, file saved.")
