#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/visualization/cloud_viewer.h>

#include <sensor_msgs/Imu.h>
#include <livox_ros_driver/CustomMsg.h>

ros::Publisher pub;
void rgb_set(int wr, int wg, int wb, int br, int bg, int bb)
{                                                                                 //设置RGB
        printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm", wr, wg, wb, br, bg, bb); //\033[38表示前景，\033[48表示背景，三个%d表示混合的数
}

int main(int argc, char **argv)
{
        // Initialize ROS
        ros::init(argc, argv, "my_pcl_tutorial");
        ros::NodeHandle nh;

        rosbag::Bag bag;
        bag.open("/home/l/dataset/CamVox.bag", rosbag::bagmode::Read); //打开一个bag文件

        std::vector<std::string> topics; //设置需要遍历的topic

        topics.push_back(std::string("/isee_rgb"));
        topics.push_back(std::string("/livox/lidar"));
        topics.push_back(std::string("/livox/imu"));

        rosbag::View view(bag, rosbag::TopicQuery(topics));
        //使用迭代器的方式遍历,注意：每一个迭代器为一帧数据
        rosbag::View::iterator it = view.begin();

        for (; it != view.end(); ++it)
        {
                //获取一帧数据内容，运用auto使其自动满足对应类型
                auto m = *it;
                //得到该帧数据的topic
                std::string topic = m.getTopic();
                if (topic == "/isee_rgb")
                {
                        sensor_msgs::Image::ConstPtr rgb_msg = m.instantiate<sensor_msgs::Image>();
                        cout << "/isee_rgb   " << setprecision(19) << rgb_msg->header.stamp.toSec() << endl;
                }
                if (topic == "/livox/lidar")
                {
                        livox_ros_driver::CustomMsg::ConstPtr livox_msg = m.instantiate<livox_ros_driver::CustomMsg>();
                        cout << "/livox/lidar   " << setprecision(19) << livox_msg->header.stamp.toSec() << endl;
                }
                 if (topic == "/livox/imu")
                 {
                         sensor_msgs::Imu::ConstPtr imu_msg = m.instantiate<sensor_msgs::Imu>();
                 } 
        cout << endl;

        bag.close();
}

