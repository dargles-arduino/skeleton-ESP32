/**
 * Program: skeleton
 * Purpose:
 *   A basic framework for starting any program. This version (v2.0) aims to 
 *   provide WiFi and time functionality without clogging up the main sketch.
 *   It also adds in OLED connectivity via I2C as the ESP32-C3 doesn't seem 
 *   to like cooperating with the Serial.print routines.
 * @author: David Argles, d.argles@gmx.com
 */

/* Program identification */ 
#define PROG    "skeleton-ESP32"
#define VER     "1.0"
#define BUILD   "18oct2023 @14:46h"

// Set trace to be false if you don't want diagnostic output to serial port
#define trace true

/* Necessary includes */
#include "flashscreen.h"
#include "myWiFi.h"
#include "myTime.h"

/* Global "defines" - may have to look like variables because of type */
#define BAUDRATE 115200     // Baudrate for serial output

/* ----- Initialisation ------------------------------------------------- */

/* Global stuff that must happen outside setup() */
flashscreen flash;
myWiFi      wifi;
//myTime      timer;

void setup() {
  Serial.begin(BAUDRATE);           // Start up the serial output port
  // Serial.setDebugOutput(true);
  flash.message(PROG, VER, BUILD);  // Send program details to serial output

  // Set the built-in led as an output
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW); // and turn it off

  // Start up WiFi
  IPAddress ip = wifi.start();
  Serial.print("WiFi started with IP: ");
  Serial.println(ip);

  // Start up time server
  //if(wifi.connected)timer.sync();

  // put your remaining setup code here, to run once:
  
}

void loop() 
{
  // If we failed to get the WiFi or the time, try again now
  //if(!wifi.connected) wifi.connect();
  //if(wifi.connected && !timer.running) timer.sync();
  
  // Handle any web requests
  wifi.handleRequests();

// On the minute, print out the date and time to the serial output
  /*if(second()==0){
    Serial.print("Time now: ");
    Serial.println(dateTime());
  }*/

  delay (1000); // Wait a bit
  
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED)); // And toggle the built-in LED on or off
}
