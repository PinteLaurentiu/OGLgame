#ifndef TEXTURE_H
#define TEXTURE_H

#include <fstream>

struct png_struct_def;
struct png_info_def;
typedef long unsigned int size_t;
typedef struct png_struct_def png_struct;
typedef struct png_info_def png_info;
typedef png_struct* png_structp;
typedef png_info* png_infop;
typedef unsigned char byte;

class Texture
{
public:
	Texture();
	Texture(const char* file);
	Texture(const Texture& tx);
	~Texture();
	Texture& operator= (const Texture& tx);
	void set();
private:
	class RCutil;
	class ReadDataHandle;
	class RawImageData;
	RCutil* data;
	void readInfoFromPng(png_structp pngPointer, png_infop pngInfoPointer);
	void readDataFromPng(png_structp pngPointer, png_infop pngInfoPointer, RawImageData& rawdata);
};

class Texture::RCutil
{
public:
	unsigned int refCount = 1;
	unsigned int textureID = 0;
	unsigned int width = 0;
	unsigned int height = 0;
};

class Texture::ReadDataHandle
{
public:
	static void readPngDataCallback(png_structp pngPointer, byte* rawData, size_t readLength);
    ReadDataHandle(byte* data, int size);
    ~ReadDataHandle();
    byte* data;
    unsigned int size;
    unsigned int offset;
};

class Texture::RawImageData
{
public:
	byte* data = nullptr;
	unsigned int size = 0;
};

#endif /* TEXTURE_H */
