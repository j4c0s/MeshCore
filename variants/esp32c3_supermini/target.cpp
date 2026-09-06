#include <Arduino.h>
#include "target.h"

ESP32C3SuperMiniBoard board;

static SPIClass spi(FSPI);
static Module module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY, spi);
RADIO_CLASS radio(&module);

WRAPPER_CLASS radio_driver(radio, board);

ESP32RTCClock fallback_clock;
AutoDiscoverRTCClock rtc_clock(fallback_clock);

#if ENV_INCLUDE_GPS
  #include <helpers/sensors/MicroNMEALocationProvider.h>
  #if defined(PIN_GPS_RX) && defined(PIN_GPS_TX)
    HardwareSerial gpsSerial(1);
    MicroNMEALocationProvider nmea = MicroNMEALocationProvider(gpsSerial, &rtc_clock);
  #else
    MicroNMEALocationProvider nmea = MicroNMEALocationProvider(Serial1, &rtc_clock);
  #endif
  EnvironmentSensorManager sensors = EnvironmentSensorManager(nmea);
#else
  EnvironmentSensorManager sensors;
#endif

bool radio_init() {
  board.begin();
  fallback_clock.begin();

#if defined(PIN_BOARD_SDA) && defined(PIN_BOARD_SCL)
  Wire.begin(PIN_BOARD_SDA, PIN_BOARD_SCL);
#else
  Wire.begin();
#endif
  rtc_clock.begin(Wire);
  sensors.begin();

#if ENV_INCLUDE_GPS && defined(PIN_GPS_RX) && defined(PIN_GPS_TX)
  gpsSerial.begin(9600, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
#endif

  spi.begin(P_LORA_SCLK, P_LORA_MISO, P_LORA_MOSI, P_LORA_NSS);
  return radio.std_init(&spi);
}

mesh::LocalIdentity radio_new_identity() {
  RadioNoiseListener rng(radio);
  return mesh::LocalIdentity(&rng);
}
