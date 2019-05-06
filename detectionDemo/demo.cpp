#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include "../src/detection_class.hpp"
#include "../src/detection.h"
#include "../src/AlgoDetectionManager.h"

#pragma comment(lib, "AlgoDetection.lib")
#pragma comment(lib, "opencv_world320.lib")


void show_console_result(std::vector<boundingbox> const result_vec, std::vector<std::string> const obj_names)
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

void draw_boxes(cv::Mat mat_img, std::vector<boundingbox> result_vec, std::vector<std::string> obj_names, int current_det_fps = -1, int current_cap_fps = -1)
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
	std::string name_file1 = "data/chaoyingDataset1.names";
	std::string cfg_file1 = "data/yolov3-chaoyingDataset1.cfg";
	std::string weights_file1 = "data/yolov3-chaoyingDataset1_50600.weights";
	std::string file_name1;

	float const thresh = 0.2;

	Detection* detector1 = AlgoDetectionManager::create(cfg_file1, weights_file1);
	auto objNames1 = objects_names_from_file(name_file1);


	while (true)
	{
		std::cout << "input image filename1: ";
		if (file_name1.size() == 0)
		{
			std::cin >> file_name1;
		}
		if (file_name1 == "q")
		{
			break;
		}

		std::string const fileExt = file_name1.substr(file_name1.find_last_of(".") + 1);
		if (fileExt == "jpg" || fileExt == "JPEG" || fileExt == "png")
		{
			cv::Mat matImg = cv::imread(file_name1);

			auto start = std::chrono::steady_clock::now();
			std::vector<boundingbox> resultVec;
			int err = detector1->detect(matImg, resultVec);
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
			draw_boxes(matImg, resultVec, objNames1);
			std::string outName = file_name1.substr(0, file_name1.rfind("."));
			outName = outName + "_prediction.png";
			//std::cout << outName << std::endl;
			cv::imwrite(outName, matImg);
			cv::namedWindow("detection", cv::WINDOW_NORMAL);
			cv::imshow("detection", matImg);
			show_console_result(resultVec, objNames1);
			cv::waitKey(0);
		} 
		else
		{
			std::cout << " Finish soon!!!" << std::endl;
		}
		file_name1.clear();
	}

	AlgoDetectionManager::destroy(detector1);

	std::string name_file2 = "data/chaoyingDataset2.names";
	std::string cfg_file2 = "data/yolov3-tiny-chaoyingDataset2.cfg";
	std::string weights_file2 = "data/yolov3-tiny-chaoyingDataset2_46000.weights";
	std::string file_name2;

	Detection* detector2 = AlgoDetectionManager::create(cfg_file2, weights_file2);
	auto objNames2 = objects_names_from_file(name_file2);

	while (true)
	{
		std::cout << "input image filename2: ";
		if (file_name2.size() == 0)
		{
			std::cin >> file_name2;
		}
		if (file_name2 == "q")
		{
			break;
		}

		std::string const fileExt = file_name2.substr(file_name2.find_last_of(".") + 1);
		if (fileExt == "jpg" || fileExt == "JPEG" || fileExt == "png")
		{
			cv::Mat matImg = cv::imread(file_name2);

			auto start = std::chrono::steady_clock::now();
			std::vector<boundingbox> resultVec;
			int err = detector2->detect(matImg, resultVec);
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> time = end - start;
			std::cout << "Time: " << time.count() << " sec" << std::endl;

			for (size_t i = 0; i < resultVec.size(); ++i)
			{
				std::cout << "object " << i << std::endl;
				std::cout << "obj id: " << resultVec[i].obj_id << " bbox: "
					<< resultVec[i].x << " " << resultVec[i].y
					<< " " << resultVec[i].w << " " << resultVec[i].h
					<< " score: " << resultVec[i].prob << std::endl;
			}
			draw_boxes(matImg, resultVec, objNames2);
			std::string outName = file_name2.substr(0, file_name2.rfind("."));
			outName = outName + "_prediction.png";
			cv::imwrite(outName, matImg);
			cv::namedWindow("detection", cv::WINDOW_NORMAL);
			cv::imshow("detection", matImg);
			show_console_result(resultVec, objNames2);
			cv::waitKey(0);
		}
		else
		{
			std::cout << " Finish soon!!!" << std::endl;
		}
		file_name2.clear();
	}

	AlgoDetectionManager::destroy(detector2);
}