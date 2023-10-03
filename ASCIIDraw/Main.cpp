#include <stdio.h>
#include <Windows.h>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

#include "MyImage.h"
#include "ASCIIConverter.h"

void SetFrame()
{
	system("mode con: cols=200 lines=200");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;                  
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Terminal"); 
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

int main()
{
	SetFrame();

	auto src = MyImage("src.jpg");
	src.DrawImage();

	system("PAUSE");
	return 0;
}