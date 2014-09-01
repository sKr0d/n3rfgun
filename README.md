n3rfgun
=======

Nerf Gun Modification.

My son thought it would it would be fun to modify a Nerf gun, to increase the firing speed
and dart speed/distance.  He found a few YouTube videos that showed how to break down the gun.
After that, we went our own direction, replacing the analog parts with an Arduino from Adafruit,
called the Trinket.  We chose the 5v model, as it was close to the 6v that powers the gun.

We stripped out all of the original electronics, leaving only the motors and switches.

The original design used standard 2N2222 NPN transistors to switch the motors on and off, but
discovered that the two motors powering the accelerator, had a starting load of 1.2A, and the
2N2222 could only supply 700mA.  We switched to the TIP120 instead, as we could get a peak load
of 2A, that was enough to start the motors.

After some test firing, we decided that the accelerator motors were running too fast.  The batteries
were going to run out fast, and the darts really hurt when they hit you!  We employed the PWM feature
of the Arduino to contol the speed of the motors.

PARTS LIST
*  1x Adafruit Trinket 5v - https://www.adafruit.com/product/1501
*  2x TIP120 Darlington Transistor - https://www.adafruit.com/products/976
*  2x 1N4001 Diode - https://www.adafruit.com/products/755
*  2x 2.2k resistor
*  2x 10k resistor
*  1x 220 ohm resistor
*  6x Adafruit NeoPixels - https://www.adafruit.com/products/1260
*  Hookup wire

** OPERATION **

POWER
The power is applied to the circuit when the magazine is loaded into the gun.

ACCELERATION
When the gun powers up, the acceleration motors are not spinning.  By pressing the button below the
trigger, the acceleration motors start to spin at 50% speed.  Another press of the button jumps to 75%,
and a third press puts the motors at full power.  Another press sets the motors to 0 again.

FIRING
The Nerf gun employs a safety mechanism, and will not fire if the lower button is not held.  During
the acceleration stage, press and hold the speed button when you are at the desired level.  This
will enable the trigger, and allow you to fire the gun.

Squeeze the trigger, and the loader motor will be engaged, pushing a dart into the accelerator.
The dart is then grabbed, and launched from the gun. This is a fully-automatic gun, so as long as the
trigger is held, a new dart will be loaded into the accelerator and launched.

Sometimes the gun jams, when a dart is not picked up fast enough, and the loader attempts to grab
the next one.  The easiest way to clear it, is to remove the magazine, remove any stuck darts,
override the magazine power button, then pull the trigger a couple of times to return the loader
to the correct position before loading the magazine again.

BLINKY LIGHTS
We added some Adafruit NeoPixels for some nightime effects.

When the gun is powered on, the NeoPixels will cycle through a rainbow of colors.
When the trigger is pressed, the NeoPixels do a lighting effect to emulate the firing of the gun.



