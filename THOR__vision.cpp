// (c) daniel ford, daniel.jb.ford@gmail.com

// vision node, object tracking and optic flow
// 9.4.2011 optic flow and object tracking integrated at last!

#include "ros/ros.h"
#include "thor/visionMsg.h"

#include "optic.h"
#include "optic.cpp"
 
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <stdio.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

int main(int argc, char* argv[])
{

    // optic flow class
    Optic visual;

    // tracking variables
    double X = 0, Z = 0;
    double ballX = 0, ballY = 0, ballR = 0;
    int ballDetect = 0;

    // init ros node and publisher
    ros::init(argc, argv, "vision");    // init node
    ros::NodeHandle n;                  // init node handle
    ros::Publisher vision_pub = n.advertise<thor::visionMsg>("vision_state", 1000);     // create publisher handle
    ros::Rate loop_rate(10);              // specify loop rate (10 Hz here)
    thor::visionMsg viz;                  // init message to publish

    ROS_INFO("Vision node initialized");

    while( ros::ok() )
    {

        visual.getflows(X, Z, ballX, ballY, ballR, ballDetect);

        // update and publish message
        viz.ballDetect = ballDetect;
        viz.ballX = ballX; viz.ballY = ballY; viz.ballR = ballR;
        viz.opticX = X; viz.opticZ = Z;
        vision_pub.publish(viz);

        //ROS_INFO("X %f Z %f",X,Z);
        //ROS_INFO("bX %f bY %f bR %f", ballX, ballY, ballR);

        // flush data to callbacks (not needed here, but generally useful)
        ros::spinOnce();

        // sleep until woken again by loop_rate code
        loop_rate.sleep();


    }

    return 0;
}
