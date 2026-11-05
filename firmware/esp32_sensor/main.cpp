#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_IOT_VLAN_SSID";
const char* password = "YOUR_VLAN_PASSWORD";
const char* mqtt_server = "10.10.40.10";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      if (client.connect("ESP32_TelemetryNode", "iot_user", "iot_pass")) {
        client.publish("telemetry/node1/status", "online");
      } else {
        delay(5000);
      }
    }
  }
  client.loop();
  delay(10000);
}
