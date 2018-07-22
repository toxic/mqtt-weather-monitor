# mqtt-weather-monitor
Read temperature, humidity and light values and publish to MQTT and display data via web UI.

## Hardware
- Arduino UNO
- CC3000 WIFI shield
- DHT11 sensor (temperature & humidity)
- Arduino KY-018 Photo resistor module

## Software
- Arduino IDE

  You have to install external libraries:
  - Adafruit CC3000 Library
  - Adafruit MQTT Library
  - DHT Sensor Library
- (optional) VisualStudio Code + arduino extention
  
  If you choose to use VisualStudio Code for coding you have to configure few things for it to work.
  1. Set user settings parameter for intelliSense Engine to { "C_Cpp.intelliSenseEngine": "Tag Parser" }
  2. Follow instructions from (https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
  
- [MQTT server](https://www.eclipse.org/mosquitto/download/) 
- [Node-RED](https://nodered.org/) + Node-RED-dashboard for web UI
- (optional) [MQTT.fx](http://mqttfx.jensd.de/) desktop client to test MQTT server (publish & subscribe to feeds)
