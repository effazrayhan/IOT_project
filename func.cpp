#define BLYNK_TEMPLATE_ID "****"
#define BLYNK_DEVICE_NAME "****"
#define BLYNK_AUTH_TOKEN "****" 

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 15        
#define DHTTYPE DHT11    
#define SOIL_PIN 34   
#define LDR_PIN 35  

char ssid[] = "iPhoneX"; 
char pass[] = "xoxoxoxo";
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendData() {

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

 
  int soilMoistureValue = analogRead(SOIL_PIN);
  int soilMoisturePercent = map(soilMoistureValue, 4095, 0, 0, 100); 

 
  int ldrValue = analogRead(LDR_PIN);
  int lightLevelPercent = map(ldrValue, 0, 4095, 0, 100); 

  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisturePercent);
  Serial.println(" %");
  
  Serial.print("Light Level: ");
  Serial.print(lightLevelPercent);
  Serial.println(" %");

  
  Blynk.virtualWrite(V0, temperature);         
  Blynk.virtualWrite(V1, humidity);           
  Blynk.virtualWrite(V2, soilMoisturePercent);
  Blynk.virtualWrite(V3, lightLevelPercent);   
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
