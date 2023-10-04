#pragma once
#include <string>
#include <opencv2/core/types.hpp>

class MyImage
{
public:
	static void ResizeAndAdjustImage(const cv::Mat& src, cv::Mat& dst, cv::Size&& size);
	static void DrawImage(const cv::Mat& src);
};

