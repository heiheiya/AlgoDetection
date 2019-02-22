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

#include <vector>
#include <opencv2\opencv.hpp>

struct boundingbox {
	unsigned int x, y, w, h;    // (x,y) - top-left corner, (w, h) - width & height of bounded box
	float prob;                    // confidence - probability that the object was found correctly
	unsigned int obj_id;        // class of object - from range [0, classes-1]
}; 

DECTECTIONDLL_API int initDetector(std::string cfg_filename, std::string weight_filename);
DECTECTIONDLL_API void releaseDetector();
DECTECTIONDLL_API std::vector<boundingbox> detectDL(cv::Mat mat, float thresh = 0.2, bool use_mean = false);

