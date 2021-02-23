#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>
  
const char* ssid = "Rhino";
const char* password =  "Creative007";
int LED_PIN = 14;
int LEDState = 0;         // current state of the led

void setup() {
  Serial.begin(115200);
  
  pinMode (LED_PIN, OUTPUT);

  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  
}

void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
  
    // Toggle LED
  if (LEDState == LOW) {
     digitalWrite(LED_PIN, HIGH);
     LEDState = HIGH;
     }else{
        digitalWrite(LED_PIN, LOW);
             LEDState = LOW;
     }
     
   int httpResponseCode = http.POST("POSTING from ESP32 - " + String(LEDState));   //Send the LED State
   
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(3000);  //Send a request every 3 seconds
  
}