#pragma once

#include "Arduino.h"

#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#error Platform not supported
#endif

#include "../../StreamingOperator.hpp"
#include "../Datatypes/Interface.hpp"
#include "../Constants.hpp"
#include "../Limits.hpp"
#include "../Utils/Helpers.hpp"

namespace HomieInternals {
class Boot {
 public:
  explicit Boot(const char* name);
  virtual void setup();
  virtual void loop();

 protected:
  const char* _name;
};
}  // namespace HomieInternals
