// (c) daniel ford, daniel.jb.ford@gmail.com

#include <iostream>
#include "chassis.h"

using namespace std;

main()
{

	//cout << "here1" << endl;

	// init chassis
	Chassis thor;
	thor.sendCmd();

	int idx=0;

	while(1)
	{
	
		cout << "index: " << idx << endl;

		// read chassis state from USB
		thor.getState();

		// print state to screen
		thor.showState();

    // TO DO:
		// read/compute visual state from camera
		// update planning/probs based on full state
		// choose action based on probs

		// send actions to chassis
		thor.sendCmd();
		
		// alternate ROS nodes
    
    // TO DO:
		// chassis: service requests and state publication
		// planning: service calls to chassis and action publication
		// visual: optic flow and object tracking 
		// GUI/monitor: state and action subscriber, reset/launch

		idx++;

	}
	
}
