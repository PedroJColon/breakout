#include "Texture2D.h"

Texture2D::Texture2D() : m_width(0), m_height(0), m_interalFormat(GL_RGB), m_imageFormat(GL_RGB), m_warpS(GL_REPEAT), m_warpT(GL_REPEAT),
m_filterMin(GL_LINEAR), m_filterMax(GL_LINEAR)
{
    glGenTextures(1, &m_ID);
}

Texture2D::~Texture2D()
{
}

void Texture2D::Generate(int width, int height, unsigned char* data)
{
    m_width = width;
    m_height = height;

    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_interalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_warpS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_warpT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
