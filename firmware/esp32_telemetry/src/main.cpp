/**
 * ESP32 Production IoT Telemetry Node
 * Author: Aryan Pandya (Aryan-136)
 * Protocols: WiFi 802.11 b/g/n, MQTT v3.1.1, JSON Serialization
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Network Credentials
const char* WIFI_SSID     = "AryanCloud_IoT_VLAN";
const char* WIFI_PASSWORD = "HardenedVlanPassword";
const char* MQTT_SERVER   = "192.168.30.5";
const int   MQTT_PORT     = 1883;
const char* MQTT_USER     = "esp32_client";
const char* MQTT_PASS     = "SecureClientKey";

// Device Identification
const char* DEVICE_ID     = "esp32-node-01";
const char* TOPIC_PUB     = "home/sensors/esp32-node-01/telemetry";
const char* TOPIC_LWT     = "home/sensors/esp32-node-01/status";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
const long interval = 10000; // 10-second intervals

void setup_wifi() {
    delay(10);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void reconnect_mqtt() {
    while (!client.connected()) {
        // Connect with Last Will and Testament (LWT) for graceful offline detection
        if (client.connect(DEVICE_ID, MQTT_USER, MQTT_PASS, TOPIC_LWT, 1, true, "offline")) {
            client.publish(TOPIC_LWT, "online", true);
        } else {
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
    if (!client.connected()) {
        reconnect_mqtt();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastPublish > interval) {
        lastPublish = now;

        // Simulated high-precision industrial telemetry
        float temperature = 24.5 + (random(-15, 15) / 10.0);
        float humidity = 55.0 + (random(-20, 20) / 10.0);
        int wifiRssi = WiFi.RSSI();

        StaticJsonDocument<256> doc;
        doc["device_id"] = DEVICE_ID;
        doc["uptime_sec"] = millis() / 1000;
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;
        doc["wifi_rssi"] = wifiRssi;

        char buffer[256];
        serializeJson(doc, buffer);
        client.publish(TOPIC_PUB, buffer);
    }
}