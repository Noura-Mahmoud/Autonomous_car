#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

WiFiClient client;
HTTPClient http;

int wifiCount;
String payload;
String str;
String state;
String dir;
int httpResponseCode;
//String urlString = "http://172.28.132.122:8090/direction?";
String urlString = "http://192.168.1.105:8090/direction?";
//char * urlString = "http://192.168.1.105:8090/direction";


// set pin numbers
int ard_7 = 4;     // D2 on esp and to 7 in arduino
int ard_8 = 5;     // D1 on esp and to 8 in arduino
int mod = 12; // d6

  char * username = "KhaledDodo";
  char * password = "veto939599";
//char * username = "STUDBME2";
//char * password = "BME2Stud";

void setup() {
  // initialize ard pins as output
  pinMode(ard_7, OUTPUT);
  pinMode(ard_8, OUTPUT);
  pinMode(mod, OUTPUT);

  Serial.begin(115200);
  Serial1.begin(115200);
  delay(2000);

  WiFi.begin(username, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    wifiCount++;
    if (wifiCount == 20) {
      wifiCount = 0;

    }
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  delay(500);
}

void loop()
{ 
//  http.begin(client, urlString);
  http.begin(client, urlString.c_str());
  // Your Domain name with URL path or IP address with path
  httpResponseCode = http.GET();
  if (httpResponseCode > 0)
  {
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
    Serial.println("payload = ");
    Serial.println(payload);

    state  = payload[0];

    if ( state == "Automatic") // automatic
    {
      digitalWrite(mod, LOW);
      Serial.println("Automatic");
    }
    else if ( state != "Automatic") // manual
    {
      digitalWrite(mod, HIGH);
      Serial.println("manual");
    }

    
    dir = payload[1];

    Serial.println("dir = ");
    Serial.println(dir);

    if ( dir == "F") // f
    {
      digitalWrite(ard_7, LOW);
      digitalWrite(ard_8, LOW);
    }
    else if ( dir == "R") // r
    {
      digitalWrite(ard_7, HIGH);
      digitalWrite(ard_8, LOW);
    }
    else if ( dir == "B") // b
    {
      digitalWrite(ard_7, LOW);
      digitalWrite(ard_8, HIGH);
    }
    else if ( dir == "L") // l
    {
      digitalWrite(ard_7, HIGH);
      digitalWrite(ard_8, HIGH);
    }
  }
//  else
//  {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//  }
  http.end();
  delay(1500);
}