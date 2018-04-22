/*
  Web Server

 A simple web server that shows the value of the analog input pins.
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

 */

#include <SPI.h>
#include <Ethernet.h>
#include <time.h>
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  // some variation of randomized mac address, e.g. 0xDF, 0xAF, 0xDD, 0xEB, 0xAA, 0xFC
};
IPAddress ip(internal_ip_of_your_choice);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
int count = 0;
String style = "<style type=\"text/css\">body {font-family: Georgia, \"Times New Roman\", Times, serif; color: purple; background-color: lightgrey;} #landing-page-welcome, #picture-container {text-align: center;}</style>";
String MAIN_HEADER = "Goose's Internal Server";
String MAIN_IMAGE = "http://animalsbirds.com/wp-content/uploads/2017/04/Goose-Bird-wallpaper.jpg";
//clock_t start = clock(), diff;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void incrementCount() {
  count++;
}

void writeTimeTaken(String countString, EthernetClient client) {
  client.print(countString + "<br/>");
  client.print("Time taken: approx. " + String(count / 22) + " minutes.");
}

void writeOutput(String countString, EthernetClient client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>" + style + "</head>");
  client.println("<body>");
  client.println("<div><h1 id='landing-page-welcome'><hr>" + MAIN_HEADER + "</hr></h1></div><br/>");
  client.print("<div id='picture-container'><img src='" + MAIN_IMAGE + "'/></div><br/>");
  writeTimeTaken(countString, client);
  client.println("</body>");
  client.println("</html>");
  return;     
}

void loop() {
  // listen for incoming clients
  String countString = "Count is up to: " + String(count);
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          writeOutput(countString, client);
          incrementCount();
          // output the value of each analog input pin
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
