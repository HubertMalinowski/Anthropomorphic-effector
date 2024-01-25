#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "Orange_Swiatlowod_0880";       // Nazwa sieci WiFi
const char* password = "wZDwL7NZChG3d4RH4H";         // Hasło sieci WiFi

const char* mqtt_server = "192.168.1.128";      // Adres brokera MQTT
const int mqtt_port = 1883;                          // Port brokera MQTT
const char* mqtt_topic = "Array_of_fingers";             // Nazwa tematu MQTT

WiFiClient espClient;
PubSubClient client(espClient);

Servo Fingers[5]; //Tablica serwomechanizmów

int servoPins[5] = {14, 15, 4, 13, 2}; // Piny, do których są podłączone serwomechanizmy

void setup() {
  Serial.begin(115200);

// Podłączenie serwomechanizmów do odpowiednich pinów
  for (int i = 0; i < 5; i++) {
    Fingers[i].attach(servoPins[i]);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Łączenie z siecią WiFi...");
  }

  Serial.println("Połączony z siecią WiFi");
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Wiadomość MQTT odebrana:");

  for (unsigned int i = 0; i < 5; i++) {
    if(payload[i+1]==49){
        Fingers[i].write(170);
      }else{
        Fingers[i].write(10); 
        }
        
    Serial.print(payload[i]);
    Serial.print(" ");
  }

  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Łączenie z MQTT brokerem...");

    if (client.connect("arduino_client")) {
      Serial.println("połączony");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("niepowodzenie, kod błędu: ");
      Serial.print(client.state());
      Serial.println(" próba ponownego połączenia za 5 sekund");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}
