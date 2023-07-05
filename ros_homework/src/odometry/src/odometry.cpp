#include <iostream>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"

void callback(const nav_msgs::Odometry::ConstPtr& ptr)
{
    std::cout << "std_msgs/Header 头部" << std::endl;
    std::cout << "    uint32 序列号: " << ptr->header.seq << std::endl;
    std::cout << "    时间戳: " << ptr->header.stamp << std::endl;
    std::cout << "    字符串 坐标系ID: " << ptr->header.frame_id << std::endl;
    std::cout << "字符串 子坐标系ID: " << ptr->child_frame_id << std::endl;
    std::cout << "geometry_msgs/PoseWithCovariance 姿态" << std::endl;
    std::cout << "    geometry_msgs/Pose 姿态" << std::endl;
    std::cout << "        geometry_msgs/Point 位置" << std::endl;
    std::cout << "        float64 x: " << ptr->pose.pose.position.x << std::endl;
    std::cout << "        float64 y: " << ptr->pose.pose.position.y << std::endl;
    std::cout << "        float64 z: " << ptr->pose.pose.position.z << std::endl;
    std::cout << "    geometry_msgs/Quaternion 方向" << std::endl;
    std::cout << "        float64 x: " << ptr->pose.pose.orientation.x << std::endl;
    std::cout << "        float64 y: " << ptr->pose.pose.orientation.y << std::endl;
    std::cout << "        float64 z: " << ptr->pose.pose.orientation.z << std::endl;
    std::cout << "        float64 w: " << ptr->pose.pose.orientation.w << std::endl;
    std::cout << "    float64[36] 协方差" << std::endl;
    std::cout << "        ";
    for (int i = 0; i < 36; ++i) {
        std::cout << ptr->pose.covariance[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "geometry_msgs/TwistWithCovariance 速度" << std::endl;
    std::cout << "    geometry_msgs/Twist 速度" << std::endl;
    std::cout << "        geometry_msgs/Vector3 线速度" << std::endl;
    std::cout << "            float64 x: " << ptr->twist.twist.linear.x << std::endl;
    std::cout << "            float64 y: " << ptr->twist.twist.linear.y << std::endl;
    std::cout << "            float64 z: " << ptr->twist.twist.linear.z << std::endl;
    std::cout << "        geometry_msgs/Vector3 角速度" << std::endl;
    std::cout << "            float64 x: " << ptr->twist.twist.angular.x << std::endl;
    std::cout << "            float64 y: " << ptr->twist.twist.angular.y << std::endl;
    std::cout << "            float64 z: " << ptr->twist.twist.angular.z << std::endl;
    std::cout << "    float64[36] 协方差" << std::endl;
    std::cout << "        ";
    for (int i = 0; i < 36; ++i) {
        std::cout << ptr->twist.covariance[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "show_odometry");
    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber = nodeHandle.subscribe("/odom", 1000, callback);
    ros::spin();
    return 0;
}
