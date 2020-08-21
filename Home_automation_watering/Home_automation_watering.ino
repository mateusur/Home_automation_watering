const char* topic_solenoid = "" // Topic you want to subscribe to 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
  
void reconnect(){
  while(!client.connected()){
    char* clientID = "ESP32_watering";
      if(client.connect(clientID){
        client.subscribe(topic_solenoid);
        }
      else {
        Serial.print("failed, rc=");
        Serial.print(client.state();
        delay(5000);
        }
    }
}
