#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "../AlgoDetection/src/detection_class.hpp"
#include "../AlgoDetection/src/AlgoDetection.h"

#pragma comment(lib, "opencv_world320.lib")


void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names)
{
	for (auto &i : result_vec)
	{
		if (obj_names.size() > i.obj_id)
		{
			std::cout << obj_names[i.obj_id] << " - ";
		}
		std::cout << "obj_id = " << i.obj_id << ", x = " << i.x << ", y = " << i.y << ", w = " << i.w << ", h = "
			<< i.h << std::setprecision(3) << ", prob = " << i.prob << std::endl;
	}
}

void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names, int current_det_fps = -1, int current_cap_fps = -1)
{
	int const colors[6][3] = { {1,0,1}, {0,0,1}, {0,1,1}, {0,1,0}, {1,1,0}, {1,0,0} };

	for (auto &i : result_vec)
	{
		cv::Scalar color = obj_id_to_color(i.obj_id);
		cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
		if (obj_names.size() > i.obj_id)
		{
			std::string obj_name = obj_names[i.obj_id];
			if (i.track_id > 0)
			{
				obj_name += "-" + std::to_string(i.track_id);
			}
			cv::Size const textSize = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
			int const maxWidth = (textSize.width > i.w + 2) ? textSize.width : (i.w + 2);
			cv::rectangle(mat_img, cv::Point2f(std::max((int)i.x - 1, 0), std::max((int)i.y - 30, 0)),
				cv::Point2f(std::min((int)i.x + maxWidth, mat_img.cols - 1), std::min((int)i.y, mat_img.rows - 1)),
				color, CV_FILLED, 8, 0);
			putText(mat_img, obj_name, cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(0, 0, 0), 2);
		}
	}

	if (current_det_fps >= 0 && current_cap_fps >= 0)
	{
		std::string fpsStr = "FPS detection: " + std::to_string(current_det_fps) + "   FPS capture: " + std::to_string(current_cap_fps);
		putText(mat_img, fpsStr, cv::Point2f(10, 20), cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, cv::Scalar(50, 255, 0), 2);
	}
}

int main(int argc, char *argv[])
{
	std::string name_file = "data/light.names";
	std::string cfg_file = "data/yolov3-light.cfg";
	std::string weights_file = "data/yolov3-light_100000.weights";
	std::string file_name;

	float const thresh = 0.2;

	initDetector(cfg_file, weights_file);
	auto objNames = objects_names_from_file(name_file);

	while (true)
	{
		std::cout << "input image filename: ";
		if (file_name.size() == 0)
		{
			std::cin >> file_name;
		}
		if (file_name.size() == 0)
		{
			break;
		}

		std::string const fileExt = file_name.substr(file_name.find_last_of(".") + 1);
		if (fileExt == "jpg" || fileExt == "JPEG" )
		{
			cv::Mat matImg = cv::imread(file_name);

			auto start = std::chrono::steady_clock::now();
			std::vector<boundingbox> resultVec = detectDL(matImg);
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> time = end - start;
			std::cout << "Time: " << time.count() << " sec" << std::endl;

			for (size_t i = 0; i < resultVec.size(); ++i)
			{
				std::cout << "object " << i << std::endl;
				std::cout<<"obj id: "<< resultVec[i].obj_id << " bbox: "
					<<resultVec[i].x << " "<< resultVec[i].y
					<< " " << resultVec[i].w << " " << resultVec[i].h
					<<" score: "<< resultVec[i].prob<<std::endl;
			}
			//draw_boxes(matImg, resultVec, objNames);
			//cv::namedWindow("detection", cv::WINDOW_NORMAL);
			//cv::imshow("detection", matImg);
			//show_console_result(resultVec, objNames);
			//cv::waitKey(0);
		} 
		else
		{
			std::cout << " Finish soon!!!" << std::endl;
		}
		file_name.clear();
	}
}