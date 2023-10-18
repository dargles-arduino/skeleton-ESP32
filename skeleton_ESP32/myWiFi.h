/**
 * Class definition for myWiFi
 * 
 * The myWiFi class provides a unified approach for connecting to WiFi - it needs to be 
 * different depending on which chip you're using. This class will need to be altered 
 * to suit different chips.
 * 
 * @author  David Argles, d.argles@gmx.com
 * @version 15Dec2021 16:40h
 */
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Set these for your local AP details
const char  *ssid     = "mySSID";
const char  *password = "12348765";

bool        serverWaiting = false;
String      serverMessage = "Hello World!\n";

WiFiServer server(80);

  /* Just a little test message.  Go to http://192.168.4.1 in a web browser
     connected to this access point to see it.
  */
  void handleRoot() 
  {
    //server.send(200, "text/html", serverMessage);
    return;
  }



class myWiFi
{
  private:
   
  public:
  bool  running = false;

  /**
   * start
   * Starts up the WiFi
   */
  IPAddress start()
  {
    // *** Start up the WiFi ***
    if(trace)Serial.print("Starting up WiFi");
    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    if(trace)
    {
      Serial.print("AP IP address: ");
      Serial.println(myIP);
    }

    // Now start up the (web)server
    server.begin();
    if(trace)Serial.println("Server started");

    return(myIP);    
  }

  void handleRequests()
  {
    WiFiClient client = server.available();   // listen for incoming clients

    if (client) 
    {                                          // if you get a client,
      if(trace)Serial.println("New Client.");  // print a message out the serial port
      String currentLine = "";                 // make a String to hold incoming data from the client
      while (client.connected()) 
      {                                        // loop while the client's connected
        if (client.available()) 
        {                                      // if there's bytes to read from the client,
          char c = client.read();              // read a byte, then
          if(trace)Serial.write(c);            // print it out the serial monitor
          if (c == '\n') 
          {                                    // if the byte is a newline character
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) 
            {
              // The HTTP response ends with another blank line:
              client.println(serverMessage);
              // break out of the while loop:
              break;
            }
            else 
            {    // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          } 
          else if (c != '\r') 
          {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
        }
      }
      // close the connection:
      client.stop();
      if(trace)Serial.println("Client Disconnected.");
    }
  }
};
