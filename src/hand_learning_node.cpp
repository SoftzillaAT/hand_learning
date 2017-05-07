#include "hand_learning/hand_learning_node.h"

using namespace std;

namespace hand_learning {

  /* constructor */
  HandLearning::HandLearning(ros::NodeHandle &nh) : 
    node_handle(&nh)
  {

    node_handle = &nh;
    ROS_INFO("Waiting for servers....");
  }

 
  void HandLearning::run() 
  {
    ROS_INFO("Start ...");
  }

} // close namespace

int main(int argc, char **argv) 
{
  ros::init(argc, argv, "hand_learning");
  if(!ros::isInitialized())
    return 1;
  ros::NodeHandle n;
  ROS_INFO("HAND LEARNING STARTET v1!");

  hand_learning::HandLearning my_node(n);
  ROS_INFO("Class crated");
  my_node.run();
  ros::spin();
  return 0;
}
