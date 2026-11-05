# :satellite: Edge IoT Telemetry & Automation Platform

[![PlatformIO](https://img.shields.io/badge/Firmware-C%2B%2B%20%2F%20PlatformIO-F58220?style=for-the-badge&logo=cplusplus&logoColor=white)](https://platformio.org)
[![ESP32](https://img.shields.io/badge/Hardware-ESP32%20%2F%20ESP8266-E7352C?style=for-the-badge&logo=espressif&logoColor=white)](https://espressif.com)
[![MQTT](https://img.shields.io/badge/Message%20Broker-Eclipse%20Mosquitto-3C5280?style=for-the-badge&logo=eclipse-mosquitto&logoColor=white)](https://mosquitto.org)
[![Home Assistant](https://img.shields.io/badge/Automation%20Engine-Home%20Assistant-41BDF5?style=for-the-badge&logo=homeassistant&logoColor=white)](https://www.home-assistant.io)

An end-to-end edge Internet-of-Things (IoT) platform connecting physical microcontrollers (ESP32/ESP8266) to private cloud telemetry engines over an isolated IoT VLAN. Features C++ firmware with Last Will & Testament (LWT) disconnect monitoring, authenticated MQTT pub/sub data streams, and automated Home Assistant threshold triggers.

---

## :triangular_ruler: Edge IoT Architecture

```mermaid
flowchart TD
    subgraph Edge Layer [Isolated IoT VLAN]
        ESP1[ESP32 Telemetry Node #1<br/>DHT22 / I2C Sensors]
        ESP2[ESP8266 Microcontroller #2<br/>Relay & Environment]
    end

    subgraph Messaging & Ingress
        Broker[Eclipse Mosquitto MQTT Broker :1883<br/>Authenticated TLS / LWT Enabled]
    end

    subgraph Automation & Processing
        HA[Home Assistant Core :8123<br/>Automations & State Engine]
        Prom[Prometheus Telemetry Scraper]
    end

    subgraph Actions & Alerts
        Cooling[Relay Actuators / Cooling Fans]
        Notify[Push Notifications / Telegram Alerts]
    end

    ESP1 -->|Publish JSON Telemetry| Broker
    ESP2 -->|Publish JSON Telemetry| Broker
    Broker -->|Subscribe home/sensors/#| HA
    HA -->|Trigger Alert Conditions| Notify
    HA -->|Command Actuator Relays| Cooling
    HA --> Prom
```

---

## :gear: MQTT Topic Taxonomy

| Topic Pattern | Direction | Payload Example | Description |
| :--- | :--- | :--- | :--- |
| `home/sensors/+/telemetry` | Publish | `{"temperature": 24.5, "humidity": 55.2, "rssi": -62}` | Periodic sensor telemetry payload |
| `home/sensors/+/status` | LWT / State | `"online"` / `"offline"` | Last Will & Testament connectivity state |
| `home/actuators/cooling/relay1` | Subscribe | `"ON"` / `"OFF"` | Actuator switch control state |

---

## :rocket: Deployment & Provisioning

### 1. Boot Local Services
```bash
git clone https://github.com/Aryan-136/iot-automation-platform.git
cd iot-automation-platform

docker compose up -d
```

### 2. Flashing ESP32 Firmware
```bash
cd firmware/esp32_telemetry
# Compile and flash via PlatformIO
pio run --target upload
```

---

## :file_folder: Repository Layout
```text
.
â”œâ”€â”€ config/
â”‚   â”œâ”€â”€ homeassistant/
â”‚   â”‚   â””â”€â”€ automations.yaml      # Automated threshold triggers & alerts
â”‚   â””â”€â”€ mosquitto/
â”‚       â””â”€â”€ mosquitto.conf        # Hardened MQTT broker configuration
â”œâ”€â”€ firmware/
â”‚   â””â”€â”€ esp32_telemetry/
â”‚       â””â”€â”€ src/
â”‚           â””â”€â”€ main.cpp          # Production C++ firmware with JSON serialization
â”œâ”€â”€ docker-compose.yml            # Mosquitto & Home Assistant orchestration
â””â”€â”€ README.md                     # Architectural documentation & topic taxonomy
```