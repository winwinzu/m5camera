#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "ESP32-WiFi";
const char pass[] = "esp32wifi";

const IPAddress ip(192, 168, 20, 2);
const IPAddress subnet(255, 255, 255, 0);

esp_err_t err;
void camera_setup()
{
  camera_config_t config;
  config.pin_sscb_scl = 23;
  config.pin_sscb_sda = 22;
  config.pin_xclk = 27;
  config.pin_vsync = 25;
  config.pin_href = 26;
  config.pin_pclk = 21;
  config.pin_d0 = 32;
  config.pin_d1 = 35;
  config.pin_d2 = 34;
  config.pin_d3 = 5;
  config.pin_d4 = 39;
  config.pin_d5 = 18;
  config.pin_d6 = 36;
  config.pin_d7 = 19;
  config.pin_reset = 15;
  
  config.xclk_freq_hz = 20000000;
  config.ledc_timer = LEDC_TIMER_0;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_240X240;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  err = esp_camera_init(&config);
}


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);
  delay(1000);
  Serial.println("Initializing...");
  WiFi.softAPConfig(ip, ip, subnet);
  IPAddress serverIP = WiFi.softAPIP();
  server.begin();
  camera_setup();
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
  if(err != ESP_OK)
  {
    Serial.println("fuck");
  }
}