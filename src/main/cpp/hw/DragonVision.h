/*
 * DragonVision.h
 *
 * Created on: 2/16/2019
 *  Author: Aryan
 */

 #ifndef SRC_SUBSYS_COMPONENTS_DRAGONVISION_H_
#define SRC_SUBSYS_COMPONENTS_DRAGONVISION_H_
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


 class DragonVision {
private:
   cv::Mat image;
   cv::Mat outputimage;
   int width;
   int height;

 public:
   DragonVision();
   ~DragonVision();
   cv::Mat getImage();
   int getWidth(cv::Mat &image);
   int getHeight(cv::Mat &image);
   void showCircle(cv::Mat &image, int &width, int &height);
   void showCross(cv::Mat &image, int &width, int &height);
   void RotateVertically(cv::Mat &image, cv::Mat &outputimage);
};

 #endif 