
#include <WiFi.h>
#include <PubSubClient.h>


// WiFi
const char *ssid = "mousse"; // Enter your WiFi name
const char *password = "qweqweqwe";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
void setup(){
	// Set software serial baud to 115200;
	Serial.begin(115200);
	// connecting to a WiFi network
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
	    delay(500);
	    Serial.println("Connecting to WiFi..");
	}
}
void loop(){

	if(SensorAlert(){
		client.setServer(mqtt_broker, mqtt_port);
		client.setCallback(callback);
		while (!client.connected()) {
		    String client_id = "esp32-client-";
		    client_id += String(WiFi.macAddress());
		    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
		    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
			Serial.println("Public emqx mqtt broker connected");
		    } else {
			Serial.print("failed with state ");
			Serial.print(client.state());
			delay(2000);
		    }
		}
	}
}

