#include <Arduino.h>
#include <esp_camera.h>
#include <WiFi.h>

WiFiServer server(80);

const char ssid[] = "ESP32-WiFi";
const char pass[] = "esp32wifi";

const IPAddress ip(192, 168, 20, 2);
const IPAddress subnet(255, 255, 255, 0);

void setup()
{
  Serial.begin(115200);
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
  config.pin_pwdn = -1;

  config.xclk_freq_hz = 20000000;
  config.ledc_timer = LEDC_TIMER_0;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.pixel_format = PIXFORMAT_YUV422;
  config.frame_size = FRAMESIZE_QQVGA;
  // config.pixel_format = PIXFORMAT_RGB888;
  // config.frame_size = FRAMESIZE_QQVGA;

  // config.jpeg_quality = 50;
  config.fb_count = 1;

esp_err_t  err = esp_camera_init(&config);
if(err != ESP_OK)
{
  Serial.println("Error");
}
}



void loop() {
  
  WiFiClient client = server.available();
  
  if(client)
  {
    Serial.println("success");
    client.println("FUCKOFF");
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
  
  camera_fb_t *fb = NULL;
  esp_err_t res = ESP_OK;

  fb = esp_camera_fb_get();
  if(!fb)
  {
    Serial.println("holy shit");
  }
  Serial.println(fb -> len);
}
