#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "ESP32-WiFi";
const char pass[] = "esp32wifi";

const IPAddress ip(192, 168, 20, 2);
const IPAddress subnet(255, 255, 255, 0);


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);
  delay(1000);
  Serial.println("Initializing...");
  WiFi.softAPConfig(ip, ip, subnet);
  IPAddress serverIP = WiFi.softAPIP();
  server.begin();
  // put your setup code here, to run once:
}

void loop() {
  WiFiClient client = server.available();
  if(client)
  {
    Serial.println("success");
    client.println("FUCKOFF");
    server.println("FUCKOFF");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>ESP32 Web Server HTML</title>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>ESP32 Web Server HTML</h>");
    client.println("<p><a href=\"/H\"><button>LED:ON</button></a></p>");
    client.println("<p><a href=\"/L\"><button>LED:OFF</button></a></p>");
    client.println("</body>");
    client.println("</html>");
  }
  else
  {
    // Serial.println("cant open");
  }
  // put your main code here, to run repeatedly:
}