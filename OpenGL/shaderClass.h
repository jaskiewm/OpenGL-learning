#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// ID is the shader program reference
		GLuint ID;

		// Constructor builds shader program from fragment and vertex shader
		Shader(const char* vertexFile, const char* fragmentFile);

		// Activate shader program
		void Activate();

		// Delete shader program
		void Delete();

	private:
		//Checks if the shaders compiled properly
		void compileErrors(unsigned int shader, const char* type);
};

#endif