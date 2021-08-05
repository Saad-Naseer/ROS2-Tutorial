#include <rclcpp/rclcpp.hpp>
//#include <sensor_msgs/msg/image.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("im_talker");
    //auto chatter_pub = node->create_publisher<sensor_msgs::msg::Image>("image_pub", 1000);

    image_transport::ImageTransport it(node);
    auto chatter_pub = it.advertise("image_pub", 1000);

    cv::VideoCapture cap(0);
    //rclcpp::Rate loop_rate(10);
    rclcpp::Rate loop_rate(1000);
    sensor_msgs::msg::Image::SharedPtr im_msg;
    while (rclcpp::ok())
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        im_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "rgb8", frame).toImageMsg();
        chatter_pub.publish(im_msg);
        cv::resize(frame, frame, cv::Size(640, 480));
        cv::imshow("ros2_webcam", frame);
        if (cv::waitKey(10) == 27)
            break;

        // chatter_pub->publish(msg);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
    cap.release();
    return 0;
}
