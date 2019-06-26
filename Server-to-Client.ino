#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Configuration parameters for Access Point
char * ssid_ap = "";                // SSID name
char * password_ap = "";            // SSID password
IPAddress ip(192,168,11,4);         // arbitrary IP address (doesn't conflict w/ local network)
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);

// Set up the server object
ESP8266WebServer server;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(ssid_ap,password_ap);
  // Print IP Address as a sanity check
  Serial.begin(115200);
  Serial.println("CLEARSHEET");
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Temperature");
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
  // Configure the server's routes
  server.on("/",handleIndex); // use the top root path to report the last sensor value
  server.begin();
}

void loop() {
  server.handleClient();
}

float gen_ran() {
  float val = float(random(40,100));  
  //Serial.print(val);
  return val;
}

void handleIndex() {
  String temp = "Temperatue : ";
  Serial.println();
  String temp1 = String(gen_ran());
  server.send(200,"text/plain",temp + temp1);
  Serial.print("DATA,TIME,");                   // for EXCEL log 
  Serial.println(temp1);
  delay(100);
}
