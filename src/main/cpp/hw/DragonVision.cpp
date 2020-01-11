/*
 * DragonVision.cpp
 *
 * Created on: 2/16/2019
 *  Author: Aryan
 */

 #include <hw/DragonVision.h>

 //Constructor
DragonVision::DragonVision()
{

 }

 //Destructor
DragonVision::~DragonVision()
{

 }

 cv::Mat  DragonVision::getImage()
{
    return image;
}

 int DragonVision::getWidth(cv::Mat &image)
{
    return image.size().width;
}

 int DragonVision::getHeight(cv::Mat &image)
{
    return image.size().height;
}

 void DragonVision::showCircle(cv::Mat &image, int &width, int &height)
{
    //create circle in the middle of the screen
    int radius= 40;
    cv::Scalar lightgreen(0,255,0);
    cv::Point center(width/2, height/2);
    cv::circle(image, center, radius, lightgreen, 3, 8);
}

 void DragonVision::showCross(cv::Mat &image, int &width, int &height)
{
    //create cross in the middle of the screen
    cv::Scalar lightgreen(0,255,0);
    cv::Point p1(width/2-40, height/2);
    cv::Point p2(width/2+40, height/2);
    cv::Point p3(width/2, height/2-40);
    cv::Point p4(width/2, height/2+40);
    cv::line(image,p1,p2,lightgreen, 3);//horizontal line
    cv::line(image,p3,p4,lightgreen, 3);//vertical line
}

  void DragonVision::RotateVertically(cv::Mat &image, cv::Mat &outputimage)
 {
     cv::flip(image, outputimage, 0);
 } 