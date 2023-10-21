/**
 * Class definition for myWiFi
 * 
 * The myWiFi class provides a unified approach for connecting to WiFi - it needs to be 
 * different depending on which chip you're using. This class will need to be altered 
 * to suit different chips.
 * 
 * @author  David Argles, d.argles@gmx.com
 * @version 19oct2023 23:00h
 */

#include <WiFi.h>
// #include <WiFiClient.h>
// #include <WiFiAP.h>

// Set these for your local AP details
const char  *ssid     = "mySSID";
const char  *password = "12348765";

class myWiFi
{
  private:
   
  public:
  bool         running = false;
  IPAddress    ipAddr = -1;

  /**
   * start
   * Starts up the WiFi
   */
  void start()
  {
    WiFi.begin(ssid, password);
    int tries = 5;
    while((WiFi.status() != WL_CONNECTED) && (tries>0))
    {
      delay(500);
      tries--;
    }
    if(WiFi.status()==WL_CONNECTED)
    {
      running = true;
      ipAddr = WiFi.localIP();
    } 
    else running = false;
    return;    
  }

};
