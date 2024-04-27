#include <iostream>
#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//-------Initializing vertices and indices-------//
//Vertices of three triangles in a bigger triangle (Zelda)
GLfloat vertices[]{
	// Coordinates are X,Y,Z (=0 because 2D), colors are in R,G,B
	// Every second set of three is a colour (Links are located in the default.frag and default.vert
	// base = 0.5, height = 0.5

	-0.5f, -0.5f, 0.0f,	0.95f, 0.745f, 0.18f,	// Lower Left Corner (COORD - 0)
	0.5f, -0.5f, 0.0f,	0.95f, 0.745f, 0.18f,	// Lower Right Corner (COORD - 1)
	0.0f, 0.5f, 0.0f,	1.00f, 0.960f, 0.85f,	// Top Corner (COORD - 2)
	-0.25f, 0.0f, 0.0f,	0.95f, 0.745f, 0.18f,	// Center Left Corner (COORD - 3)
	0.25f, 0.0f, 0.0f,	0.95f, 0.745f, 0.18f,	// Center Right Corner (COORD - 4)
	0.0f, -0.5f, 0.0f,	0.95f, 0.745f, 0.18f	// Bottom Corner (COORD - 5)

};

// Indices for 3 triangles in a larger triangle
GLuint indices[] =
{
	0, 3, 5, //Bottom Left Triangle
	3, 2, 4, //Bottom Right Triangle
	5, 4, 1  //Top Triangle
};

int main() 
{
	//-------Initializing GLFW-------//
	//Initialize GLFW
	glfwInit();

	// Tells GLFW what version of OpenGL we are running (V#3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Tell GLFW we are using CORE profile

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
	
	// Generates and binds VAO (Vertex array object)
	VAO VAO1;
	VAO1.Bind();

	//Builds and links Buffer Objects to Indices & Vertices
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attrivutes to VAO (ie, coord = layout 1, colour = layout 2)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3* sizeof(float)));

	// Unbinds all objects (to prevent modifying them)
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Only close window when close button or another function is reached
	while (!glfwWindowShouldClose(window)) {

		// Specifies background colour
		glClearColor(0.07, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign colour to it
		glClear(GL_COLOR_BUFFER_BIT);

		//Tell OGL which shader program we want to use
		shaderProgram.Activate();

		//1f for input 1 float
		glUniform1f(uniID, 0.5f);

		// Bind the VAO so OGL knows how to use it
		VAO1.Bind();
		// Draw triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //Specifies primitive, number of indices, type of indices, starting index

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