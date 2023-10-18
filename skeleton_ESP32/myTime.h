/**
 * Class definition for myTime
 * The myTime class provides a front end for Rop Gonggrijp's ezTime library.
 * NOTES: 
 * - Don't keep this code in unless you need it - it's useful, but takes up a lot of 
 *     memory.
 * - This requires a working WiFi connection to be established first.
 * - The ezTime library provides the following functions:
 *     year(), month(), day(), hour(), minute(), second(), dateTime().
 *   I -think- that's it...
 * 
 * @author  In this form, David Argles, d.argles@gmx.com. But really, all the hard work 
 *          has been done by Rop Gonggrijp. You'll have to install his ezTime library in 
 *          tools->manage libraries.
 * @version 24Dec2021 17:07h
 */

// The next line sets up the time server (ezTime)
#include <ezTime.h>

class myTime
{
  public:
  bool  running = false;

  /**
   * connect
   * Starts up the WiFi
   */
  void sync()
  {
    // *** Start up the time client ***
    if(trace)Serial.print("Syncing up time: ");
    waitForSync(7);
    if(timeStatus()==timeSet)
    {
      running = true;
      if(trace)Serial.println("time synced");
    }
    else if(trace)Serial.println("failed to sync time");  
    return;    
  }
};
