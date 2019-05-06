/*************************************************
Copyright:chaoying
Author:Tong
Date:2019-02-22
Description:Object detection interface
**************************************************/

#pragma once
//#ifdef DECTECTIONDLL_EXPORTS
//#if defined(_MSC_VER)
//#define DECTECTIONDLL_API __declspec(dllexport)
//#else
//#define DECTECTIONDLL_API __attribute__((visibility("default")))
//#endif
//#else
//#if defined(_MSC_VER)
//#define DECTECTIONDLL_API __declspec(dllimport)
//#else
//#define DECTECTIONDLL_API
//#endif
//#endif
//
//#include <vector>
//#include <opencv2\opencv.hpp>
//
//struct boundingbox {
//	unsigned int x, y, w, h;    // (x,y) - top-left corner, (w, h) - width & height of bounding box
//	float prob;                    // confidence - probability that the object was found correctly
//	unsigned int obj_id;        // class of object - from range [0, classes-1]
//}; 
//
///*************************************************
//Function:       initDetector
//Description:    before do object detection, you must call initDetector once
//Input:          @param cfg_filename: a string, the cfg file path, absolute and
//                relative path are both ok
//@param weight_filename: a string, the weight file path, absolute and
//				relative path are both ok
//Output:    
//Return: error code.If cfg file path or weight file path is empty, return -1
//Others:
//*************************************************/
//DECTECTIONDLL_API int initDetector(std::string cfg_filename, std::string weight_filename);
//
///*************************************************
//Function:       releaseDetector
//Description:    release the object detector
//Input:         
//Output:
//Return: 
//Others:
//*************************************************/
//DECTECTIONDLL_API void releaseDetector();
//
///*************************************************
//Function:       detectDL
//Description:    do object detection
//Input:          @param image: an OpenCV Mat, the image to detect
//@param thresh: a float, if you want to detect more objects,set it a
//               big value,vice versa.The default value is 0.2.
//@param use_mean: a bool, if you want to subtract mean value from the
//               input image for data augmentation,set it to true.The 
//			   default value is false.
//Output:
//Return: a vector.The elements of the vector are the detected objects.
//        Each is a boundingbox struct defined above.
//Others:
//*************************************************/
//DECTECTIONDLL_API std::vector<boundingbox> detectDL(cv::Mat image, float thresh = 0.2, bool use_mean = false);

#include "detection.h"
#include "detection_class.hpp"

class AlgoDetection : public Detection
{
public:
	AlgoDetection(std::string cfgFilename, std::string weightFilename, int gpu_id = 0);

	int detect(cv::Mat image, std::vector<boundingbox>& detections, float thresh = 0.2, bool use_mean = false) override;

private:
	Detector detector;
};
