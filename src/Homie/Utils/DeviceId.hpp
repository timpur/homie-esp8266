#pragma once

#include "Arduino.h"

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

#include "../Limits.hpp"
#include "../Utils/Helpers.hpp"

namespace HomieInternals {
class DeviceId {
 public:
  static const char* get();
};
}  // namespace HomieInternals
