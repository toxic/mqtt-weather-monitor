
#include <Adafruit_CC3000.h>
#include "DHT.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

int DHT_DIGITAL_PIN = 7;
int LIGHT_ANALOG_PIN = A1;
int MIC_DIGITAL_PIN = 8;

DHT dht(DHT_DIGITAL_PIN, DHT11);

// CC3000 interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3 // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT  5 // These can be
#define ADAFRUIT_CC3000_CS   10 // any two pins
// Hardware SPI required for remaining pins.
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);
Adafruit_CC3000_Client wifi_client;

// WiFi access point credentials
#define WLAN_SSID     "WIFI_SID"
#define WLAN_PASS     "WIFI_PASS"
#define WLAN_SECURITY WLAN_SEC_WPA2

// Setup the MQTT
#define MQTT_SERVER      "MQTT_SERVER_ADDRESS"
#define MQTT_SERVERPORT  1883
Adafruit_MQTT_Client mqtt(&wifi_client, MQTT_SERVER, MQTT_SERVERPORT);

// Setup MQTT publish
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, "home/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, "home/humidity");
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish(&mqtt, "home/light");

void MQTT_connect();

void setup() {

  Serial.begin(115200);

  pinMode(MIC_DIGITAL_PIN, INPUT);

  // Init & connect to WIFI
  Serial.print("WIFI: ");
  
  cc3000.begin();
  cc3000.deleteProfiles();
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);

  /* Wait for DHCP to complete */
  while (!cc3000.checkDHCP()) {
    delay(100);
  }
  Serial.println("Connected");

  // Init temperature & humidity sensor
  dht.begin();
}

void loop() {
  MQTT_connect();

  // publish values
  temperature.publish(dht.readTemperature());
  humidity.publish(dht.readHumidity());
  light.publish((uint32_t)analogRead(LIGHT_ANALOG_PIN));

  delay(1000 * 60 * 5); // every 5 minutes
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("MQTT: ");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));

    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1); // die
    }
  }
  Serial.println("Connected");
}
