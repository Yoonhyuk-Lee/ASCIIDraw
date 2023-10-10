#include <stdio.h>
#include <Windows.h>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

#include "MyImage.h"
#include "ASCIIConvertLUT.hpp"

#include "opencv2\opencv.hpp"

void SetFrame()
{
	system("mode con: cols=256 lines=200");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 6;
	cfi.dwFontSize.Y = 6;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"³ª´®°íµñÄÚµù"); 
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

int main()
{
	SetFrame();

    cv::Mat frame;

    cv::VideoCapture cap(0);
    while (cap.isOpened())
    {
        auto start = std::chrono::system_clock::now();
        
        cap >> frame;
        if (frame.empty())
            continue;

        
        MyImage::ResizeAndAdjustImage(frame, frame, { 256, 144 });
        MyImage::AnisotropicDiffusion(frame, frame);
        MyImage::DrawImage(frame);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

        std::cout << std::endl << std::endl;
        std::cout << std::to_string(1000.f / duration.count()) << " [fps]" << std::endl;
    }
    cap.release();
    
	return 0;
}