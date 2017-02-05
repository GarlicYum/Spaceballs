#pragma once
#include "Graphics.h"

struct BitmapFileHeader
{
	unsigned int fileSize;
	unsigned short reserved1, reserved2;
	unsigned int offsetToPixelData;
};

struct BitmapInfoHeader
{
	unsigned int headerSize;
	int width, height;
	unsigned short planes;
	unsigned short bits;
	unsigned int compression;
	unsigned int imageSize;
	int xResolution, yResolution;
	unsigned int nColors;
	unsigned int importantColours;
};

struct Pixel24
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

void LoadBmp(const char* filename, Color* surface);