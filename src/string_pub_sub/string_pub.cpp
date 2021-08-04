#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("talker");
    auto chatter_pub = node->create_publisher<std_msgs::msg::String>("chatter",
    1000);

    rclcpp::Rate loop_rate(10);
    int count = 0;
//  std_msgs::String msg;
    std_msgs::msg::String msg;
//  while (ros::ok())
  while (rclcpp::ok())
  {
    std::stringstream ss;
    ss << "hello world " << count++;
    msg.data = ss.str();
//    ROS_INFO("%s", msg.data.c_str());
    RCLCPP_INFO(node->get_logger(), "%s\n", msg.data.c_str());
    chatter_pub->publish(msg);
//    ros::spinOnce();
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  return 0;
}