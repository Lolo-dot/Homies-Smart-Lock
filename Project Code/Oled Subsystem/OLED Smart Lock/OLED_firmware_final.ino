/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.
************************************************************/
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

// Declaration for SSD1306 display connected using software SPI (default arduino case commented out):
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
char auth[] = "AUTHENTICATION KEY HERE";

WidgetTerminal terminal(V9);
BlynkTimer timer;  //blynk timer

int lockState; //locked/unlocked state variable for V0

void myTimerEvent(){

  Blynk.syncVirtual(V0); //Sync with database V0 value

  if(lockState==1){
    digitalWrite(17, LOW); //turns on led (locked)

    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,5);
    display.println(F("Locked"));
    display.display();
  }
  else{
        digitalWrite(17, HIGH); //turns off led (unlocked)

        display.clearDisplay();
        display.setTextSize(2); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10,5);
        display.println(F("Unlocked"));
        display.display();
  }
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

  //Initial Boot LED On
  digitalWrite(17, LOW);
  timer.setTimeout(2000L,initBlink);

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

  timer.setInterval(500L, myTimerEvent); //timer runs every 0.5 seconds
  
}//end of setup

void loop()
{
  Blynk.run();
  timer.run();
}

void initBlink(){  //initial boot Led Off On indicator function

  digitalWrite(17, HIGH);
  timer.setTimeout(2000L, [](){ digitalWrite(17, LOW); } );

  //terminal debugging message
  terminal.println(F("Welcome!"));
  terminal.flush();
}


BLYNK_WRITE(V0){ //reads changes to V0, stores value to lockstate variable
    lockState = param.asInt();
  }
