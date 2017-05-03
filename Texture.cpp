#include "Texture.h"
#include <fstream>
#include <png.h>
#include "glhs.h"

/** FIXME **/
#include <cassert>
/** FIXME **/

using namespace std;

Texture::Texture() : data(nullptr) {}

Texture::Texture(const char* file) : data(new RCutil())
{
	ifstream fin(file);
	if (!fin)
		assert(false);
	fin.seekg(0, ios::end);
	size_t size = fin.tellg();
	fin.seekg(0, ios::beg);
	byte* buffer = new byte[size];
	fin.read((char*)buffer, size);
	if (fin.fail())
		assert(false);
	fin.close();

	assert(png_check_sig(buffer, 8));
	png_structp pngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	assert(pngPointer);
	png_infop pngInfoPointer = png_create_info_struct(pngPointer);
	assert(pngInfoPointer);
	ReadDataHandle handle(buffer, size);
	png_set_read_fn(pngPointer, &handle, ReadDataHandle::readPngDataCallback);
	if (setjmp(png_jmpbuf(pngPointer)))
	    assert(false);
	readInfoFromPng(pngPointer, pngInfoPointer);
	RawImageData rawdata;
	readDataFromPng(pngPointer, pngInfoPointer, rawdata);
	png_read_end(pngPointer, pngInfoPointer);
	png_destroy_read_struct(&pngPointer, &pngInfoPointer, nullptr);
	delete [] buffer;

	glGenTextures(1, &(data->textureID));
	glBindTexture(GL_TEXTURE_2D, data->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawdata.data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] rawdata.data;
}

Texture::Texture(const Texture& tx) : data(tx.data)
{
	if (data != nullptr)
		data->refCount++;
}

Texture::~Texture()
{
	if (data == nullptr)
		return;

	data->refCount--;
	if (data->refCount > 0)
		return;

	glDeleteTextures(1, &(data->textureID));
	delete data;
	data = nullptr;
}

Texture& Texture::operator =(const Texture& tx)
{
	if (tx.data == data)
		return *this;

	if (data != nullptr)
	{
		data->refCount--;
		if (data->refCount <= 0)
		{
			glDeleteTextures(1, &(data->textureID));
			delete data;
			data = nullptr;
		}
	}

	data = tx.data;
	if (data != nullptr)
		data->refCount++;

	return *this;
}

void Texture::readInfoFromPng(png_structp pngPointer, png_infop pngInfoPointer)
{
	int bitDepth, colorType;
	png_read_info(pngPointer, pngInfoPointer);
	png_get_IHDR(pngPointer, pngInfoPointer, &(data->width), &(data->height), &bitDepth, &colorType, nullptr, nullptr, nullptr);
	if (png_get_valid(pngPointer, pngInfoPointer, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(pngPointer);

	if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
		png_set_expand_gray_1_2_4_to_8(pngPointer);

	if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
	    png_set_gray_to_rgb(pngPointer);

	if (colorType == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(pngPointer);

	if (colorType == PNG_COLOR_TYPE_PALETTE || colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY)
		png_set_add_alpha(pngPointer, 0xFF, PNG_FILLER_AFTER);

	if (bitDepth < 8)
		png_set_packing(pngPointer);
	else if (bitDepth == 16)
		png_set_scale_16(pngPointer);

	png_read_update_info(pngPointer, pngInfoPointer);
	colorType = png_get_color_type(pngPointer, pngInfoPointer);
	if (colorType != PNG_COLOR_TYPE_RGBA)
		assert(false);
}

void Texture::readDataFromPng(png_structp pngPointer, png_infop pngInfoPointer, RawImageData& rawdata)
{
	const unsigned int rowSize = png_get_rowbytes(pngPointer, pngInfoPointer);
	rawdata.size = rowSize * data->height;
	rawdata.data = new unsigned char[rawdata.size];
	byte* rowPtrs[data->height];
	for (unsigned int i = 0; i < data->height; i++)
	{
		rowPtrs[i] = rawdata.data + i * rowSize;
	}
	png_read_image(pngPointer, &rowPtrs[0]);
}

void Texture::ReadDataHandle::readPngDataCallback(png_structp pngPointer, byte* rawData, size_t readLength)
{
	ReadDataHandle* handle = (ReadDataHandle*)png_get_io_ptr(pngPointer);
	byte* start = handle->data + handle->offset;
	byte* end =  handle->data + handle->offset + readLength;
	for (; start != end; start++)
	{
		*rawData = *start;
		rawData++;
	}
	handle->offset += readLength;
}

Texture::ReadDataHandle::ReadDataHandle(byte* data, int size) : data(data), size(size), offset(0) {}

Texture::ReadDataHandle::~ReadDataHandle() {};

void Texture::set() {
	glBindTexture(GL_TEXTURE_2D, data->textureID);
}
