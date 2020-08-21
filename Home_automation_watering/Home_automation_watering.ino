#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE 50

const char* ssid = ""; //Your WiFi ssid
const char* password = ""; //Your WiFi password
const char* server_ip = ""; //Sever name or ip(format xxx.xxx.x.x)
int server_port = 1883; //Server port, usually 1883 or 8883
const char* topic_solenoid = ""; // Topic you want to subscribe to 

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(server_ip, server_port);

}

void loop() {
  if(!client.connected())
    reconnect();
  client.loop();

}

void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  delay(500);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if((char)payload[0] =='1'){ //open Solenoid
    }
  else if((char)payload[0] == '0'){ //close Solenoid
    }  
}
void reconnect(){
  char* clientID = "ESP32_watering";
  while(!client.connected()){
      if(client.connect(clientID)){
        client.subscribe(topic_solenoid);
        }
      else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        delay(5000);
        }
    }
}
