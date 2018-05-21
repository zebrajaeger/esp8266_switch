//#include <string.h>
#include <fs.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

#include "./dnsserver.h"
#include "./wifiscanner.h"
#include "./config.h"

const char *ssid = "ESP8266 Access Point";

DNSServer         dnsServer;
ESP8266WebServer server(80);
Config config;
WifiScanner wifiScanner;

// -----------------------------------------------------------------------------
void setup()
// -----------------------------------------------------------------------------
{
  // Serial output
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // File System
  SPIFFS.begin();

  // read config
  config.fromFile("/config.json");
  Serial.println(config.toString());

  // WIFI
  WiFi.softAP(ssid);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  // DNS Server
  dnsServer.start(53, "*", WiFi.softAPIP());

  // HTTP Server
  server.on("/config.json", handleNotFound);

  server.on("/api/scan", handleScan);
  server.on("/api/scan/", handleScan);

  server.on("/api/config/network", HTTP_GET, handleConfigNetworkRead);
  server.on("/api/config/network/", HTTP_GET, handleConfigNetworkRead);

  server.on("/api/config/network", HTTP_POST, handleConfigNetworkWrite);
  server.on("/api/config/network/", HTTP_POST, handleConfigNetworkWrite);

  server.onNotFound(handle);

  server.begin();

  // DEBUG
  printFiles();
  wifiScanner.scan();
  
  String result;
  config.toJson(result);
  Serial.println(result);
}

// -----------------------------------------------------------------------------
void handleNotFound()
// -----------------------------------------------------------------------------
{
  Serial.println("handleNotFound()");

  server.send(404, "text/html", "Not found: '" + server.uri() + "'");
}

// -----------------------------------------------------------------------------
void handleScan()
// -----------------------------------------------------------------------------
{
  Serial.println("handleScan()");

  String result;
  wifiScanner.toJson(result);
  server.send(200, "application/json", result);
}

// -----------------------------------------------------------------------------
void handleConfigNetworkRead()
// -----------------------------------------------------------------------------
{
  Serial.println("handleConfigNetworkRead()");
  
  String result;
  config.toJson(result);
  server.send(200, "application/json", result);
}

// -----------------------------------------------------------------------------
void handleConfigNetworkWrite()
// -----------------------------------------------------------------------------
{
  Serial.println("handleConfigNetworkWrite()");

  if (server.args() == 1) {
    Serial.println("  (1)");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(server.arg(0));
    if (json.success()) {
      Serial.println("  (2)");
      config.fromJson(json);
    }
  }

  config.toFile("/config.json");

  String result;
  config.toJson(result);
  Serial.println("New Config:" + result );

  server.send(200, "application/json", result);
}

// -----------------------------------------------------------------------------
void handle()
// -----------------------------------------------------------------------------
{
  Serial.println("handle()");

  String url(server.uri());
  if (!handleFileRead("/ap" + url)) {
    handleNotFound();
  }
}

// -----------------------------------------------------------------------------
bool handleFileRead(String path)
// -----------------------------------------------------------------------------
{
  Serial.println("handleFileRead()");

  if (path.endsWith("/")) {
    path += "index.html";
  }

  Serial.println( "  request: '" + path + "'" );

  String contentType;
  if (path.endsWith(".htm") || path.endsWith(".html")) contentType = "text/html";
  else if (path.endsWith(".css")) contentType = "text/css";
  else if (path.endsWith(".js")) contentType = "application/javascript";
  else if (path.endsWith(".png")) contentType = "image/png";
  else if (path.endsWith(".gif")) contentType = "image/gif";
  else if (path.endsWith(".jpg")) contentType = "image/jpeg";
  else if (path.endsWith(".ico")) contentType = "image/x-icon";
  else if (path.endsWith(".xml")) contentType = "text/xml";
  else if (path.endsWith(".pdf")) contentType = "application/x-pdf";
  else if (path.endsWith(".zip")) contentType = "application/x-zip";
  else if (path.endsWith(".gz")) contentType = "application/x-gzip";
  else if (path.endsWith(".json")) contentType = "application/json";
  else contentType = "text/plain";

  if (SPIFFS.exists(path)) {
    Serial.println( "  sending file: '" + path + "'" );
    File file = SPIFFS.open(path, "r");
    server.sendHeader("Cache-Control", " max-age=172800");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
void loop()
// -----------------------------------------------------------------------------
{
  dnsServer.processNextRequest();
  server.handleClient();
}

// -----------------------------------------------------------------------------
void printFiles()
// -----------------------------------------------------------------------------
{
  Serial.print("Files");
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    Serial.print("  " + dir.fileName() + "(");
    File f = dir.openFile("r");
    Serial.print(f.size());
    Serial.println(")");
  }
}

