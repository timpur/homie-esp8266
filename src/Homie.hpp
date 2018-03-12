#pragma once

#include "Arduino.h"
#include "AsyncMqttClient.h"

#include "Homie/Datatypes/Interface.hpp"
#include "Homie/Constants.hpp"
#include "Homie/Limits.hpp"
#include "Homie/Utils/DeviceId.hpp"
#include "Homie/Boot/Boot.hpp"
#include "Homie/Boot/BootStandalone.hpp"
#include "Homie/Boot/BootNormal.hpp"
#include "Homie/Boot/BootConfig.hpp"
#include "Homie/Logger.hpp"
#include "Homie/Config.hpp"
#include "Homie/Blinker.hpp"
#include "Homie/Utils/HomieButton.hpp"

#include "SendingPromise.hpp"
#include "HomieBootMode.hpp"
#include "HomieEvent.hpp"
#include "HomieNode.hpp"
#include "HomieSetting.hpp"
#include "StreamingOperator.hpp"

// Define DEBUG for debug

#define Homie_setFirmware(name, version) const char* __FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" name "\x93\x44\x6b\xa7\x75"; const char* __FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" version "\xb0\x30\x48\xd4\x1a"; Homie.__setFirmware(name, version);
#define Homie_setBrand(brand) const char* __FLAGGED_BRAND = "\xfb\x2a\xf5\x68\xc0" brand "\x6e\x2f\x0f\xeb\x2d"; Homie.__setBrand(brand);

namespace HomieInternals {
class HomieClass {
  friend class ::HomieNode;
  friend SendingPromise;

 public:
  HomieClass();
  ~HomieClass();
  void setup();
  void loop();

  bool loadSettings();

  void __setFirmware(const char* name, const char* version);
  void __setBrand(const char* brand) const;

  HomieClass& disableLogging();
  HomieClass& setLoggingPrinter(Print* printer);
  HomieClass& disableLedFeedback();
  HomieClass& setLedPin(uint8_t pin, uint8_t on);
  HomieClass& setConfigurationApPassword(const char* password);
  HomieClass& setGlobalInputHandler(const GlobalInputHandler& globalInputHandler);
  HomieClass& setBroadcastHandler(const BroadcastHandler& broadcastHandler);
  HomieClass& onEvent(const EventHandler& handler);
  HomieClass& setResetTrigger(uint8_t pin, bool state, uint16_t time);
  HomieClass& disableResetTrigger();
  HomieClass& setSetupFunction(const CallbackFunction& function);
  HomieClass& setLoopFunction(const CallbackFunction& function);
  HomieClass& setHomieBootMode(HomieBootMode bootMode);
  HomieClass& setHomieBootModeOnNextBoot(HomieBootMode bootMode);
  HomieClass& setHomieButtonClick(CallbackFunction& function);

  static void reset();
  static void reboot();
  static void setIdle(bool idle);
  static bool isConfigured();
  static bool isConnected();
  static const ConfigStruct& getConfiguration();
  AsyncMqttClient& getMqttClient();
  Logger& getLogger();
  static String getDeviceID();
  static void prepareToSleep();
  static void doDeepSleep(uint32_t time_us = 0, RFMode mode = RF_DEFAULT);

 private:
  bool _setupCalled;
  bool _firmwareSet;
  bool _loadedSettings;
  Boot* _boot;
  BootStandalone _bootStandalone;
  BootNormal _bootNormal;
  BootConfig _bootConfig;
  SendingPromise _sendingPromise;
  Logger _logger;
  Blinker _blinker;
  Config _config;
  AsyncMqttClient _mqttClient;

  void _checkBeforeSetup(const __FlashStringHelper* functionName) const;

  const char* __HOMIE_SIGNATURE;
};
}  // namespace HomieInternals

extern HomieInternals::HomieClass Homie;
