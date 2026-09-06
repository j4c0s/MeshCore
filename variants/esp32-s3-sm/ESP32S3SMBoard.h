#pragma once

#include <helpers/ESP32Board.h>
#include <Arduino.h>

class ESP32S3SMBoard : public ESP32Board {
public:
  void begin() {
    ESP32Board::begin();
  }

  const char* getManufacturerName() const override {
    return "ESP32-C3 Super Mini";
  }
};
