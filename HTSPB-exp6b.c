#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*   HiTechnic Experimenter's Kit for the SuperPro

Experiment - 6 Variation - Complex Reaction Time Measurement

This program measures the time taken to press a button switch after an LED is turned on.

*/

#include "drivers/HTSPB-driver.h"

task main() {
  ubyte buttonmask = 0;

  // The data to be written: 0x30 = 110000 binary,
  // makes B4,B5 digital ports outputs.
  HTSPBsetupIO(HTSPB, 0x03);

  while(true) {
    // Turn off all outputs
    HTSPBwriteIO(HTSPB, 0x00);

    eraseDisplay();
    nxtDisplayTextLine(2, "running");

    wait1Msec(random(5000) + 3000);

    // Turn on a random LED
    if(random(1) > 0) {
      HTSPBwriteIO(HTSPB, 0x01);
      buttonmask = 0x10;
    } else {
      HTSPBwriteIO(HTSPB, 0x02);
      buttonmask = 0x20;
    }

    time1[T1] = 0;

    while (HTSPBreadIO(HTSPB, 0x30) != buttonmask) {
      wait1Msec(5);
    }

    eraseDisplay();
    nxtDisplayTextLine(2, "Time: %d", time1[T1]);

    while (HTSPBreadIO(HTSPB, 0x30) != 0x30) {
      wait1Msec(5);
    }
  }
}
