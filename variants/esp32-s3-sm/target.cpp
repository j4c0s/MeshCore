#include <Arduino.h>
#include "target.h"

ESP32S3SMBoard board;

#if defined(P_LORA_SCLK)
  static SPIClass spi;
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY, spi);
#else
  RADIO_CLASS radio = new Module(P_LORA_NSS, P_LORA_DIO_1, P_LORA_RESET, P_LORA_BUSY);
#endif

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
  fallback_clock.begin();

#if defined(PIN_BOARD_SDA) && defined(PIN_BOARD_SCL)
  Wire.begin(PIN_BOARD_SDA, PIN_BOARD_SCL);
#else
  Wire.begin();
#endif
  rtc_clock.begin(Wire);

#if ENV_INCLUDE_GPS && defined(PIN_GPS_RX) && defined(PIN_GPS_TX)
  gpsSerial.begin(9600, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
#endif

#if defined(P_LORA_SCLK)
  spi.begin(P_LORA_SCLK, P_LORA_MISO, P_LORA_MOSI);
  return radio.std_init(&spi);
#else
  return radio.std_init();
#endif
}

mesh::LocalIdentity radio_new_identity() {
  RadioNoiseListener rng(radio);
  return mesh::LocalIdentity(&rng);  // create new random identity
}
