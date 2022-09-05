#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "KNUET-Gast";
const char *password = "Knuet201";
WiFiClient espClient;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  Serial.println("Connection done.");
}

void loop() {
  // put your main code here, to run repeatedly:

}
