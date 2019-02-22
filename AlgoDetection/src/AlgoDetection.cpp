#include "AlgoDetection.h"
#include "detection_class.hpp"

Detector *detector;


int initDetector(std::string cfg_filename, std::string weight_filename)
{
	if (cfg_filename.empty() || weight_filename.empty())
	{
		throw std::runtime_error("cfg filename or weight filename is empty");
	}
	detector = new Detector(cfg_filename, weight_filename);
	return 0;
}

DECTECTIONDLL_API void releaseDetector()
{
	if (detector != NULL)
	{
		delete detector;
		detector = NULL;
	}
}

DECTECTIONDLL_API std::vector<boundingbox> detectDL(cv::Mat mat, float thresh/* = 0.2*/, bool use_mean/* = false*/)
{
	if (mat.data == NULL)
	{
		throw std::runtime_error("image is empty");
	}

	std::vector<bbox_t> detection = detector->detect(mat);
	std::vector<boundingbox> detectionDL;
	for (size_t i = 0; i < detection.size(); ++i)
	{
		boundingbox bbox;
		bbox.x = detection[i].x;
		bbox.y = detection[i].y;
		bbox.w = detection[i].w;
		bbox.h = detection[i].h;
		bbox.prob = detection[i].prob;
		bbox.obj_id = detection[i].obj_id;
		detectionDL.push_back(bbox);
	}
	return detectionDL;

}