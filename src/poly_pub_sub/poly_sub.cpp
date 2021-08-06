#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/polygon.hpp>

void topic_callback(const geometry_msgs::msg::Polygon::SharedPtr msg)
{
   // RCLCPP_INFO(rclcpp::get_logger("my_logger"), "I heard: '%s'", msg->data);
   for (int i = 0 ;i <4 ; i++)
   {
       std::cout << "x : " << msg->points[i].x << std::endl;
       std::cout << "y : " << msg->points[i].y << std::endl;
       std::cout << "z : " << msg->points[i].z << std::endl;
   }
    
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("poly_listener");
    auto chatter_sub = node->create_subscription<geometry_msgs::msg::Polygon>(
        "/poly_pub", 1, topic_callback);
    rclcpp::spin(node);
    //loop_rate.sleep();
}