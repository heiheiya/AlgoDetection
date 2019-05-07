/*************************************************
Copyright:chaoying
Author:Tong
Date:2019-05-06
Description:Object detection interface
**************************************************/

#pragma once
#ifdef DECTECTIONDLL_EXPORTS
#if defined(_MSC_VER)
#define DECTECTIONDLL_API __declspec(dllexport)
#else
#define DECTECTIONDLL_API __attribute__((visibility("default")))
#endif
#else
#if defined(_MSC_VER)
#define DECTECTIONDLL_API __declspec(dllimport)
#else
#define DECTECTIONDLL_API
#endif
#endif

#include <opencv2\opencv.hpp>

struct boundingbox {
	unsigned int x, y, w, h;    // (x,y) - top-left corner, (w, h) - width & height of bounding box
	float prob;                    // confidence - probability that the object was found correctly
	unsigned int obj_id;        // class of object - from range [0, classes-1]
	unsigned int track_id;        // tracking id for video (0 - untracked, 1 - inf - tracked object)
}; 


class DECTECTIONDLL_API Detection
{
public:
	virtual ~Detection() {};

	//////////////////////////////////////////////////////////////////////////
	//Function:       detect
	//Description:    do object detection
	//Input:          @param image: an OpenCV Mat, the image to detect
	//@param detections: a vector.The elements of the vector are the detected objects.
	//        Each is a boundingbox struct defined above.
	//@param thresh: a float, if you want to detect more objects,set it a
	//               big value,vice versa.The default value is 0.2.
	//@param use_mean: a bool, if you want to subtract mean value from the
	//               input image for data augmentation,set it to true.The 
	//			   default value is false.
	//Output:
	//Return: a int.Error code.
	//Others:
	//////////////////////////////////////////////////////////////////////////
	virtual int detect(cv::Mat image, std::vector<boundingbox>& detections, float thresh = 0.2, bool use_mean = false) = 0;
};