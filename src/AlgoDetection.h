/*************************************************
Copyright:chaoying
Author:Tong
Date:2019-02-22
Description:Object detection interface
**************************************************/

#pragma once

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
