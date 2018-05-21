export interface LedData {
  // this is a boolean bu we handle this as a string due to error in domain of JsonArray or ESP8266 code.
  state: String;
}
