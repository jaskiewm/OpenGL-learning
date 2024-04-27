#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
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
	//store file into strings
	std::string vertexCode = get_file_contents(vertexFile); 
	std::string fragmentCode = get_file_contents(fragmentFile);

	//store variables into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//-------Creating shaders (both vertex and fragment)-------//
	// Get shader object and it's reference
	// Create Shader -> attach source code to shader -> compile shader
	// Create shader program -> link shaders to program -> delete shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//unsigned integer (positive integer)
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //Attach vertex shader source to vertex shader object
	glCompileShader(vertexShader); //Compiles the shader source into machine

	// Get shader object and it's reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //unsigned integer (positive integer)
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

// Activates shader program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes shader program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader :: compileErrors(unsigned int shader, const char* type)
{
	//Stores compliation status
	GLint hasCompiled;

	//Character array to store error messages in
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}