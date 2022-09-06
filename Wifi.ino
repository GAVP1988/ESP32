#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "KNUET-Gast";
const char *password = "Knuet201";
WiFiClient espClient;

const char *mqttBrocker = "139.13.210.118";
const char *topic = "esp32/jade";
const char *mqttUsername = "";
const char *mqttPassword = "";
const int mqttPort = 1883;
PubSubClient client(espClient);



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
  client.setServer(mqttBrocker, mqttPort);
  client.setCallback(callback);
  while(!client.connected()){
    String clientID = "Guilherme";
    clientID += String(WiFi.macAddress());
    Serial.printf("The %s tries to connect to mqtt brocker...\n",clientID.c_str());
    if(client.connect(clientID.c_str(), mqttUsername, mqttPassword)){
      Serial.println("mqtt brocker connected");
    }
    else {
      Serial.print("mqtt connection failed");
      Serial.println(client.state());
      delay(2000);
    }
  }

  client.publish(topic, "Hi EMQX brocker I'm a ESP32 :)");
  client.subscribe(topic);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
}

void callback(char *topic, byte *payload, unsigned int length){
  
  Serial.print("Message received in topic: ");
  Serial.println(topic);
  Serial.print("The message is: ");
  
  for(int i=0;i<length; i++){
    Serial.print((char) payload[i]);
  }
  
  Serial.println();
  Serial.println("-+-+-+End+-+-+-+");
}
