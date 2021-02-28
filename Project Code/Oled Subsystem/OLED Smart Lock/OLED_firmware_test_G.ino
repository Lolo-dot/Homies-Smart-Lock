/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 
 MODIFIED by Steven for smart lock OLED capstone project
 OLED splash screen and setup blinks. Oled and led respond to door state
 Blynk app includes terminal, button (lock/unlock), value display ( of lock status)
 and a superchart (of server data history)
 **************************************************************************

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT SwSerial

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default arduino case commented):
//Modified with stm32 pinouts (PB7,PA6 etc)
#define OLED_MOSI  PB7//9
#define OLED_CLK   PB8//10 
#define OLED_DC    PA6//11 
#define OLED_CS    PB12//12
#define OLED_RESET PA7//13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0gdWBq9y8A34bYUgV5XthEu5UnpSAsqE";

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);
BlynkTimer timer;  //blynk timer

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();

}

void myTimerEvent(){
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, V3);
}

void setup()
{
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  timer.setTimeout(2000L,initBlink);


//Serial.println(F("check 1")); //testing code. does not display, serial connection to slow?

  // Clear the terminal content
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush(); //push out messages

  
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    terminal.println(F("SSD1306 allocation failed"));
    terminal.flush();
    for(;;); // Don't proceed, loop forever
  }
  else{
    terminal.println(F("SSD1306 allocation success"));
    terminal.flush();
  }

  display.display();//loaded with adafruit splash
  terminal.println(F("Splash Loaded"));
  terminal.flush();

  timer.setInterval(200L, myTimerEvent);
  
}//end of setup

void loop()
{
  Blynk.run();
  timer.run();
}

void initBlink(){

  digitalWrite(17, HIGH);
  timer.setTimeout(2000L, [](){ digitalWrite(17, LOW); } );
  terminal.println(F("Welcome!"));
  terminal.flush();
}


BLYNK_WRITE(V3){ //read?
  if(param.asInt()==1){
    digitalWrite(17, LOW); //turns on led (locked)

    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,5);
    display.println(F("Locked"));
    display.display();

    String lockState = "1 (Locked)";
    Blynk.virtualWrite(V2, lockState);
  }
  else{
        digitalWrite(17, HIGH); //turns off led (unclocked)

        display.clearDisplay();
        display.setTextSize(2); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10,5);
        display.println(F("Unlocked"));
        display.display();

        String lockState = "0 (Unlocked)";
        Blynk.virtualWrite(V2, lockState);
  }
}
