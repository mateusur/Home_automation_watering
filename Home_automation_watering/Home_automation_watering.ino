
//#include <WiFi.h> // Use with esp32
#include <ESP8266WiFi.h>  // Use with esp8266
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define MSG_BUFFER_SIZE 50
#define SOLENOID 5
//

const char* ssid = ""; //Your WiFi ssid
const char* password = ""; //Your WiFi password
const char* server_ip = ""; //Sever name or ip(format xxx.xxx.x.x)
int server_port = 1883; //Server port, usually 1883 or 8883
const char* topic_solenoid = "garden/watering/solenoid"; // Topic you want to subscribe to
const char* topic_watering = "garden/watering/watered";
const char* topics_solenoid[7] = { "garden/watering/solenoid/sunday", "garden/watering/solenoid/monday", "garden/watering/solenoid/tuesday", "garden/watering/solenoid/wednesday"
                                   , "garden/watering/solenoid/thursday", "garden/watering/solenoid/friday", "garden/watering/solenoid/saturday"};
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
const int ledPin =  2;
//Watering for peroid of time
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
bool operational = false;
unsigned long interval = 1000;
//Colling down solenoid
unsigned long previousMillis2 = 0;
bool cold = true;
const unsigned long cooldown_interval = 300000; // 5min
//Time
const long utcOffsetInSeconds = 7200;
unsigned long previousMillis3 = 0;
char timing[7][5] = { "0000", "0000", "0000", "0000", "0000", "0000", "0000" };
int today = -1; //day of the week, sunday is 0
bool watered = false;
char watered2='0';
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(server_ip, server_port);
  client.setCallback(callback);
  timeClient.begin();
  pinMode(SOLENOID, OUTPUT);
  pinMode(ledPin, OUTPUT);
  today = timeClient.getDay();
}

void loop() {
  if (!client.connected())
    reconnect();
  client.loop();

  currentMillis = millis();
  if (cold == false && currentMillis - previousMillis2 >= cooldown_interval) {
    cold = true;
    operational = false;
    Serial.println("COLD");
  }
  if ( cold && operational && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    previousMillis2 = currentMillis;
    digitalWrite(ledPin, LOW);
    digitalWrite(SOLENOID, LOW);
    operational = false;
    cold = false;
    Serial.println("HOT");
  }
  timeClient.update();

  if (timeClient.getDay() != today) {
    if(today != -1)
      client.publish(topic_watering, "0",true);
    today = timeClient.getDay();
    watered = false;
  }
  switch (today) {
    case 0: //sunday
      if (watered2 == '0' && (int)timing[0][0] == 1 && timeClient.getHours() >= (int)timing[0][1] && timeClient.getMinutes() >= (int)timing[0][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[0][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
    case 1:
      if (watered2 == '0' && (int)timing[1][0] == 1 && timeClient.getHours() >= (int)timing[1][1] && timeClient.getMinutes() >= (int)timing[1][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[1][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
    case 2:
      if (watered2 == '0' && (int)timing[2][0] == 1 && timeClient.getHours() >= (int)timing[2][1] && timeClient.getMinutes() >= (int)timing[2][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[2][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
    case 3:
      if (watered2 == '0' && (int)timing[3][0] == 1 && timeClient.getHours() >= (int)timing[3][1] && timeClient.getMinutes() >= (int)timing[3][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[3][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }

      }
      break;
    case 4:
      if (watered2 == '0' && (int)timing[4][0] == 1 && timeClient.getHours() >= (int)timing[4][1] && timeClient.getMinutes() >= (int)timing[4][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[4][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
    case 5:
      if (watered2 =='0'  && (int)timing[5][0] == 1 && timeClient.getHours() >= (int)timing[5][1] && timeClient.getMinutes() >= (int)timing[5][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[5][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
    case 6:
      if (watered2 == '0' && (int)timing[6][0] == 1 && timeClient.getHours() >= (int)timing[6][1] && timeClient.getMinutes() >= (int)timing[6][2]) {
        if (cold) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(SOLENOID, HIGH);
          previousMillis = millis();
          interval = (int)timing[1][3] * 1000 * 60;
          operational = true;
          watered = true;
          client.publish(topic_watering, "1",true);
        }
      }
      break;
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String watering_time = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    Serial.print(" ");
  }
  Serial.println();
  for (int i = 0; i < length; i++) {
    Serial.print(payload[i]);
    Serial.print(" ");
  }

  Serial.println();
  if ( strcmp(topic, topic_solenoid) == 0) {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      watering_time += (char)payload[i];
    }
    operational = true;
    if (cold) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(SOLENOID, HIGH);
    }
    previousMillis = millis();
    interval = watering_time.toInt() * 1000 * 60;

  }
  if(strcmp(topic, topic_watering) ==0){
     for (int i = 0; i < length; i++) {
       watered2 = (char)payload[i]; 
    }
    if(watered2=='1')
    Serial.println("porownanie dziala");
    }
  if (strcmp(topic, topics_solenoid[0]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[0][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[1]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[1][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[2]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[2][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[3]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[3][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[4]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[4][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[5]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[5][i] = (char)payload[i];
    }
  }
  if (strcmp(topic, topics_solenoid[6]) == 0) {
    for (int i = 0; i < 4; i++) {
      timing[6][i] = (char)payload[i];
    }
  }
}

void reconnect() {
  char* clientID = "ESP8266_watering";
  while (!client.connected()) {
    if (client.connect(clientID)) {
      client.subscribe(topic_solenoid, 0);
      client.subscribe(topic_watering, 0);
      for (int i = 0; i < 7; ++i)
        client.subscribe(topics_solenoid[i], 0);
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
