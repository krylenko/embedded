// (c) daniel ford, daniel.jb.ford@gmail.com

/*************** Thor chassis class and related constants ***********/

#ifndef CHASSIS_H
#define CHASSIS_H

#include <iostream>
#include "serial.h"

#include "thor/stateMsg.h"      
#include "thor/stateCmd.h"

#define	MSGSIZE		29

using namespace std;

class Chassis
{

	public:
	
		Chassis();				                    // constructor
		~Chassis(){close(USBser);};			      // destructor

		// communication with chassis 
		thor::stateMsg getState();                          // retrieve state from chassis
    
    bool updateState( thor::stateCmd::Request &req,     // tell PIC to update state
                      thor::stateCmd::Response &res );

    // state initialization
		void init();
	
	private:

		// state variables for the chassis
		enum {FWD, BACK};
		enum {LEFT, RIGHT};
    enum {ON, OFF};
		
		char driveMtr[5];		// forward/backward
		char steerMtr[2];		// left/right
		char gripSense[4];	// hand sensor
		char gripPos[4];		// hand open/close
		char frontBump[2];	// bump sensors
    char rearBump[2];
		char camTilt[4];		// camera servo position
		char lightRed[2];		// LEDs
		char lightYel[2];	
		char lightGrn[2];	

		// serial port
		int USBser;

};

// constructor
Chassis::Chassis()
{
	// initialize serial port
	USBser = open_port("/dev/ttyUSB0");
	serial_init(USBser);

}

// get chassis state
thor::stateMsg Chassis::getState()
{

	int msgLen = 0, junk = 0;
  char frame = '0';

  junk = write(USBser, "R", 1);         // send read command

  while(frame != 'F' )                  // wait for framing byte
    junk = read(USBser, &frame, 1);

  // read state from chassis
	msgLen = read(USBser, &driveMtr, 5);
	msgLen = read(USBser, &steerMtr, 2);
	msgLen = read(USBser, &gripSense, 4);
	msgLen = read(USBser, &gripPos, 4);
	msgLen = read(USBser, &frontBump, 2);
	msgLen = read(USBser, &rearBump, 2);
	msgLen = read(USBser, &camTilt, 4);
	msgLen = read(USBser, &lightRed, 2);
	msgLen = read(USBser, &lightYel, 2);
	msgLen = read(USBser, &lightGrn, 2);

  // convert state var chars to ints and update state message
  thor::stateMsg state;                   // init message

  state.driveMtr  = atoi(driveMtr);
	state.steerMtr  = atoi(steerMtr);
	state.gripSense = atoi(gripSense);
  state.gripPos   = atoi(gripPos);
  state.frontBump = atoi(frontBump);
  state.rearBump  = atoi(rearBump);
  state.camTilt   = atoi(camTilt);

  if(atoi(lightRed) == ON) 
    state.lightRed  = "on";
  else state.lightRed = "off";

  if(atoi(lightYel) == ON) 
    state.lightYel  = "on";
  else state.lightYel = "off";

  if(atoi(lightGrn) == ON) 
    state.lightGrn  = "on";
  else state.lightGrn = "off";

	return state;

}

// state update service callback 
bool Chassis::updateState(  thor::stateCmd::Request &req,
                            thor::stateCmd::Response &res )
{

  res.success = 1;
  return true;

}

// state initialization
void Chassis::init()
{

	int junk = 0;

  junk = write(USBser, "W", 1);      // send write command
  
  junk += write(USBser, "+000", 5);
  junk += write(USBser, "5", 2);     // 0 is left, 9 is right, anything else is no turn
                                     // will need to recenter wheels by turning actively
  junk += write(USBser, "000", 4);
  junk += write(USBser, "000", 4);
  junk += write(USBser, "0", 2);
  junk += write(USBser, "0", 2);
  junk += write(USBser, "000", 4);
  junk += write(USBser, "1", 2);
  junk += write(USBser, "0", 2);
  junk += write(USBser, "1", 2);
  
  //ROS_INFO("%d bytes written",junk);
  ROS_INFO("Chassis node initialized");
	
}

#endif
