#include "AlgoDetectionManager.h"
#include "AlgoDetection.h"

Detection* AlgoDetectionManager::create(std::string cfgFilename, std::string weightFilename, int gpu_id /*= 0*/)
{
	Detection* detector = new AlgoDetection(cfgFilename, weightFilename, gpu_id);

	return detector;
}

void AlgoDetectionManager::destroy(Detection* detector)
{
	delete detector;
}
