#include "Texture2D.h"

Texture2D::Texture2D()
{
    // Set inital variables (to have warnings go away)
    m_ID = 0;
    m_width = 0;
    m_height = 0;
    m_internalFormat = GL_RGB;
    m_imageFormat = GL_RGB;
    m_warpS = GL_REPEAT;
    m_warpT = GL_REPEAT;
    m_filterMin = GL_LINEAR;
    m_filterMax = GL_LINEAR;
}

Texture2D::Texture2D(int width, int height, unsigned char* data, bool alpha) : m_width(width), m_height(height), m_internalFormat(GL_RGB), 
m_imageFormat(GL_RGB), m_warpS(GL_REPEAT), m_warpT(GL_REPEAT), m_filterMin(GL_LINEAR), m_filterMax(GL_LINEAR)
{
    // Generate the texture with its own ID
    glGenTextures(1, &m_ID);
    // If we have alpha value, override the current initalize values to use RGBA values
    if (alpha)
    {
        m_internalFormat = GL_RGBA;
        m_imageFormat = GL_RGBA;
    }
    // Ensure the texture is bind to set parameters
    glBindTexture(GL_TEXTURE_2D, m_ID);
    // Create texture using image data made with STBI
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);
    // Set texture parameters with the following member variables initalized
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
    // Unbind texture once we set parameters
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
}

void Texture2D::Bind() const
{
    // Use texture associated with its ID
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
