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
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/transforms.h>


// ######## SERVICES ########
#include <recognition_srv_definitions/recognize.h>


namespace hand_learning {

	class HandLearning {

		private:
			// Node Handle
			ros::NodeHandle* n;
			ros::Subscriber sub_camera_;
			void callbackCamera ( const sensor_msgs::PointCloud2ConstPtr& );   /// callback function to execute on incoming sensor data
			void savePCL( const sensor_msgs::PointCloud2ConstPtr& );
			void startRecognizer( const sensor_msgs::PointCloud2ConstPtr& );
    	public:
			/* constructor */
			HandLearning(ros::NodeHandle &nh);
			void run();
	};


}

#endif
