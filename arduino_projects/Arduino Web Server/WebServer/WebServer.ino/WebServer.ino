/*
  Web Server

 A simple web server that displays a landing page.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 modified 23 Apr 2018
 by John deGuise
 */

#include <SPI.h>
#include <Ethernet.h>
#include <time.h>

byte mac[] = {0xDF, 0xAE, 0xDE, 0xEB, 0xAF, 0xFA};
IPAddress ip(192, 168, 0, 178);
EthernetServer server(80);

long count = 0;
char rx_byte = 0;
String STYLE_TAG = "<style type='text/css'>body {font-family: Georgia, \'Times New Roman\', Times, serif; color: purple; background-color: lightgrey;} #landing-page-welcome, #picture-container, #count-string {text-align: center;}</style>";
String PAGE_HEADING = "";
String PAGE_TITLE = "";
//String FAVICON = "<link rel='shortcut icon' type='image/x-icon' href='file://localhost/Users/GOOSE/Desktop/favicon.ico'/>";

String formatPageTitle(String titleInput) {return "<title>" + titleInput + "</title>";}

void startServer() {
  Serial.begin(9600);
  while (!Serial);
  
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void initializeServerVars() {
  while(!Serial.available()) {Serial.println("Please enter title of page!"); delay(1000);}
  while(Serial.available()) {rx_byte = Serial.read(); if (rx_byte != '\n') {PAGE_HEADING += rx_byte;}}
  Serial.println("Setting title to : " + PAGE_HEADING);
  
  PAGE_TITLE = formatPageTitle(PAGE_HEADING);  
}
void setup() {
  startServer();
  initializeServerVars();
}

void writeTimeTaken(EthernetClient client) {
  client.println("<p>Time taken: approx. " + String(count / 30) + " minutes.</p>");
}

void setupHTMLMetadata(EthernetClient client){
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");  
}

void setupHead(EthernetClient client) {
  client.println("<head>");
  client.println(PAGE_TITLE);
  client.println(STYLE_TAG);
//  client.println(FAVICON);
  client.println("</head>");
}

void setupBody(EthernetClient client, String countString) {  
  String MAIN_IMAGE = "<img src='http://animalsbirds.com/wp-content/uploads/2017/04/Goose-Bird-wallpaper.jpg'/>";
  client.println("<body>");
  client.println("<div><h1 id='landing-page-welcome'><hr/>");
  client.println(PAGE_HEADING);
  client.println("</h1></div><br/>");
  client.println("<div id='picture-container'>");
  client.println(MAIN_IMAGE);
  client.println("</div>");
//  client.println("<p id='count-string'>");
//  client.println(countString);
//  client.println("</p>");
//  client.println("<p>");
//  writeTimeTaken(client);
//  client.println("</p>");
//  client.println(JS_TO_EXECUTE);
  client.println("</body>");
}

void buildHTML(EthernetClient client, String countString, String JS_TO_EXECUTE) {
  setupHTMLMetadata(client);
  
  client.println("<html>");
  setupHead(client);
  setupBody(client, countString);
  client.println("</html>");
  return;
}

void loop() {
  String countString = "Count is up to: " + String(count);
  String JS = "<script>console.log('" + String(countString) + "');</script>";
  EthernetClient client = server.available();
  
  if (client) {
    boolean currentLineIsBlank = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n' && currentLineIsBlank) {
          buildHTML(client, countString, JS);
          count++;
          break;
        }
        if (c == '\n') {currentLineIsBlank = true; /* you're starting a new line */}
        else if (c != '\r') {currentLineIsBlank = false; /* you've gotten a character on the current line */}
      }
    }
    client.stop();
  }
}
