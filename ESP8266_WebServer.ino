#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "YourWiFi";
const char* password = "Passowrd";

  IPAddress ip(192,168,1,200);   
  IPAddress gateway(192,168,1,1);   
  IPAddress subnet(255,255,255,0); 
  
ESP8266WebServer server(80);

const int output1 = 14;
const int output2 = 12;
const int output3 = 13;
const int output4 = 15;

boolean device1 = false;
boolean device2 = false;
boolean device3 = false;
boolean device4 = false;

void handleRoot() {

  String cmd;     
      cmd += "<!DOCTYPE HTML>\r\n";
      cmd += "<html>\r\n";    
      cmd += "<head>";
      cmd += "<meta http-equiv='refresh' content='5'/>";
      cmd += "</head>";
      
      if(device1){
        cmd +=("<br/>Device0ON");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device1' value='ON' ></form>");
      }
      else{
        cmd +=("<br/>Device0OFF");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device1' value='OFF' ></form>");
      }
      
      if(device2){
        cmd +=("<br/>Device1ON");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device2' value='ON' ></form>");
      }
      else{
        cmd +=("<br/>Device1OFF");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device2' value='OFF' ></form>");
      }
           
       if(device3){
        cmd +=("<br/>Device2ON");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device3' value='ON' ></form>");
      }
      else{
        cmd +=("<br/>Device2OFF");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device3' value='OFF' ></form>");
      }
      
      if(device4){
        cmd +=("<br/>Device3ON");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device4' value='ON' ></form>");
      }
      else{
        cmd +=("<br/>Device3OFF");
        cmd +=("<form menthod='get'><input class='button' type='submit' name='Device4' value='OFF' ></form>");
      }
           
      cmd += "<html>\r\n";
      server.send(200, "text/html", cmd);
  
if(server.hasArg("Device1")){ // kiểm tra trong chuỗi request từ client gửi về server có chứa dữ liệu với tên Device1 không
  String dev1 = server.arg("Device1"); // Lấy dữ liệu của Device1.
if(dev1 == "OFF") // nếu dữ liệu chứa bằng "OFF"
  digitalWrite(output1, HIGH); //Bật thiết bị 1
  device1 = true;
else
  digitalWrite(output1, LOW); 
  device1 = false;
}
if(server.hasArg("Device2")){ 
  String dev2 = server.arg("Device2");
if(dev2 == "OFF") 
  digitalWrite(output2, HIGH); 
  device2 = true;
else
  digitalWrite(output2, LOW); 
  device2 = false;
}
if(server.hasArg("Device3")){ 
  String dev3 = server.arg("Device3");
if(dev3 == "OFF") 
  digitalWrite(output3, HIGH); 
  device3 = true;
else
  digitalWrite(output3, LOW); 
  device3 = false;
}
if(server.hasArg("Device4")){ 
  String dev4 = server.arg("Device4");
if(dev4 == "OFF") 
  digitalWrite(output4, HIGH); 
  device4 = true;
else
  digitalWrite(output4, LOW); 
  device4 = false;
}  
}

void handleNotFound(){
 
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}

void setup(void){
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);

  digitalWrite(output1, LOW); 
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
   
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  Serial.println("");
  Serial.print("Connected to ");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/socket0On", [](){
    server.send(200, "text/plain", "device1 = ON");
    Serial.println("device1 = ON");
    digitalWrite(output1, HIGH); 
    device1 = true;
  });

  server.on("/socket0Off", [](){
    server.send(200, "text/plain", "device1 = OFF");
    Serial.println("device1 = OFF");
    digitalWrite(output1, LOW); 
    device1 = false;
  });

  server.on("/socket1On", [](){
    server.send(200, "text/plain", "device2 = ON");
    digitalWrite(output2, HIGH); 
    Serial.println("device2 = ON");
    device2 = true;
  });

  server.on("/socket1Off", [](){
    server.send(200, "text/plain", "device2 = OFF");
    digitalWrite(output2, LOW); 
    Serial.println("device2 = OFF");
    device2 = false;
  });

  server.on("/socket2On", [](){
    server.send(200, "text/plain", "device3 = ON");
    digitalWrite(output3, HIGH); 
    Serial.println("device3 = ON");
    device3 = true;
  });

  server.on("/socket2Off", [](){
    server.send(200, "text/plain", "device3 = OFF");
    digitalWrite(output3, LOW); 
    Serial.println("device3 = OFF");
    device3 = false;
  });

  server.on("/socket3On", [](){
    server.send(200, "text/plain", "device4 = ON");
    digitalWrite(output4, HIGH); 
    Serial.println("device4 = ON");
    device4 = true;
  });

  server.on("/socket3Off", [](){
    server.send(200, "text/plain", "device4 = OFF");
    digitalWrite(output4, LOW);
    Serial.println("device4 = OFF"); 
    device4 = false;
  });
    
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
