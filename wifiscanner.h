#ifndef _APP_WIFI_SCANNER_H_
#define _APP_WIFI_SCANNER_H_

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "./wifiresult.h"


#define MAX_RESULT_SIZE 50

class WifiScanner {
    int resultSize = 0;
    WiFiResult    *wifiSSIDs;

  public:
    /**
       see http://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/scan-class.html
    */
    // -----------------------------------------------------------------------------
    int scan()
    // -----------------------------------------------------------------------------
    {
      Serial.println("Scan Networks");

      clear();

      resultSize = WiFi.scanNetworks();
      if(resultSize>MAX_RESULT_SIZE){
        resultSize = MAX_RESULT_SIZE;
      }
      wifiSSIDs = new WiFiResult[resultSize];
      for (int i = 0; i < resultSize; i++) {
        wifiSSIDs[i].duplicate = false;
        WiFi.getNetworkInfo(i, wifiSSIDs[i].SSID, wifiSSIDs[i].encryptionType, wifiSSIDs[i].RSSI, wifiSSIDs[i].BSSID, wifiSSIDs[i].channel, wifiSSIDs[i].isHidden);
      }

      // sort by signal strength
      for (int i = 0; i < resultSize; i++) {
        for (int j = i + 1; j < resultSize; j++) {
          if (wifiSSIDs[j].RSSI > wifiSSIDs[i].RSSI) {
            std::swap(wifiSSIDs[i], wifiSSIDs[j]);
          }
        }
      }
      return resultSize;
    }

    void toString(String & result) {
      toJson(result);
    }

    int size() {
      return resultSize;
    }

    void clear() {
      if (wifiSSIDs) {
        delete [] wifiSSIDs;
      }
      resultSize = 0;
    }

    void toJson(String & result) {
    
      DynamicJsonBuffer jsonBuffer;
      JsonArray &json = jsonBuffer.createArray();

      for (int i = 0; i < resultSize; i++) {
        JsonObject &obj = json.createNestedObject();
        wifiSSIDs[i].toJson(obj);
      }

      json.printTo(result);
    }
};

#endif // _APP_WIFI_SCANNER_H_
