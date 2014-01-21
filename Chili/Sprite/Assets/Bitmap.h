#pragma once
#include <d3d9.h>

struct BitmapFileHeader
{
   unsigned int fileSize;                       /* File size in bytes          */
   unsigned short reserved1, reserved2;
   unsigned int offsetToPixelData;                     /* Offset to image data, bytes */
};

struct BitmapInfoHeader
{
   unsigned int headerSize;               /* Header size in bytes      */
   int width,height;                /* Width and height of image */
   unsigned short planes;       /* Number of colour planes   */
   unsigned short bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int nColors;           /* Number of colours         */
   unsigned int importantColors;   /* Important colours         */
};

struct Pixel24
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

void LoadBmp(const char* filename, D3DCOLOR* surface);