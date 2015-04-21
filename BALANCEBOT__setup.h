// (c) daniel ford, daniel.jb.ford@gmail.com

#include "JoystickDriver.c"

#define MS        1000.0

// PID constants
#define Kp        75
#define Ki        0.15
#define Kd        1500
/*
// PID range scaling constants
#define MOTORRNG  100
#define MTRLO     0
#define MTRHI     100
*/

// minimal-order coeffs and scaling

// MOST USABLE
// Pc = -0.0479, -0.0021
// Po = -0.05
#define MOTORRNG  25    // works w/ power supply
//#define MOTORRNG  18    // works w/ batteries
#define MTRLO     0
#define MTRHI     100
float Dob[2] = {1, -1};
float psi0num[2] = {0, -0.00005};
float psi1num[2] = {21.9343, -21.8042};

/*
// NOT BAD
// Pc = -0.0479, -0.0021
// Po = -0.1
#define MOTORRNG  5
#define MTRLO     0
#define MTRHI     100
float Dob[2] = {1, -0.9999};
float psi0num[2] = {0, -0.0001};
float psi1num[2] = {32.8385, -32.7078};
*/

/*
// BEST FROM MIN-ORDER DESIGN
// Pc = -0.1+-0.1j
// Po = -0.4
#define MOTORRNG  5
#define MTRLO     0
#define MTRHI     100
float Dob[2] = {1, -0.9996};
float psi0num[2] = {0, -0.0004134};
float psi1num[2] = {133.8836, -133.7323};
*/

// common to all min-order
float psi0den_nl[2] = {Dob[0]+psi0num[0],Dob[1]+psi0num[1]};

float psi0u_1 = 0;
float psi0e_1 = 0;
float psi0e_2 = 0;

float psi1u_1 = 0;
float psi1e_1 = 0;
float psi1e_2 = 0;

// plant variables
int light = 0; int dist = 0;
int lightZero = 0; int distZero = 0;
int leftV = 0; int rightV = 0;
int newLeftV = 0; int newRightV = 0;

float sense = 0;
float cmdValue = 0; float scaledCmd = 0;
float origCmdValue = 0;
float fwdCmdValue = 0;
float revCmdValue = 0;

// timing and process control vars
float t_current = 0;
bool start = false;

// controller vars
float error = 0; float scaledError = 0;
float errLast = 0;
float errSum = 0;

float intTerm = 0;
int sumMax = 10;
int sumMin = -sumMax;

// convenience and scaling functions

// get light reading
int getLightRaw(){
 return SensorRaw[lightSense];
}

int getDistRaw(){
 return SensorRaw[distSense];
}

float fuseSensors(int lightRaw, int distRaw){

 int lightLo = 380; int lightHi = 540;
 float lightRng = lightHi - lightLo;
 float lightScale = (lightRaw - lightLo)/lightRng;

 float distMax = 12.;
 float distScale = distRaw/distMax;

 float alpha = 1.0;

 return lightScale*alpha + distScale*(1-alpha);

}

// stop motors, reset encoders
void reset()
{
  MuteSound();
  eraseDisplay();
  motor[leftMtr] = 0;
  motor[rightMtr] = 0;
  leftV = rightV = newLeftV = newRightV = 0;

  cmdValue = fuseSensors(getLightRaw(),getDistRaw());
  origCmdValue = cmdValue;
  fwdCmdValue = cmdValue*1.2;
  revCmdValue = cmdValue*0.9;

  errLast = 0;
  errSum = 0;

  // reset timer and set up vars
  ClearTimer(T1);
  t_current = time1[T1]/MS;

}

// read joystick and assign vars
void joystk(){

  getJoystickSettings(joystick);

  int joyX = joystick.joy1_x2;
  int joyY = joystick.joy1_y1;

  // left/right
  if(abs(joyX)>15){
    newLeftV = leftV + joyX/4;
    newRightV = rightV - joyX/4;
  }
  // fwd/rev
  else if(abs(joyY)>15){
    newLeftV = leftV;
    newRightV = rightV;
    if(joyY>0)
      cmdValue = revCmdValue;
    if(joyY<0)
      cmdValue = fwdCmdValue;
  }
  else{
    cmdValue = origCmdValue;
    newLeftV = leftV;
    newRightV = rightV;
  }
}

// limit outputs to prevent out-of-range values, runaways
void limitOuts(){

  if( (newLeftV > 32765) || (newLeftV < -32765) )
    newLeftV = 0; rightV = 0;
  if( (newRightV > 32765) || (newRightV < -32765) ){
    newRightV = 0; leftV = 0;
  }

  if(newLeftV > MTRHI){ newLeftV = MTRHI; }
	if(newLeftV < -MTRHI){ newLeftV = -MTRHI; }

	if(newRightV > MTRHI){ newRightV = MTRHI; }
	if(newRightV < -MTRHI){ newRightV = -MTRHI; }

	if(newRightV < MTRLO && newRightV > -MTRLO && newRightV != 0)
	  motor[rightMtr] = newRightV + MTRLO;
	else
	  motor[rightMtr] = newRightV;

	if(newLeftV < MTRLO && newRightV > -MTRLO && newLeftV != 0)
	  motor[leftMtr] = newLeftV + MTRLO;
	else
    motor[leftMtr] = newLeftV;


}
