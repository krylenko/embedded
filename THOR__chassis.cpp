// (c) daniel ford, daniel.jb.ford@gmail.com

// chassis node
// communicates with PIC18F4580 to get and update state of chassis (motors, gripper, LEDs, etc.)

#include "ros/ros.h"
#include "chassis.h"

int main(int argc, char **argv)
{

  // init chassis object
  Chassis thor;
  thor.init();     // initialize state variables

  // set up ros publisher
  ros::init(argc, argv, "chassis");     // init publisher node
  ros::NodeHandle n;                    // init node handle
  
  // create publisher handle
  // topic name in quotes
  ros::Publisher chassis_pub = n.advertise<thor::stateMsg>("chassis_state", 1000);    
                                                                           
  ros::Rate loop_rate(10);              // specify loop rate (10 Hz here)

  // set up ros service
  ros::init(argc, argv, "chassisStateUpdate");  // init service node
  ros::NodeHandle s;                            // init node handle
  ros::ServiceServer service = s.advertiseService("chassis_state_update", &Chassis::updateState, &thor);  

  // loop while roscore is running
  while (ros::ok())
  {

    // get state from PIC, update state in Chassis object, fill state message
    thor::stateMsg state = thor.getState();   
    chassis_pub.publish(state);               // publish message

    // flush data to callbacks (not needed here, but generally useful)
    ros::spinOnce();

    // sleep until woken again by loop_rate code
    loop_rate.sleep();

  }

  return 0;
}

