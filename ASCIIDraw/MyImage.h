#pragma once
#include <string>

namespace cv
{
	class Mat;
}

class MyImage
{
public:
	MyImage(const std::string& filePath);
	~MyImage();

	void DrawImage();

private:
	cv::Mat* m_pSrc;
};

