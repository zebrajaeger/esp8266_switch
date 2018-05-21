export interface WifiNetwork {
  SSID: String,
  encryptionType: Number,
  RSSI: String,
  BSSID: String,
  channel: Number,

  // this is a boolean bu we handle this as a string due to error in domain of JsonArray or ESP8266 code.
  hidden: String
}
