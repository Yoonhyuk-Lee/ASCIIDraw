#pragma once


constexpr int ASCII_TABLE_SIZE = 91;

static const char ASCII_TABLE[ASCII_TABLE_SIZE] =
{
		'`', '.', '-', '\'', ':', '_', ',', '^', '=', ';', '>',
		'<', '+', '!', 'r', 'c', '*', '/', 'z', '?', 's',
		'L', 'T', 'v', ')', 'J', '7', '(', '|', 'F', 'i',
		'{', 'C', '}', 'f', 'I', '3', '1', 't', 'l', 'u',
		'[', 'n', 'e', 'o', 'Z', '5', 'Y', 'x', 'j', 'y',
		'a', ']', '2', 'E', 'S', 'w', 'q', 'k', 'P', '6',
		'h', '9', 'd', '4', 'V', 'p', 'O', 'G', 'b', 'U',
		'A', 'K', 'X', 'H', 'm', '8', 'R', 'D', '#', '$',
		'B', 'g', '0', 'M', 'N', 'W', 'Q', '%', '&', '@'
};

class ASCIIConverter
{
public:	
	static char norm2ASCII(float fVal);
};
