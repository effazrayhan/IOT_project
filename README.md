# ESP32 IoT Monitoring — Temperature, Humidity, Soil Moisture, and Light

A compact IoT monitoring project for ESP32 that reads temperature & humidity (DHT11), soil moisture, and ambient light (LDR), and forwards the measurements to a Blynk dashboard. This README documents the repository structure, hardware wiring, software dependencies, build and configuration steps, and troubleshooting tips.




## Project snapshot

This project contains a simple ESP32 sketch (`func.cpp`) that:
- Reads DHT11 temperature and humidity on GPIO 15.
- Reads a soil moisture sensor on ADC GPIO 34 and converts it to a percent value.
- Reads an LDR on ADC GPIO 35 and converts it to a percent value.
- Publishes values to a Blynk dashboard at virtual pins V0..V3.
- Sends updates on a 2-second interval and logs values over serial at 115200 baud.

Files inspected while writing this README:
- `func.cpp`      — main ESP32 sketch (sensors, pins, Blynk integration)
- `LICENSE`       — MIT License (copyright 2025 Effaz Rayhan Anando)
- `iot.jpg`       — project image (illustration/asset)
- `test.txt`, `test2.txt` — miscellaneous text files in the repo




## Features

- Temperature and humidity reading (DHT11)
- Soil moisture reading and percent mapping
- Ambient light (LDR) reading and percent mapping
- Push to remote Blynk dashboard using Blynk library for ESP32
- Serial logging for local debugging




## Hardware required

- ESP32 development board (any common Dev Module)
- DHT11 temperature & humidity sensor
- Soil moisture sensor (analog output)
- LDR (photoresistor) + pull-down resistor (e.g., 10k) or LDR module
- Breadboard and jumper wires
- USB cable to flash the ESP32




## Wiring / Pin mapping

Use the GPIO pins defined in `func.cpp`. Example wiring to match the sketch:

- DHT11 data pin -> GPIO 15
- Soil moisture analog out -> GPIO 34 (ADC)
- LDR analog out -> GPIO 35 (ADC)
- GND -> sensor grounds
- 3.3V -> sensors that require 3.3V (verify module voltage requirements)

Note: GPIO numbers above correspond to the constants in `func.cpp`: `DHTPIN = 15`, `SOIL_PIN = 34`, `LDR_PIN = 35`.




## Software dependencies

You can use either Arduino IDE (with ESP32 support) or PlatformIO.

Required libraries:
- Blynk library supporting ESP32 (BlynkSimpleEsp32)
- DHT sensor library (DHT.h)

On Arduino IDE:
1. Install the ESP32 board support via the board manager (Espressif ESP32).
2. Install the DHT and Blynk libraries via Library Manager.

If you use PlatformIO, add the appropriate `lib_deps` entries for Blynk and DHT.




## Configuration

Open `func.cpp` and replace the placeholders with your own values:

- BLYNK_TEMPLATE_ID, BLYNK_DEVICE_NAME (optional)
- BLYNK_AUTH_TOKEN — put your Blynk device token here
- `ssid` and `pass` — WiFi SSID and password for the network the ESP32 will join

Important constants in `func.cpp` (for reference):
- Sampling interval: 2000 ms (2 seconds)
- Serial baud: 115200
- Virtual pins used:
  - V0 = temperature (°C)
  - V1 = humidity (%)
  - V2 = soil moisture (%)
  - V3 = light level (%)

Sensor analog scaling in `func.cpp`:
- Soil moisture analogRead range mapped from 4095 -> 0 to 0 -> 100%
- LDR analogRead range mapped from 0 -> 4095 to 0 -> 100%

Adjust mappings if your sensor/module reports inverted or different ranges.




## Build & Flash (Arduino IDE)

1. Open `func.cpp` with the Arduino IDE (File > Open).
2. Select the correct board: Tools > Board > `ESP32 Dev Module` (or your board).
3. Select the correct Port.
4. Install required libraries (Blynk, DHT).
5. Edit `func.cpp` to set your WiFi credentials and Blynk token.
6. Click Upload.

Open the Serial Monitor at 115200 baud to observe sensor output.

## Build & Flash (PlatformIO)

A minimal `platformio.ini` example (add to project root) — adjust as needed:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps =
  blynkkk/Blynk@^1.0.0  ; adjust to a compatible Blynk package
  adafruit/DHT sensor library@^1.4.3
```

Then build and upload with:

```bash
platformio run --target upload
platformio device monitor
```




## How it works (brief)

1. On `setup()` the sketch initializes Serial, Blynk, and the DHT sensor.
2. A BlynkTimer calls `sendData()` every 2000 ms.
3. `sendData()` reads the DHT11 and both analog sensors, maps analog values to percentages, prints values to Serial, and sends values to Blynk virtual pins V0..V3.

This keeps a remote dashboard updated while also providing local logs for debugging.




## Verifying & Troubleshooting

- Serial monitor at 115200 will show lines like:
  - "Temperature: X °C"
  - "Humidity: Y %"
  - "Soil Moisture: Z %"
  - "Light Level: W %"

- If DHT readings show NaN or fail repeatedly:
  - Check DHT wiring and pin number (GPIO 15 in the sketch).
  - Ensure the DHT library is installed and DHT type matches (DHT11).

- If analog values are always 0 or 4095:
  - Verify ADC pin wiring and that the sensor/module outputs a valid analog voltage.
  - Some ESP32 boards have ADC attenuation settings — hardware modules may include required resistors.

- If Blynk does not receive values:
  - Verify Blynk auth token and WiFi credentials in `func.cpp`.
  - Check that the board connects to WiFi (Serial prints will indicate connection progress) and that the board has internet access.

