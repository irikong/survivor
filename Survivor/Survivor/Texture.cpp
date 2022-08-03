#include "Texture.h"
#include "GL/glew.h"
#include "SOIL/SOIL.h"

Texture::Texture() :
	mTextureID(0),
	mWidth(0),
	mHeight(0)
{

}

Texture::~Texture()
{
}

bool Texture::Load(const std::string& filePath)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);
	
	if (image == nullptr) return false;

	int format = channels == 4 ? GL_RGBA : GL_RGB;

	glGenTextures(1, &mTextureID); // textureCount, textureID
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 축소할 때 밉맵 사용
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
