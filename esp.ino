#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <Arduino_JSON.h>

WiFiClient client;
HTTPClient http;

int wifiCount;
String payload;
String str;
String state;
String dir;
int httpResponseCode;
//const char* urlString = "http://172.28.131.66:8090/direction?";
const char* urlString = "http://192.168.43.240:8090/direction";
//const char* urlString = "http://192.168.43.240:8090/direction"; // main
//const char* urlString = "http://192.168.43.240:8090/direction"; // habd


// set pin numbers
int ard_7 = 4;     // D2 on esp and to 7 in arduino
int ard_8 = 5;     // D1 on esp and to 8 in arduino
int mod = 12; // d6

//  char * username = "KhaledDodo";
//  char * password = "veto939599";
//char * username = "STUDBME2";
//char * password = "BME2Stud";
  char * username = "Mikasa";
  char * password = "mnnymnny";

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

// habd start
String httpGETRequest(const char* urlString) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, urlString);

  // Send HTTP POST request
  int httpResponseCode = http.GET();
  Serial.println("fn ");
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    //    Serial.print("payload: ");
    //    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

// end habd


void loop()
{
  // start habd
  delay (750);
  String response;
  String responseArr[2];

  response = httpGETRequest(urlString);
  JSONVar myObject = JSON.parse(response);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  //  Serial.print("JSON object = ");
  //  Serial.println(myObject);

  //  Serial.print("mode = ");
  //  Serial.println(myObject[0]);
  //  Serial.print("dir = ");
  //  Serial.println(myObject[1]);

  state  = myObject[0];

  if ( state == "Automatic") // automatic
  {
    digitalWrite(mod, LOW);
    Serial.println("Automatic");
  }
  else if ( state == "Manual") // manual
  {
    digitalWrite(mod, HIGH);
    Serial.println("manual");
  }


  dir = myObject[1];

  Serial.print("dir = ");
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
