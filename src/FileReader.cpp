#include "FileReader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void FileReader::LoadShaderFromFile(std::string vertexFile, std::string fragmentFile, std::string& vertexCode, std::string& fragmentCode)
{
    std::ifstream vertexFileStream;
    std::ifstream fragmentFileStream;

    // Ifstream can throw exception
    vertexFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexFileStream.open(vertexFile);
        fragmentFileStream.open(fragmentFile);
        std::stringstream vertexStringStream, fragmentStringStream;
        // Read file buffer and output into string streams
        vertexStringStream << vertexFileStream.rdbuf();
        fragmentStringStream << fragmentFileStream.rdbuf();
        // Once we are done reading our file, close it!
        vertexFileStream.close();
        fragmentFileStream.close();
        // Convert our string stream into String class
        vertexCode = vertexStringStream.str();
        fragmentCode = fragmentStringStream.str();

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
    }
}

void FileReader::LoadImageFromFile(std::string imageFile, bool alpha, int& width, int &height, int& nrChannels, unsigned char* data)
{
    const char* file = imageFile.c_str(); // Convert string to const char pointer
    // With the reference variables, sent the variables to stbi_load to carry it over to wherever this function is being called
    data = stbi_load(file, &width, &height, &nrChannels, 0); // load file using stbi library
    // Check if data was sucessfully loaded
    if (data)
    {
        std::cout << "Image has been loaded\n" << std::endl;
    }
    else
    {
        std::cout << "Unable to Load Image\n" << std::endl;
    }
}

void FileReader::FreeImageData(unsigned char* data)
{
    stbi_image_free(data);
}
