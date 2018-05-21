#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include <fs.h>
#include <ArduinoJson.h>

class Config {
  public:
    String BSSID;
    String password;

    // -----------------------------------------------------------------------------
    void fromFile(String path)
    // -----------------------------------------------------------------------------
    {
      Serial.println("load config from '" + path + "'");

      if (SPIFFS.exists(path)) {
        File configFile = SPIFFS.open(path, "r");
        if (configFile) {
          size_t size = configFile.size();
          std::unique_ptr<char[]> buf(new char[size]);
          configFile.readBytes(buf.get(), size);
          DynamicJsonBuffer jsonBuffer;
          JsonObject& json = jsonBuffer.parseObject(buf.get());
          if (json.success()) {
            fromJson(json);
          }
        } else {
          Serial.println("  failed to open config file for reading");
        }
      } else {
        Serial.println("  config file does not exist");
      }
    }

    // -----------------------------------------------------------------------------
    void toFile(String path)
    // -----------------------------------------------------------------------------
    {
      Serial.println("saving config to '" + path + "'");

      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();

      toJson(json);

      File configFile = SPIFFS.open(path, "w");
      if (!configFile) {
        Serial.println("  failed to open config file for writing");
      }

      json.printTo(configFile);
      configFile.close();
    }

    // -----------------------------------------------------------------------------
    void fromJson(JsonObject & root)
    // -----------------------------------------------------------------------------
    {
      // ".as<String>()" is a workaround, see https://arduinojson.org/example/string/
      BSSID = root["BSSID"].as<String>();
      password = root["password"].as<String>();
    }

    // -----------------------------------------------------------------------------
    bool hasSSID()
    // -----------------------------------------------------------------------------
    {
      return BSSID.length() > 0;
    }

    // -----------------------------------------------------------------------------
    bool hasPassword()
    // -----------------------------------------------------------------------------
    {
      return password.length() > 0;
    }

    // -----------------------------------------------------------------------------
    String toString()
    // -----------------------------------------------------------------------------
    {
      String result;
      toJson(result);
      return result;
    }
    
    // -----------------------------------------------------------------------------
    void toJson(JsonObject & root)
    // -----------------------------------------------------------------------------
    {
      root["BSSID"] = BSSID;
      root["password"] = password;
    }

    // -----------------------------------------------------------------------------
    void toJson(String & result)
    // -----------------------------------------------------------------------------
    {
      DynamicJsonBuffer jsonBuffer;
      JsonObject &json = jsonBuffer.createObject();

      toJson(json);

      json.printTo(result);
    }
};

#endif //_APP_CONFIG_H_
