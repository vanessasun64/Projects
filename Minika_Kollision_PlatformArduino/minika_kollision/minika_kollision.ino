/* 
Title:    minika_kollision.ino
Author:   Lawrence Gabriel Castillo
Date:     2019-Feb-17
Desc:     Deployed to AdaFruit Flora for use with NeoPixel LED strands
          Triggers LEDs to light in a pre-determined light sequences.
Purpose:  Lighting patterns developed for artist Vanessa Sun. Vanessa is 
          augmenting an outfit in support of Minika Ko fashion and tech show, 
          "Kollision."
Build:    Arduino 1.8.6; Arduino AVR Boards 1.6.22 (LilyPad); 
          AdaFruit AVR Boards 1.4.13 (Flora); AdaFruit NeoPixel 1.1.8
Deploy:   LilyPad Arduino, Processor ATmega328P, Port Dev/ttyUSB1
          AdaFruit Flora, Port Dev/ttyACM0 (AdaFruit Flora)
*/

#include <Adafruit_NeoPixel.h>
#define PIN 6

// @param number of pixels in strip
// @param Arduino pin number (most are valid)
// @param pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    strip.begin();
    strip.setBrightness( 50 );
    strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
    //ConvergePattern();
    RandomizePattern();
}

/*
Section: Randomize Pattern
*/

// Color setup for randomize pattern. This pattern pallette 
// only displays: orange yellow white
// @post    calls helper function to both set and reset LED output
// @return  four LED outputs (two on, two off)
void RandomizePattern()
{
    int r = 255;  // red valid 0-255
    int g = 0;    // green valid 0-90: affects white tone/ brightness 
    int b = 0;    // blue valid 0-100: affects white tone/ brightness
    int waitSet = 4;    // sets delay after LED on (ms)
    int waitReset = 1;  // sets delay after LED off (ms)

    // runs 7 times
    // red is constant, green increases exponentially, blue on/ off 
    for( int i = 2; i < 129; i *= 2 )
        { int g_ = 0, b_ = 0;
        if ( i >= 128 ) { g_ = 61 + g; b_ = 155 + b; }
        Randomize(strip.Color( r, ( i/2 + 40 + g_ ), b_ ), waitSet ); // LED on 
        Randomize(strip.Color( 0, 0, 0 ), waitReset ); } // LED off
}

// LEDs will light in a random pattern, simulating the look of brain activity.
// Strand is divided in half (left/ right brain) and one LED is 
// set on both sides
// @param   color ( R, G, B ); values range from 0-255
// @param   time delay ( ms ); non-negative
// @pre     valid entry
// @post    random access of one LED of lower half and one from upper half
// @return  two LED outputs
void Randomize( uint32_t color_rgb, uint8_t wait_time ) 
{ 
    for( uint16_t i = 0; i < 1; i++ ) 
        { strip.setPixelColor( random( 0, strip.numPixels()/2 ), color_rgb ); // lower
        strip.setPixelColor( random ( strip.numPixels()/2, strip.numPixels()), color_rgb ); //upper
        strip.show(); } // output
        
    delay( wait_time * 6 ); // wait before sending back to loop()
}

/*
Section: Converge LED Pattern
*/

// Color setup for converge pattern. This pattern pallette 
// only displays colors: red orange pink magenta purple
// @post    calls helper function to both set and reset LED output
// @return  four LED outputs (two on, two off)
void ConvergePattern() 
{
    int r = 255;  // red valid 0-255
    int g = 10;   // green valid 0-191: offset
    int b = 0;    // blue valid 0-128: offset
    int waitSet = 100;  // sets delay after LED on ( ms )
    int waitReset = 1;  // sets delay after LED off ( ms )

    // runs 7 times
    // red is constant, green and blue increase exponentially
    for( int i = 2; i < 129; i *= 2 )
        { Converge(strip.Color( r, ( i/2 + g ), i + b), waitSet ); 
        Converge(strip.Color( 0, 0, 0 ), waitReset ); }
}

// LEDs will light from both ends towards the middle.
// Strand is divided in half (left/ right) and one LED is 
// set on both sides
// @param   color ( R, G, B ); values range from 0-255
// @param   time delay ( ms ); non-negative
// @pre     valid entry
// @post    access of one LED of lower half and one from upper half
// @return  14 LED outputs
void Converge( uint32_t color_rgb, uint8_t wait_time ) 
{ 
    for( uint16_t i = 0; i < ( strip.numPixels()/2 ); i++ ) 
        { strip.setPixelColor( i, color_rgb ); // lower
        strip.setPixelColor(( strip.numPixels()-1-i ), color_rgb ); // upper
        strip.show(); delay( wait_time ); }
        
    delay( wait_time * 6 ); // wait before sending back to loop()
}
