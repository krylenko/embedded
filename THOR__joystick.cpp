// (c) daniel ford, daniel.jb.ford@gmail.com

// XBOX controller node 

#include "ros/ros.h"
#include <SDL.h>
#include "thor/joyMsg.h"

void initSDL(void);

int main(int argc, char **argv)
{

	int LJoyX=0, LJoyY=0, LTrig=0, RJoyX=0;
	int RJoyY=0, RTrig=0, hat=0;

	int buttonA=0, buttonB=0, buttonBlk=0, buttonX=0, buttonY=0;
  int buttonWht=0, buttonStart=0, buttonLJoy=0, buttonRJoy=0, buttonBack=0;

	int running=1;

  // set up ros publisher
  ros::init(argc, argv, "joystick");    // init node
  ros::NodeHandle n;                    // init node handle
  ros::Publisher joy_pub = n.advertise<thor::joyMsg>("joystick", 1000);
  ros::Rate loop_rate(10);              // specify loop rate (10 Hz here)

	// init SDL and event struct
	initSDL();
	SDL_Event event;

	// init joystick
	SDL_Joystick *stick = NULL; 
	stick = SDL_JoystickOpen( 0 ); 
	if( stick == NULL ) { printf("no joystick opened\n"); }	

  //ROS_INFO("hats %d",SDL_JoystickNumHats(stick));

	while( ros::ok() && running )
	{

		// grab axis and button values
		LJoyX = SDL_JoystickGetAxis(stick, 0);
		LJoyY = SDL_JoystickGetAxis(stick, 1);
		LTrig = SDL_JoystickGetAxis(stick, 2);
		RJoyX = SDL_JoystickGetAxis(stick, 3);
		RJoyY = SDL_JoystickGetAxis(stick, 4);
		RTrig = SDL_JoystickGetAxis(stick, 5);

		hat = SDL_JoystickGetHat(stick, 0);

		buttonA = SDL_JoystickGetButton(stick, 0);
		buttonB = SDL_JoystickGetButton(stick, 1);
		buttonBlk = SDL_JoystickGetButton(stick, 2);
		buttonX = SDL_JoystickGetButton(stick, 3);
		buttonY = SDL_JoystickGetButton(stick, 4);
		buttonWht = SDL_JoystickGetButton(stick, 5);
		buttonStart = SDL_JoystickGetButton(stick, 6);
		buttonLJoy = SDL_JoystickGetButton(stick, 7);
		buttonRJoy = SDL_JoystickGetButton(stick, 8);
		buttonBack = SDL_JoystickGetButton(stick, 9);

    // print info for testing/debugging
    /*
		ROS_INFO("left joy x axis %d",LJoyX);
		ROS_INFO("left joy y axis %d",LJoyY);
  	ROS_INFO("left trigger %d",LTrig);
		ROS_INFO("right joy x axis %d",RJoyX);		
    ROS_INFO("right joy y axis %d",RJoyY);
		ROS_INFO("right trigger %d",RTrig);
		
    if(event.jhat.value & SDL_HAT_UP)    ROS_INFO("hat up");
    if(event.jhat.value & SDL_HAT_DOWN)  ROS_INFO("hat down");
    if(event.jhat.value & SDL_HAT_LEFT)  ROS_INFO("hat left");
    if(event.jhat.value & SDL_HAT_RIGHT) ROS_INFO("hat right");
    
		if(buttonA)		  ROS_INFO("A button");
		if(buttonB)		  ROS_INFO("B button");
		if(buttonBlk)	  ROS_INFO("black button");
		if(buttonX)	    ROS_INFO("X button");
		if(buttonY)		  ROS_INFO("Y button");
		if(buttonWht)   ROS_INFO("white button");
		if(buttonStart)	ROS_INFO("start button");
		if(buttonLJoy)	ROS_INFO("left joy button");
		if(buttonRJoy)  ROS_INFO("right joy button");
		if(buttonBack)  ROS_INFO("back button");
    */

    // init publication msg
    thor::joyMsg joy;
    
    // fill message
    joy.LJoyX = LJoyX;
    joy.LJoyY = LJoyY;
    joy.LTrig = LTrig;
    joy.RJoyX = RJoyX;
    joy.RJoyY = RJoyY;
    joy.RTrig = RTrig;

    joy.buttonA = buttonA;
    joy.buttonB = buttonB;
    joy.buttonX = buttonX;
    joy.buttonY = buttonY;
    joy.buttonBlk = buttonBlk;
    joy.buttonWht = buttonWht;
    joy.buttonStart = buttonStart;
    joy.buttonBack = buttonBack;
    joy.buttonLJoy = buttonLJoy;
    joy.buttonRJoy = buttonRJoy;

    // publish message        
    joy_pub.publish(joy);               

    // flush data to callbacks (not needed here, but generally useful)
    ros::spinOnce();

    // sleep until woken again by loop_rate code
    loop_rate.sleep();

		// check to see if SDL has quit to avoid hanging
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			SDL_JoystickClose(stick); 	// close joystick	
			SDL_Quit();					// quit SDL
			running = 0;				// terminate while loop
    }

  }

	return 0;

}

void initSDL()
{

	//initialize sdl
	if ( SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	//Check if there's any joysticks 
	if( SDL_NumJoysticks() < 1 )
		printf("no joystick found\n");

}


