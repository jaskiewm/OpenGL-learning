#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

int main() 
{
	//Initialize GLFW
	glfwInit();

	//Tells GLFW what version of OpenGL we are running
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Package of functions from OpenGL (Core)

	//Vertices of three triangles in a bigger triangle (Zelda)
	GLfloat vertices[]{
		//Lower left corner, lower right corner, top corner
		//Every three points is one coordinate, and z = 0f because we are making 2D objects
		-0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Left Corner (0)
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Right Corner (1)
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,0.0f // Top Corner (2)

		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Center Left Corner (3)
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Center Right Corner (4)
		0.0f, -0.5f * float(sqrt(3)) * 3 / 3,0.0f // Bottom Corner (5)
	};

	// Indices for 3 triangles in a larger triangle
	GLuint indices[] =
	{
		0, 3, 5, //Bottom Left Triangle
		3, 2, 4, //Bottom Right Triangle
		5, 4, 1  //Top Triangle
	};


	//-------Loading window and viewport-------//
	//Creating a window (width, height, name, full screen, not important)
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	//Closes GLFW and displays error if window doesn't want to open
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Make window part of current context
	glfwMakeContextCurrent(window); 
	//Load openGL configurations using GLAD
	gladLoadGL(); 
	//Area of openGL we want rendering (x=0,y=0 to x=800,y=800), the viewport
	glViewport(0,0,800,800); 


	//-------Creating shaders (both vertex and fragment)-------//
	// Get shader object and it's reference
	// Create Shader -> attach source code to shader -> compile shader
	// Create shader program -> link shaders to program -> delete shaders

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//unsigned integer (positive integer)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Attach vertex shader source to vertex shader object
	glCompileShader(vertexShader); //Compiles the shader source into machine

	// Get shader object and it's reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//unsigned integer (positive integer)
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader); //Compiles the shader source into machine

	// Create the Shader Program Object and its references
	GLuint shaderProgram = glCreateProgram();

	//Attach vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link all shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	//Delete the shaders because they are in the program from above lines
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// VAO - Vertex Array Object | VBO - Vertex Buffer Object
	// Create reference containers for the Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
	GLuint VAO, VBO; //VA0, and VBO is an array of references

	//Generates the VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make VAO the current Vertex Array Object by Binding it
	glBindVertexArray(VAO);
	
	//Make VBO object the current Object Buffer by binding it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Store data in OpenGL. Introduce certices into the VBO (now the GL_ARRAY_BUFFER is the VBO)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Static is set once and used many times

	//Configures the Vertex Attribute so that OpenGL knows how to read the VBO
	//(Pos of vertex attr, num of values (3 vertices), value type, Coord are integers?, data size, start position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable vertex attribute so OGL knows to use it
	glEnableVertexAttribArray(0); 

	// Binds the buffer to 0 so we can't make any unwanted changes with functions
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	//-------Window Settings-------//
	//Specify background colour
	glClearColor(0.07, 0.13f, 0.17f, 1.0f);
	//Clean and assign to colour to BACK BUFFER
	glClear(GL_COLOR_BUFFER_BIT);
	//swap back buffer and front buffer
	glfwSwapBuffers(window);

	//Only close window when close button or another function is reached
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OGL which shader program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OGL knows how to use it
		glBindVertexArray(VAO);
		// Draw triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3); //Specifies primitive, starting index, number of vertices
		glfwSwapBuffers(window); //Ensure buffers are swapped so we get a new image each frame

		glfwPollEvents(); //Process all GLFW events
	}

	//Deleting objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Close window
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}