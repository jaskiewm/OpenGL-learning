#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

//Shader Constructor
Shader::Shader(const char* vertexFile, const char* fragmentFile) 
{
	std::string vertexCode = get_file_contents(vertexFile); //store file into strings
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str(); //store variables into character arrays
	const char* fragmentSource = fragmentCode.c_str();

	//-------Creating shaders (both vertex and fragment)-------//
	// Get shader object and it's reference
	// Create Shader -> attach source code to shader -> compile shader
	// Create shader program -> link shaders to program -> delete shaders

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//unsigned integer (positive integer)
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //Attach vertex shader source to vertex shader object
	glCompileShader(vertexShader); //Compiles the shader source into machine

	// Get shader object and it's reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//unsigned integer (positive integer)
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader); //Compiles the shader source into machine

	// Create the Shader Program Object and its references
	ID = glCreateProgram();

	//Attach vertex and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link all shaders together into the Shader Program
	glLinkProgram(ID);

	//Delete the shaders because they are in the program from above lines
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}