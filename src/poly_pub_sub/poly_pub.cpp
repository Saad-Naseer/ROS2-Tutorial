#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/polygon.hpp>
#include <geometry_msgs/msg/point32.hpp>


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("polygon_talker");
    auto chatter_pub = node->create_publisher<geometry_msgs::msg::Polygon>("poly_pub",
    1000);

    rclcpp::Rate loop_rate(10);
   // int count = 0;
//  std_msgs::String msg;
    geometry_msgs::msg::Polygon msg;
    geometry_msgs::msg::Point32 p;
//  while (ros::ok())
  while (rclcpp::ok())
  {
    for (int i = 0; i < 4; i++)
    {
        p.x = i;
        p.y = i+1;
        p.z = 100;
        msg.points.push_back(p);
    }
   

    chatter_pub->publish(msg);
//    ros::spinOnce();
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  return 0;

}