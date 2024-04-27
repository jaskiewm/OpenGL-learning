#include"VAO.h"

//Constructor generates VAO ID
VAO::VAO() 
{
	glGenVertexArrays(1, &ID);
}

//Links a VBO to the VAO
// Offset = initial offsetting byte number to get to the RGB bytes (only colour needs this as it starts at the 4th byte)
// Stride = distance in bytes between vertices (ie, coordinate stride vs color stride)

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}