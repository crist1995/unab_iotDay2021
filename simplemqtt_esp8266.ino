#include <ESP8266WiFi.h>

#include <PubSubClient.h>

#define wifi_ssid "VTR-7795765"
#define wifi_password "fx5kqSsnLpn7"

#define mqtt_server "40.75.125.160"  // MQTT Cloud address

long lastMsg=0;
WiFiClient espClient;
PubSubClient client(espClient);
int i=0;
void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
    delay(10);
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("nodeMcuDHT11")) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
    return newValue < prevValue - maxDiff || newValue > prevValue + maxDiff;
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

            Serial.print("New value:");
            Serial.println(String(i).c_str());
            client.publish("temperature/topic", String(i).c_str(), true);
    delay(1000);    
    i++;
}
