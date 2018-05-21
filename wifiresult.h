#ifndef _WIFI_RESULT_H_
#define _WIFI_RESULT_H_

#include <ArduinoJson.h>

class WiFiResult
{
  public:
    bool duplicate;
    String SSID;
    uint8_t encryptionType;
    int32_t RSSI;
    uint8_t* BSSID;
    int32_t channel;
    bool isHidden;

    WiFiResult()
    {
    }

    void toJson(JsonObject & root ) {
      char temp[50];

      root["SSID"] = SSID;

      root["encryptionType"] = encryptionType;

      sprintf(temp, "(%ddBm)", RSSI);
      root["RSSI"] = temp;

      sprintf(temp, "%02X:%02X:%02X:%02X:%02X:%02X", BSSID[0], BSSID[1], BSSID[2], BSSID[3], BSSID[4], BSSID[5]);
      root["BSSID"] = temp;

      root["channel"] = channel;

      root["hidden"] = isHidden ? "true" : "false";
    }
};


#endif // _WIFI_RESULT_H_
