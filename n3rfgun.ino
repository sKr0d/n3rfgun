/*
 *  N3RF
 *
 *  On Adafruit Trinket 5v
 *
 *  TRG pin is the gun trigger.  When pressed, the trinket checks the status
 *  of the ARM pin.  When LOW (closed), the gun is armed, and can be fired.
 *  In the case that ARM and TRG are both LOW, the LOD pin will be activated,
 *  sending the dart into the already running ACT motors.
 *  When ARM pin goes from LOW to HIGH (gun just fired) then also start
 *  the gunfire animation.
 *  https://github.com/sKr0d/n3rfgun
 */

int numpix = 6; // number of pixels in the chain

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  #include <avr/power.h>
#endif
#define PIN 2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numpix, PIN, NEO_GRB + NEO_KHZ800);

int TRG = 4;   // trigger pin
int ARM = 3;   // armed pin
int ACT = 0;   // action pin
int LOD = 1;   // loader pin
int NEO = 2;   // neopixel pin

int ACTS = 0;   // action speeed
int LODS = 240; // loader speed
int REL = 0;   //release speed button

int i = 0;
int k = 0;
 
void setup() {
   pinMode(TRG, INPUT);
   pinMode(ARM, INPUT);
   pinMode(ACT, OUTPUT);
   pinMode(LOD, OUTPUT);
   pinMode(NEO, OUTPUT);
   
   pixels.begin();
   pixels.setBrightness(85);
   pixels.show();
}
 
void loop() {
  analogWrite(ACT, ACTS);  
   rainbow(20);
}

void arm() {
  if (digitalRead(ARM) == LOW && REL == 1) {
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
    if (digitalRead(ARM) == HIGH) {
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
    arm();
    trig();
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
