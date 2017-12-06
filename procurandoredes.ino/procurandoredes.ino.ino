#include <ESP8266WiFi.h>

const char* ssid= "virus";
const char* password = "lindinha";

 WiFiServer server(3000);
 
void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(14,OUTPUT);
  digitalWrite(14,0);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected

  Serial.println("conectando com ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while ( WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("..");
  }
  Serial.println("..");
  Serial.println("Conectado");

  server.begin();
  Serial.println("Comecando servidor:");
  
  Serial.println(WiFi.localIP());
  
}

void loop() {
  WiFiClient client = server.available();
  if (!client){
    return;
  }

  Serial.println("novo cliente");
  while(!client.available()){
    delay(1);
   }
   
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val;
  if(req.indexOf("/gpio/0")!= -1){
    Serial.println("val igual a zero");
    val=0;
    Serial.println("desligando porta 14 ");
    digitalWrite(14, val);
  }

  if (req.indexOf("/gpio/1")!= -1){
    Serial.println("val igual a um");
    val=1;
    Serial.println("ligando porta 14 ");
    digitalWrite(14, val);
  }
  /*
  else {
    Serial.println("chamada invalida");
    client.stop();
    return;
    }
    */
  
  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s =+ (val)?"high":"low";
  s =+ "</html>\n";
  client.print(s);
  delay(1);
   Serial.println("cliente fora");
}
