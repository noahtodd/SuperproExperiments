#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "drivers/hitechnic-superpro.h"

task comm(){
	int inputdata;
  bool NXTprocessing = 0; // pin 3
  ubyte arduinoUpdate = 0b00000100;// pin 2
  int frameSize = 10;
	nxtDisplayTextLine(1, "initialized task");

  // set pins 3,4,5,6,7 as outputs
  HTSPBsetupIO(HTSPB, 0b11111000);
	//change NXT processing pin to low
  HTSPBwriteIO(HTSPB, 0b11110000);

  //wait for Arduino pin to pull high. arduino is pin 2
  nxtDisplayTextLine(2, "waiting for arduino");
  while(HTSPBreadIO(HTSPB, 0b00000100) != 4){
  	nxtDisplayTextLine(5, "arduino pin: %d", HTSPBreadIO(HTSPB, 0b00000100));
  	wait1Msec(1);
  }

  while(true) {
  	inputdata = 0;
    //for loop that runs once for each packet in a frame
  	for (int i = 0; i < 10; i++){
  		//wait for the arduino to change the arduino update pinZ
  		nxtDisplayTextLine(3, "cycle %d, waiting for arduino", i);
  		while(arduinoUpdate == HTSPBreadIO(HTSPB, 0b00000100)){
  			wait1Msec(1);
  		}
  		//read input pin / pins
  		inputdata += (HTSPBreadIO(HTSPB, 0x01);
  		nxtDisplayTextLine(4, "input 1: %d", HTSPBreadIO(HTSPB, 0x01));
  		//use left-hand operator to process data
  		inputdata = inputdata << 1;
  		nxtDisplayTextLine(5, "input 1: %d", inputdata);
  		//change NXT processing pin
  		NXTprocessing = !NXTprocessing;
  		HTSPBwriteIO(HTSPB, NXTprocessing << 3);
  		//change arduinoUpdate
  		if (arduinoUpdate == 4)
  			arduinoUpdate = 0;
  		else
  			arduinoUpdate = 4;
  	}
  	//display data
  	nxtDisplayTextLine(7, "Data: %d", inputdata);
  	//TODO apportion data to values usable in the rest of the program
  }
}

task test(){
	HTSPBsetupIO(HTSPB, 0b11111000);
	while(true){
		HTSPBwriteIO(HTSPB, 0b00001000);
		wait10Msec(100);
		HTSPBwriteIO(HTSPB, 0b00000000);
		wait10Msec(100);
	}
}

task main() {
  StartTask(comm);
  //StartTask(test);
  while(true){wait10Msec(1000);}
}
