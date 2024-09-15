#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

class Texture2D
{
private:
public:
    unsigned int m_width, m_height;
    unsigned int m_internalFormat;
    unsigned int m_imageFormat;
    // texture config
    unsigned int m_warpS;
    unsigned int m_warpT;
    unsigned int m_filterMin;
    unsigned int m_filterMax;

    unsigned int m_ID; // Texture's ID to be used
    Texture2D(); // Empty default constructor made to make linker happy - DO NOT USE!
    Texture2D(int, int, unsigned char*, bool);
    ~Texture2D();
    void Bind() const;
};


#endif // TEXTURE2D_H