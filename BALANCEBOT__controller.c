// (c) daniel ford, daniel.jb.ford@gmail.com

#pragma config(Sensor, S1,     lightSense,          sensorLightActive)
#pragma config(Sensor, S4,     distSense,           sensorNone)
#pragma config(Motor,  motorA,          leftMtr,       tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMtr,      tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "setup.h"

// minimal-order observer controller
void ctrlMinOrder(float cmdInput, float error){

  // no loop version
  // calc psi1 based on output error and save values for next iteration
  float psi1 = -1*Dob[1]*psi1u_1 + psi1num[0]*psi1e_1 + psi1num[1]*psi1e_2;
  psi1e_2 = psi1e_1; psi1e_1 = error;
  psi1u_1 = psi1;

  // calc psi0 based on input and save value for next iteration
  //float psi0in = cmdInput - psi1;
  float psi0in = 0 - psi1;
  float psi0 = -1*psi0den_nl[1]*psi0u_1 + Dob[0]*psi0e_1 + Dob[1]*psi0e_2;
  psi0e_2 = psi0e_1; psi0e_1 = psi0in;
  psi0u_1 = psi0;

  leftV = (int)(psi0*MOTORRNG);
  rightV = leftV;

}

// try balancing the robot
void balance()
{

  t_current = time1[T1]/MS;
  nxtDisplayCenteredBigTextLine(1,"RUNNING");

  // update error
  light = getLightRaw(); dist = getDistRaw();
  sense = fuseSensors(light, dist);
	error = cmdValue - sense;

	// call controller routine to update commanded velocity
	ctrlMinOrder(cmdValue,error);

	// add joystick commands
  joystk();

  // limit outputs and send
  limitOuts();

}

// main task
task main(){

  reset();
  while(1){
    if(!start){
      nxtDisplayTextLine(1,"light %d",getLightRaw());
      nxtDisplayTextLine(2,"left: set zero");
      nxtDisplayTextLine(3,"orange: balance");
      if(nNxtButtonPressed == 2)
        reset();
      if(nNxtButtonPressed == 3){
        ClearTimer(T1);
        eraseDisplay();
        start = true;
      }
    }
    if(start){
      if(nNxtButtonPressed == 1){
        reset();
        start = false;
      }
      balance();
      //wait1Msec(1);
    }
  }

}
