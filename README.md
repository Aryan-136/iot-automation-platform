# ðŸ“¡ IoT Automation Platform: ESP32 Telemetry & Home Assistant Hub

[![ESP32](https://img.shields.io/badge/Hardware-ESP32%20%2F%20ESP8266-red?style=flat-square&logo=espressif)](https://www.espressif.com/)
[![Home Assistant](https://img.shields.io/badge/Hub-Home%20Assistant-blue?style=flat-square&logo=homeassistant)](https://www.home-assistant.io/)
[![Protocol](https://img.shields.io/badge/Protocol-MQTT%20(Mosquitto)-lightgrey?style=flat-square)](https://mqtt.org/)

End-to-end IoT platform connecting microcontroller edge devices (ESP32) over an isolated VLAN via MQTT to a central Home Assistant automation engine.

---

## âš¡ Architecture Highlights
- **VLAN Isolation**: All microcontrollers sit on an isolated VLAN with no Internet egress route.
- **MQTT Broker**: Eclipse Mosquitto broker with username/password authentication and TLS encryption.
- **Custom Firmware**: C++ / Arduino sketches for ESP32 with automatic WiFi reconnection, deep sleep power management, and JSON payload publishing.
