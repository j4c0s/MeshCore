#pragma once

#include <helpers/ESP32Board.h>
#include <Arduino.h>

class ESP32C3SuperMiniBoard : public ESP32Board {
public:
  const char* getManufacturerName() const override {
    return "ESP32-C3 Super Mini";
  }
};
