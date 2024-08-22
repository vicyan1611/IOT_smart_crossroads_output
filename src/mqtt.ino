#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

//***Set server***
const char* mqttServer = "mqtt.noboroto.id.vn"; 
int port = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void mqttSetup() {
  Serial.print("Connecting to WiFi");

  wifiConnect();
  mqttClient.setServer(mqttServer, port);
  mqttClient.setCallback(callback);
  mqttClient.setKeepAlive( 90 );
}

void wifiConnect() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void mqttConnect() {
  while(!mqttClient.connected()) {
    Serial.println("Attemping MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if(mqttClient.connect(clientId.c_str(), "ptvinh", "ptvinh")) {
      Serial.println("connected");

      //***Subscribe all topic you need***
      mqttClient.subscribe("/iot/walker");
      mqttClient.subscribe("/iot/cars");
      mqttClient.subscribe("/iot/watering");
      mqttClient.subscribe("/iot/trafficlight");
    }
    else {
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.println(topic);
  String strMsg;
  for(int i=0; i<length; i++) {
    strMsg += (char)message[i];
  }
  String strTopic(topic);
  
  //Serial.println(strMsg);

  //***Code here to process the received package***
  if (strTopic == "/iot/walker")
    handleLightWalker();
  if (strTopic == "/iot/cars")
    handleCarFlow(strMsg);
  if (strTopic == "/iot/watering")
    handleRelay(strMsg);
  if (strTopic == "/iot/trafficlight")
    handleTrafficLight(strMsg);
}

void publishData(String topic, String message) {
  const char* caTopic = topic.c_str();
  const char* caMessage = message.c_str();
  mqttClient.publish(caTopic, caMessage);
}

void mqttLoop() {
  if(!mqttClient.connected()) {
    mqttConnect();
  }
  mqttClient.loop();
}