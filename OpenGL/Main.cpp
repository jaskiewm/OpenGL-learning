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

	//----------Creating shader program and objects--------------//
	
	//Generates shader objects (using default vert & frag)
	Shader shaderProgram("default.vert", "default.frag");
	
	// Generates VAO (Vertex array object) and binds it
	VAO VAO1;
	VAO1.Bind();

	//Builds and links Buffer Objects to Indices & Vertices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	// Unbinds all objects (to prevent modifying them)
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

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
		shaderProgram.Activate();
		// Bind the VAO so OGL knows how to use it
		VAO1.Bind();
		// Draw triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3); //Specifies primitive, starting index, number of vertices
		glfwSwapBuffers(window); //Ensure buffers are swapped so we get a new image each frame

		glfwPollEvents(); //Process all GLFW events
	}

	//-------Deleting Objects, closing OGL-------//
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Close window
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	return 0;
}