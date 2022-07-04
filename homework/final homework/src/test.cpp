
#include <iostream>
#include <fstream>
#include <string>
#include <complex>
#include<math.h>
#include <cstdlib>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

/**
 * 存放位图的文件头部信息.
 */
typedef struct tagBITMAPFILEHEADER
{
  WORD  bfType;					/**< 文件类型, 永远是"BM". */
  DWORD bfSize;					/**< 文件大小, 单位字节. */
  WORD  bfReserved1;			/**< 保留, 永远是0. */
  WORD  bfReserved2;			/**< 保留, 永远是0. */
  DWORD bfOffBits;				/**< 图像数据相对文件头的偏移, 单位字节. */
} __attribute__((packed)) BITMAPFILEHEADER;

/**
 * 存放位图的文件信息.
 */
typedef struct tagBITMAPINFOHEADER
{
  DWORD        biSize;			/**< 本结构体大小, 单位字节. */
  LONG         biWidth;			/**< 图像宽度, 单位像素. */
  LONG         biHeight;		/**< 图像高度, 单位像素. */
  WORD         biPlanes;		/**< 图层, 基本是 1. */
  WORD         biBitCount;		/**< 颜色的数量, 24 bit 是真彩色. */
  DWORD        biCompression;	/**< 压缩格式, 基本是 0. */
  DWORD        biSizeImage;		/**< 图像大小, 单位是字节. */
  LONG         biXPelsPerMeter;	/**< X 分辨率. */
  LONG         biYPelsPerMeter;	/**< Y 分辨率. */
  DWORD        biClrUsed;		/**< 使用的颜色数. 真彩色是 0. */
  DWORD        biClrImportant;	/**< 重要的颜色, 一般是 0. */
} __attribute__((packed)) BITMAPINFOHEADER;

typedef struct {
  DWORD        bV5Size;
  LONG         bV5Width;
  LONG         bV5Height;
  WORD         bV5Planes;
  WORD         bV5BitCount;
  DWORD        bV5Compression;
  DWORD        bV5SizeImage;
  LONG         bV5XPelsPerMeter;
  LONG         bV5YPelsPerMeter;
  DWORD        bV5ClrUsed;
  DWORD        bV5ClrImportant;
  DWORD        bV5RedMask;
  DWORD        bV5GreenMask;
  DWORD        bV5BlueMask;
  DWORD        bV5AlphaMask;
  DWORD        bV5CSType;
	//  CIEXYZTRIPLE bV5Endpoints;
  DWORD        bV5GammaRed;
  DWORD        bV5GammaGreen;
  DWORD        bV5GammaBlue;
  DWORD        bV5Intent;
  DWORD        bV5ProfileData;
  DWORD        bV5ProfileSize;
  DWORD        bV5Reserved;
} __attribute__((packed)) BITMAPV5HEADER;

/*
 * @param _file 文件名, 带 bmp 后缀.
 * @param _w 图像宽度, 单位像素.
 * @param _h 图像高度, 单位像素.
 * @param _image 图像数据流, 单位字节.
 */
void build_bmp(std::string _file,
			   int _w,
			   int _h,
			   char *_image);
void build_bmp(std::string _file,
			   int _w,
			   int _h,
			   char *_image)
{
	int width = _w;
	int height = _h;
	std::ofstream outFile(_file.c_str(), std::ios::binary);
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = width;
	bmpInfoHeader.biHeight = height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = 24;
	bmpInfoHeader.biCompression = 0;
	bmpInfoHeader.biSizeImage = width * height * 3;
	bmpInfoHeader.biXPelsPerMeter = 2834;
	bmpInfoHeader.biYPelsPerMeter = 2834;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;
	((char*)(&bmpFileHeader.bfType))[0] = 'B';
	((char*)(&bmpFileHeader.bfType))[1] = 'M';
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = bmpInfoHeader.biSize + sizeof(BITMAPFILEHEADER);
	bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + bmpInfoHeader.biSizeImage;
	outFile.write(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BITMAPFILEHEADER));
	outFile.write(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BITMAPINFOHEADER));
	outFile.write(_image, bmpInfoHeader.biSizeImage);
	outFile.close();
};

bool flag_disconvergence = false;
bool flag_stop = false;

void Julia(std::complex<double> iteration_point,std::complex<double> iteration_const ,double N)
{
	int iteration_times=0;
	if (iteration_times == N)
		flag_disconvergence = true;
	if (std::abs(iteration_point) > 2.0)
		flag_stop = true;
	while (!flag_stop)
		{
			iteration_point = iteration_point * iteration_point + iteration_const;
			iteration_times++;
			if (iteration_times == N)
				{
					flag_disconvergence = true;
					return;
				}
			if (std::abs(iteration_point) > 2.0)
				{
					flag_stop = true;
					return;
				}
		}
}
int main(int argc, char *argv[])
{
	char s[100];
	
	double fx,fy;
	std::cin>>s;
	std::cin>>fx>>fy;
	int width=1920;
	int height=1080;
	double dimension = 5.0;
	double perdim=height/width*dimension;
	double lpp=dimension * 2.0 / width;
	double ox =  - dimension;
	double oy =  - dimension / width * height;
	char *cache = new char[width * height * 3];
	double N=1000;
	std::complex<double> iteration_const{fx, fy};
	for (double j = 0; j < height; j++)
		for (double i = 0; i < width; i++)
		{
			flag_disconvergence = false;
			flag_stop = false;
			double x = ox + lpp * i;
			double y = oy + lpp * j;
			std::complex<double> iteration_point {x, y};
			int pos = width * j + i; 
			Julia(iteration_point,iteration_const,N);
			if(flag_disconvergence)
			{
				cache[pos * 3] = 255;
				cache[pos * 3 + 1] = 255;
				cache[pos * 3 + 2] = 255;
			}
			else
			{
				cache[pos * 3] = 0;
				cache[pos * 3 + 1] = 0;
				cache[pos * 3 + 2] = 0;
			}
		}
	build_bmp(s, width, height, cache);
	delete [] cache;
	return 0;
}

