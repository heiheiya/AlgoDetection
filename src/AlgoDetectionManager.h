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

#include "detection.h"

class DECTECTIONDLL_API AlgoDetectionManager
{
public:

	//////////////////////////////////////////////////////////////////////////
	//Function:       create
	//Description:    create a detection object
	//Input:          @param cfgFilename: a string, the relate or absolute path of cfg
	//@param weightFilename:  a string, the relate or absolute path of weight
	//@param gpu_id: a int, which gpu you want to use, the default is 0
	//               big value,vice versa.The default value is 0.2.
	//Output:
	//Return: a detection object
	//Others:
	//////////////////////////////////////////////////////////////////////////
	static Detection* create(std::string cfgFilename, std::string weightFilename, int gpu_id = 0);

	//////////////////////////////////////////////////////////////////////////
	//Function:       destroy
	//Description:    release thr detection object
	//Input:          @param detector: an detection object
	//Output:
	//Return: 
	//Others:
	//////////////////////////////////////////////////////////////////////////
	static void destroy(Detection* detector);
};