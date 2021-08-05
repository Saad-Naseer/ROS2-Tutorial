#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
//using std::placeholders::_1;

void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr & msg)
{
  cv::Mat im = cv::Mat(200, 200, CV_8UC3);
  //std::cout<<"i am in callback"<<std::endl;
  try
  {
    im = cv_bridge::toCvCopy(msg, "rgb8")->image;
  }
  catch (cv_bridge::Exception &e)
  {
    RCLCPP_ERROR(rclcpp::get_logger("my_logger"), "cv_bridge exception: %s", e.what());
    return;
  }

  cv::resize(im, im, cv::Size(640, 480));
  cv::imshow("ros2_listener_webcam", im);
  cv::waitKey(10);
   
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("im_listener");
  //auto chatter_sub = node->create_subscription<sensor_msgs::msg::Image>(
  // "/chatter", 1, topic_callback);

  image_transport::ImageTransport it(node);
  auto sub = it.subscribe("/image_pub", 1, imageCallback);
  rclcpp::spin(node);
  //loop_rate.sleep();

  return 0;
}
