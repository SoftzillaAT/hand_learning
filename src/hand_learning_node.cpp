#include "hand_learning/hand_learning_node.h"

using namespace std;

namespace hand_learning {

	/* constructor */
	HandLearning::HandLearning(ros::NodeHandle &nh)
	{

		n = &nh;
		ROS_INFO("Waiting for servers....");
	}


	void HandLearning::run() 
	{
		ROS_INFO("Subscribe Camera");
		sub_camera_ = n->subscribe ( "/camera/depth_registered/points", 1, &HandLearning::callbackCamera, this);
	}

	void HandLearning::callbackCamera( const sensor_msgs::PointCloud2ConstPtr& cloud_msg )
	{
		ROS_INFO("Callback Camera");
		//savePCL(cloud_msg);
		startRecognizer(cloud_msg);
	}

	void HandLearning::startRecognizer( const sensor_msgs::PointCloud2ConstPtr& cloud_msg )
	{
		recognition_srv_definitions::recognize srv;
		srv.request.cloud = *cloud_msg;
		ros::ServiceClient client = n->serviceClient<recognition_srv_definitions::recognize>("/recognition_service/sv_recognition");
		
		if (client.call(srv))
		{
			ROS_INFO("Service Response. Found Object: %d", (int)srv.response.ids.size());
		
			for( size_t i = 0; i < srv.response.ids.size(); i++ )
			{
				ROS_INFO("ID: %s\r\n", srv.response.ids[i].data.c_str());
			}
		}
		else
		{
			ROS_ERROR("Failed to call service recognition_srv");
			return;
		}	

	}

	void HandLearning::savePCL( const sensor_msgs::PointCloud2ConstPtr& cloud_msg) 
	{
		// Container for original & filtered data
		pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
		pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
		pcl::PCLPointCloud2 cloud_filtered;

		// Convert to PCL data type
		pcl_conversions::toPCL(*cloud_msg, *cloud);

		// Convert from PointCloud2 to PointCloud
		pcl::PCLPointCloud2 pcl_pc2;
		pcl_conversions::toPCL(*cloud_msg,pcl_pc2);
		pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
		pcl::fromPCLPointCloud2(pcl_pc2, *temp_cloud);  

		pcl::io::savePCDFileASCII ("/home/dom/diplomata/test_pcd.pcd", *temp_cloud);
		// OCL BINARY sae

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
