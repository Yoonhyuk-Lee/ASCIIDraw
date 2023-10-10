#pragma once
#include <string>
#include <opencv2/core/types.hpp>

class MyImage
{
public:
	static void AnisotropicDiffusion(const cv::Mat& src, cv::Mat& dst);
	static void ResizeAndAdjustImage(const cv::Mat& src, cv::Mat& dst, cv::Size&& size);
	static void DrawImage(const cv::Mat& src);

private:
	static void AnisotropicDiffusion(PBYTE pbSrc, PBYTE pbDst, const int nWidth, const int nHeight, const float fK);
};

