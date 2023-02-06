// Librerias a utilizar
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>
// inicializar a la esp32 como cliente MQTT (Mosquitto)
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
// variables de operación
float temperatura_sensor1 = 0;
float humedad_sensor1 = 0;
float temperatura_sensor2 = 0;
float humedad_sensor2 = 0;
float gas_Sensor1 = 0;
float gas_Sensor2 = 0; 
// definir nombres de puertos salidas y entradas
const int Lamp1 = 4;
const int Lamp2 = 0;
const int Lamp3 = 2;
const int Lamp4 = 15;
const int Lamp5 = 12;
const int Lamp6 = 14;
const int chapa = 27;
const int ventilador = 13;
const int sensorGas1 = 34;
const int sensorGas2 = 35;
const int sensorDHT1 = 25;
const int sensorDHT2 = 26;
DHT dht1(sensorDHT1, DHT22);
DHT dht2(sensorDHT2, DHT22);
// ======================
// SSID / Pasword de nuestro modem de internet
const char* ssid = "INFINITUM1455";
const char* password = "b6ksnu2YNd";
// dirección broker MQTT
const char* mqtt_server = "192.168.1.74";
// ***************** VOID SETUP ***************
void setup() {
 Serial.begin(115200);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 pinMode(Lamp1, OUTPUT);
 pinMode(Lamp2, OUTPUT);
 pinMode(Lamp3, OUTPUT);
 pinMode(Lamp4, OUTPUT);
 pinMode(Lamp5, OUTPUT);
 pinMode(Lamp6, OUTPUT);
 pinMode(ventilador, OUTPUT);
 pinMode(chapa, OUTPUT);
 dht1.begin();
 dht2.begin();
}
// ***** VOID SETUP_WIFI() ***********
void setup_wifi(){
 delay(10);
 Serial.println();
 Serial.print("Conectando a ");
 Serial.println(ssid);
 WiFi.begin(ssid,password);
 while(WiFi.status() != WL_CONNECTED){
 delay(500);
 Serial.print("."); 
 }
 Serial.println("");
 Serial.println("WiFi Conectado");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* message, unsigned int 
length){
 Serial.print("Mensaje recibido en topic");
 Serial.print(topic);
 Serial.print(", Message: ");
 String messageTemp;
 for(int i = 0;i < length; i++){
 Serial.print((char)message[i]);
 messageTemp += (char)message[i]; 
 }
 Serial.println();
 // instrucciones de ejecución
 // ======= 1 ================
 if (String(topic) == "esp32/output1"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp1, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp1, LOW);
 }
 }
 // ==============================
 // ======= 2 ================
 if (String(topic) == "esp32/output2"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp2, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp2, LOW);
 }
 }
 // ==============================
 // ======= 3 ================
 if (String(topic) == "esp32/output3"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp3, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp3, LOW);
 }
 }
 // ==============================
 // ======= 4 ================
 if (String(topic) == "esp32/output4"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp4, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp4, LOW);
 }
 }
 // ==============================
 // ======= 5 ================
 if (String(topic) == "esp32/output5"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp5, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp5, LOW);
 }
 }
 // ==============================
 // ======= 6 ================
 if (String(topic) == "esp32/output6"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(Lamp6, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(Lamp6, LOW);
 }
 }
 // ==============================
 // ======= 6 ================
 if (String(topic) == "esp32/output7"){
 Serial.print("Cambio de salida");
 if(messageTemp == "on"){
 Serial.println("on");
 digitalWrite(chapa, HIGH);
 }
 if(messageTemp == "off"){
 Serial.println("off");
 digitalWrite(chapa, LOW);
 }
 }
// se pueden agregar mas instrucciones 
}
// *************** VOID RECONNECT ***********
void reconnect(){
 while(!client.connected()){
 Serial.print("Intentando conexion MQTT...");
 if(client.connect("ESP8266Client")){
 Serial.println("conectado");
 client.subscribe("esp32/output1"); 
 client.subscribe("esp32/output2");
 client.subscribe("esp32/output3");
 client.subscribe("esp32/output4");
 client.subscribe("esp32/output5");
 client.subscribe("esp32/output6");
 client.subscribe("esp32/output7");
 } else{
 Serial.print("Fallo, rc = ");
 Serial.print(client.state());
 Serial.println(" Intentelo de nuevo en 5s ");
 delay(5000); 
 }
 }
}
// ejecución del prograna
void loop() {
 if(!client.connected()){
 reconnect();
 }
 client.loop();
 long now = millis();
 if(now - lastMsg > 100){
 lastMsg = now;
 // lecturas sensores dht22
 temperatura_sensor1 = dht1.readTemperature();
 humedad_sensor1 = dht1.readHumidity();
 temperatura_sensor2 = dht2.readTemperature();
 humedad_sensor2 = dht2.readHumidity();
 // lecturas sensor gas
 gas_Sensor1 = analogRead(sensorGas1);
 gas_Sensor2 = analogRead(sensorGas2);
 if(gas_Sensor1 > 3000 || gas_Sensor2 > 3000){
 digitalWrite(ventilador,HIGH);
 } else {
 digitalWrite(ventilador,LOW);
 }
 // conversion sensores dht22
 char tempString1[8];
 dtostrf(temperatura_sensor1, 1, 2, tempString1);
 Serial.print("Temperatura1: ");
 Serial.println(tempString1);
 client.publish("esp32/temperature", tempString1);
 char tempString2[8];
 dtostrf(temperatura_sensor2, 1, 2, tempString2);
 Serial.print("Temperatura2: ");
 Serial.println(tempString2);
 client.publish("esp32/temperature2", tempString2);
 char humString1[8];
 dtostrf(humedad_sensor1, 1, 2, humString1);
 Serial.print("Humedad1: ");
 Serial.println(humString1);
 client.publish("esp32/humidity", humString1);
 char humString2[8];
 dtostrf(humedad_sensor2, 1, 2, humString2);
 Serial.print("Humedad2: ");
 Serial.println(humString2);
 client.publish("esp32/humidity2", humString2);
 // conversion sensores gas
 char gasString1[8];
 dtostrf(gas_Sensor1, 1, 2, gasString1);
 Serial.print("Gas1: ");
 Serial.println(gasString1);
 client.publish("esp32/gas1", gasString1);
 char gasString2[8];
 dtostrf(gas_Sensor2, 1, 2, gasString2);
 Serial.print("Gas2: ");
 Serial.println(gasString2);
 client.publish("esp32/gas2", gasString2);
 }
}
