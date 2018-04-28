#include "DeviceId.hpp"

using namespace HomieInternals;


const char* DeviceId::get() {
  static char _deviceId[MAX_MAC_STRING_LENGTH];

  if (strlen(_deviceId)) return _deviceId;

  uint8_t mac[MAX_MAC_LENGTH];
  WiFi.enableSTA(true);
  WiFi.macAddress(mac);
  Helpers::macToString(mac, _deviceId);

  return _deviceId;
}
