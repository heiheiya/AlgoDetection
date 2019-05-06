#include <iostream>

#include "AlgoDetection.h"
#include "common.h"

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
		bbox.track_id = detection[i].track_id;
		detections.push_back(bbox);
	}
	return CYAL_DETECTION_SUCCESS;
}
