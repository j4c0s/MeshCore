# 🛰 ESP32-C3 Super Mini Repeater

This variant supports the **ESP32-C3 Super Mini** board with an **SX1262 (HT-RA62)** LoRa module, **DS3231 RTC** for offline timekeeping, and optional **I2C sensors** (such as INA3221) or **GPS**.

---

## 📌 Pinout & Wiring

### 1. ESP32-C3 to SX1262 (LoRa)
| SX1262 Pin | ESP32-C3 Pin | Description |
|------------|--------------|-------------|
| VCC        | 3.3V         | Power (3.3V) |
| GND        | GND          | Ground |
| NSS        | GPIO 10      | SPI Chip Select |
| SCK        | GPIO 2       | SPI Clock |
| MOSI       | GPIO 4       | SPI MOSI |
| MISO       | GPIO 3       | SPI MISO |
| DIO1       | GPIO 5       | Interrupt |
| BUSY       | GPIO 6       | Busy Signal |
| RESET      | GPIO 7       | Reset |

---

### 2. ESP32-C3 to Sensors & RTC (I2C)
| Sensor/RTC Pin | ESP32-C3 Pin | Description |
|----------------|--------------|-------------|
| VCC            | 3.3V         | Power (3.3V) |
| GND            | GND          | Ground |
| SDA            | GPIO 8       | I2C Data |
| SCL            | GPIO 9       | I2C Clock |

---

### 3. ESP32-C3 to GPS (UART)
| GPS Pin | ESP32-C3 Pin | Description |
|---------|--------------|-------------|
| VCC     | 3.3V         | Power (3.3V) |
| GND     | GND          | Ground |
| TX      | GPIO 21      | UART RX (MCU RX) |
| RX      | GPIO 20      | UART TX (MCU TX) |

---

## ⚡ Build Environment

Building via PlatformIO:
```bash
pio run -e esp32c3_supermini_sx1262_repeater
```
