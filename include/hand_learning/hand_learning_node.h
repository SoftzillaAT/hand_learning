#ifndef HAND_LEARNING_NODE_H
#define HAND_LEARNING_NODE_H

#include <ros/ros.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <std_srvs/Empty.h>
#include <geometry_msgs/PointStamped.h>

// ######## PCL LIBRARIES #########
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>

namespace hand_learning {

	class HandLearning {

		private:
			// Node Handle
			ros::NodeHandle* node_handle;

    		public:

			/* constructor */
			HandLearning(ros::NodeHandle &nh);
			void run();

	};


}

#endif
