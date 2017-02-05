#include "Bitmap.h"
#include <stdio.h>
#include <assert.h>

void LoadBmp(const char * filename, Color * surface)
{
	FILE* bmpFile = fopen(filename, "rb");
	char signature[2];
	fread(signature, sizeof(char), 2, bmpFile);
	assert(signature[0] == 'B' && signature[1] == 'M');

	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);

	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);

	fclose(bmpFile);
}
