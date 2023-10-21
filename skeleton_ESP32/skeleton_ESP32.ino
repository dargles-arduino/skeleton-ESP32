/**
 * Program: skeleton_ESP32
 * Purpose:
 *   A basic framework for starting any program. This version (v1.0) provides
 *   OLED connectivity via I2C as the ESP32-C3 doesn't seem to like cooperating 
 *   with the Serial.print routines.
 * @author: David Argles, d.argles@gmx.com
 */

/* Program identification */ 
#define PROG    "skeleton_ESP32"
#define VER     "1.0"
#define BUILD   "19oct2023 @ 16:51h"

// Set trace to be false if you don't want diagnostic output to serial port
#define trace true

/* Necessary includes */
#include "flashscreen.h"
#include "OLEDscreen.h"
#include "myWiFi.h"
#include "myTime.h"

/* Global "defines" - may have to look like variables because of type */
#define BAUDRATE 115200     // Baudrate for serial output

/* ----- Initialisation ------------------------------------------------- */

/* Global stuff that must happen outside setup() */
flashscreen flash;
OLEDscreen  screen;
myWiFi      wifi;
myTime      timer;

int led = 5; // BUILTIN_LED doesn't work for ESP32-C3; it's on GPIO8
             // But don't use it, it messes up the OLED

void setup() {
  Serial.begin(BAUDRATE);           // Start up the serial output port
  // Serial.setDebugOutput(true);
  flash.message(PROG, VER, BUILD);  // Send program details to serial output
  screen.begin();                   // Start up the OLED
  screen.banner(PROG, VER, BUILD);

  // Set the built-in led as an output
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); // and turn it off

  // Wait a bit then clear the screen
  delay(2000);
  screen.clear();

  // Start up WiFi
  screen.print("Starting WiFi...\n");
  wifi.start();
  if(wifi.running)
  {
    // Serial.println("WiFi connected");
    screen.print("WiFi connected\n");
    Serial.println(wifi.ipAddr);
  }
  else screen.print("WiFi failed to connect\n");

  // Start up time server
  if(wifi.running)
  {
    timer.sync();
    if(timer.running)screen.print("Time synced\n");
    else screen.print("Time failed to sync\n");
  }
  // put your remaining setup code here, to run once:
  
}

void loop() 
{
  // If we failed to get the WiFi or the time, try again now
  if(!wifi.running) 
  {
    screen.print("No WiFi, trying again\n");
    wifi.start();
  }
  if(wifi.running && !timer.running)
  {
    screen.print("Time not synced, trying again\n");
    timer.sync();
  }

// On the minute, print out the date and time to the serial output
  if(second()==0){
    Serial.print("Time now: ");
    Serial.println(dateTime());
    screen.clear();
    screen.print("\nTime: ");
    screen.print(dateTime());
  }

  delay (1000); // Wait a bit
  
  digitalWrite(led, !digitalRead(led)); // And toggle the built-in LED on or off
}
