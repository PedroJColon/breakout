#ifndef FILEREADER_H
#define FILEREADER_H

// NOTE: String is used to abstract away usage of raw pointers for sake of memory safety
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileReader
{
public:
	// Loads vertex and fragment shaders from the file given. Geometry shader support down the line?
	static void LoadShaderFromFile(std::string, std::string, std::string&, std::string&);
	// Loads Image from file given
	static void LoadImageFromFile(std::string, bool, int&, int&, int&, unsigned char*);
	// Utility for Freeing Image Data after its use
	static void FreeImageData(unsigned char*);
	// Additional Functions to add
	// LoadAudioFile();
	//
private:
	FileReader() {};
};

#endif // !FILEREADER_H