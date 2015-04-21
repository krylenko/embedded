// (c) daniel ford, daniel.jb.ford@gmail.com

// Thor planning and control node 

#include "ros/ros.h"
#include "brain.h"

// subscribe to chassis_state, vision_state
// set up a client for chassis_state_update srv

int main(int argc, char **argv)
{

  // inits
  Brain thorMind;
  ros::init(argc, argv, "brain");
  ros::NodeHandle n;

  // subscription setup
  ros::Subscriber chassis_sub = n.subscribe("chassis_state", 1000, &Brain::chassisCbk, &thorMind);
  ros::Subscriber vision_sub = n.subscribe("vision_state", 1000, &Brain::visionCbk, &thorMind);

  // service client setup
  ros::ServiceClient chassis_client = n.serviceClient<thor::stateCmd>("chassis_state_update");
  thor::stateCmd stateSrv;

  // main loop

  while(ros::ok())
  {

    // read inputs from topics

    // process inputs and decide on action

    // send commands to chassis using service call
    
    // fill service request message

    // send it and check for errors
    if( !chassis_client.call(stateSrv) )
      ROS_INFO("Failed to connect to chassis service");
    else return stateSrv.response.success;

    // flush data to callbacks
    ros::spinOnce();

  }

  return 0;

}
