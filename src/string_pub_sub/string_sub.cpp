#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
using std::placeholders::_1;


void topic_callback(const std_msgs::msg::String::SharedPtr msg) 
    {
      RCLCPP_INFO(rclcpp::get_logger("my_logger"), "I heard: '%s'", msg->data.c_str());
      //std::cout<<"I heard : "<<msg->data.c_str();
    }


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("listener");
    auto chatter_sub = node->create_subscription<std_msgs::msg::String>(
      "/chatter", 1, topic_callback);
    rclcpp::spin(node);
    //loop_rate.sleep();
  
  return 0;
}