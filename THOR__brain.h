// (c) daniel ford, daniel.jb.ford@gmail.com

// Thor planning and control node

#ifndef BRAIN_H
#define BRAIN_H

#include "thor/stateMsg.h"
#include "thor/visionMsg.h"
#include "thor/stateCmd.h"

using namespace std;

class Brain
{

  public:

  // constructor/destructor
  Brain();
  ~Brain(){};

  // subscription callbacks
  void chassisCbk(const thor::stateMsg::ConstPtr& msg);
  void visionCbk(const thor::visionMsg::ConstPtr& msg);

  private:

};

// constructor
Brain::Brain()
{

}

// chassis subscription callback
void Brain::chassisCbk(const thor::stateMsg::ConstPtr& msg)
{
  // process chassis state
}

// vision sub callback
void Brain::visionCbk(const thor::visionMsg::ConstPtr& msg)
{
  // process camera outputs
}

#endif

