/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/Documents/CTD_2023/Labs/Lab7/src/Lab7.ino"
#include "env.h"
#include "blynk.h"
#include "oled-wing-adafruit.h"
#include "basicLibrary.ino" // Custom class mentioned below

void setup();
void loop();
void printToOled(String msg);
#line 6 "/Users/admin/Documents/CTD_2023/Labs/Lab7/src/Lab7.ino"
#define tempMonitorPin A4
#define BUTTON_A_CLICKED_MSG "Temperature Alert!"
#define BUTTON_A_CLICKED_EVENT "bA_clicked"

SYSTEM_THREAD(ENABLED)

OledWingAdafruit display;

Temperature tempMonitor; // A class for the temperature sensor

void setup()
{
  tempMonitor.initialize(tempMonitorPin); // Using Custom Class to Read Sensors, LEDS, etc.

  Blynk.begin(BLYNK_AUTH_TOKEN);

  display.setup();
  display.clearDisplay();
  display.display();
}
void loop()
{
  update(); // This is the classes update
  Blynk.run();
  display.loop();
  if (display.pressedA())
  {
    Blynk.logEvent(BUTTON_A_CLICKED_EVENT, BUTTON_A_CLICKED_MSG);
    printToOled("Sent Notification");
    delay(3000);
  }
  Blynk.virtualWrite(V0, tempMonitor.fahrenheit);
  printToOled((String)tempMonitor.fahrenheit); // One of the values of the Temperature class
}

void printToOled(String msg)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
}