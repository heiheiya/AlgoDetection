#include <iostream>

#include "AlgoDetection.h"
#include "common.h"
//#include "detection_class.hpp"

//Detector *detector;
//
//int initDetector(std::string cfg_filename, std::string weight_filename)
//{
//	if (cfg_filename.empty() || weight_filename.empty())
//	{
//		std::cout<<"cfg filename or weight filename is empty"<<std::endl;
//		return -1;
//	}
//	detector = new Detector(cfg_filename, weight_filename);
//	return 0;
//}
//
//DECTECTIONDLL_API void releaseDetector()
//{
//	if (detector != NULL)
//	{
//		delete detector;
//		detector = NULL;
//		std::cout << "object detector released!" << std::endl;
//	}
//}
//
//DECTECTIONDLL_API std::vector<boundingbox> detectDL(cv::Mat image, float thresh/* = 0.2*/, bool use_mean/* = false*/)
//{
//	std::vector<boundingbox> detectionDL;
//	if (image.data == NULL)
//	{
//		throw std::runtime_error("image is empty");
//		return detectionDL;
//	}
//
//	std::vector<bbox_t> detection = detector->detect(image);	
//	for (size_t i = 0; i < detection.size(); ++i)
//	{
//		boundingbox bbox;
//		bbox.x = detection[i].x;
//		bbox.y = detection[i].y;
//		bbox.w = detection[i].w;
//		bbox.h = detection[i].h;
//		bbox.prob = detection[i].prob;
//		bbox.obj_id = detection[i].obj_id;
//		detectionDL.push_back(bbox);
//	}
//	return detectionDL;
//
//}

AlgoDetection::AlgoDetection(std::string cfgFilename, std::string weightFilename, int gpu_id/* = 0*/)
	:detector(cfgFilename, weightFilename, gpu_id)
{

}

int AlgoDetection::detect(cv::Mat image, std::vector<boundingbox>& detections, float thresh /*= 0.2*/, bool use_mean /*= false*/)
{
	detections.clear();
	if (image.data == NULL)
	{
		std::cout << "ERROR: Image is empty..." << std::endl;;
		return CYAL_DETECTION_IMAGE_EMPTY_ERROR;
	}

	std::vector<bbox_t> detection = detector.detect(image);
	for (size_t i = 0; i < detection.size(); ++i)
	{
		boundingbox bbox;
		bbox.x = detection[i].x;
		bbox.y = detection[i].y;
		bbox.w = detection[i].w;
		bbox.h = detection[i].h;
		bbox.prob = detection[i].prob;
		bbox.obj_id = detection[i].obj_id;
		detections.push_back(bbox);
	}
	return CYAL_DETECTION_SUCCESS;
}
