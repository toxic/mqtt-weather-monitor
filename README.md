# mqtt-weather-monitor
Read temperature, humidity and light values and publish to MQTT and display data via web UI.

## Hardware
- Arduino UNO
- CC3000 WIFI shield
- DHT11 sensor (temperature & humidity)
- Arduino KY-018 Photo resistor module

## Software
- Arduino IDE or VisualStudio Code + arduino extention
- MQTT (mosquitto) server
- Node-RED + Node-RED-dashboard for web UI
- (optional) MQTT.fx desktop client to test MQTT server (publish & subscribe to feeds)
