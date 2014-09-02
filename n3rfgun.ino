/*
 *  N3RFGUN
 *
 *  When magazine is inserted into the gun, the power switch is
 *  activated, and the circuit is powered by 4x c-batteries (6v).
 *  The gun should be silent, but the NeoPixels will start with the
 *  rainbow pattern, showing that the gun is active.
 *  When the speed switch is pressed, the accelerator motors will start
 *  to spin at 50%. Another click goes to 75%, and a third brings it
 *  to full power. One last click drops back to 0%.
 *  The main trigger will not fire unless the speed switch is pressed
 *  and held in place.  When you click to your desired speed, simply
 *  hold the button, then fire at will!
 *  Pressing the trigger button will activate the loader, which places
 *  a dart in the accelerator, and launches it out of the gun.
 *  This is a fully automatic gun, so it will fire until the darts are
 *  gone, or you let up on the trigger.
 *  Pressing the trigger also activates a lightning animation sequence
 *  on the NeoPixels. This simulates the muzzle flash, and looks cool
 *  in the dark or at night!
 *
 *  https://github.com/sKr0d/n3rfgun/wiki
 *  Scott and Alex McCulley, September, 2014
 */

int numpix = 6; // number of pixels in the chain

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  #include <avr/power.h>
#endif
#define PIN 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numpix, PIN, NEO_GRB + NEO_KHZ800);

int TRG = 4;   // trigger pin
int SPD = 3;   // speed pin
int ACT = 0;   // action pin
int LOD = 1;   // loader pin
int NEO = 2;   // neopixel pin

int ACTS = 0;   // action speeed
int LODS = 240; // loader speed
int REL = 0;    // release speed button

int i = 0;	// for loop
int k = 0;	// for loop
 
void setup() {
   pinMode(TRG, INPUT);
   pinMode(SPD, INPUT);
   pinMode(ACT, OUTPUT);
   pinMode(LOD, OUTPUT);
   pinMode(NEO, OUTPUT);
   
   pixels.begin();
   pixels.setBrightness(85);
   pixels.show();
}
 
void loop() {
   analogWrite(ACT, ACTS);	// set the acceleration motor speed
   rainbow(20);			// start the rainbow animation
}

void spd() {
  if (digitalRead(SPD) == LOW && REL == 1) {
    switch (ACTS) {
      case 0:
        ACTS = 128; // 50%
        break;
      case 128:
        ACTS = 192; // 75%
        break;
      case 192:
        ACTS = 255; // 100%
        break;
      default:
        ACTS = 0;   // 0%
      break;
    }
    analogWrite(ACT, ACTS);
    delay(40);
    REL = 0;
  } else {
    if (digitalRead(SPD) == HIGH) {
      REL = 1;
    }
  }
}

void trig() { // check for press of trigger button
    if (digitalRead(TRG) == LOW) {
     analogWrite(LOD, LODS);
     fire();
   } else { analogWrite(LOD, 0);
   }
}

void rainbow(uint8_t wait) { // make pretty rainbow colors
  uint16_t i, j;

  for(j=0; j<256; j=j+4) {
    spd();	// check for press of speed button
    trig();	// check for press of trigger button
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void fire() {
  for(k=0; k<6; k++) {
    fastWipe(pixels.Color(255,255,255), 50);
    delay(20);
    fastWipe(pixels.Color(0,0,0), 50);
    delay(10);
  }
}

void fastWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(1);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
