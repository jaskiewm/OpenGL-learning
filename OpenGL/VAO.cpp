#include"VAO.h"

//Constructor generates VAO ID
VAO::VAO() 
{
	glGenVertexArrays(1, &ID);
}

//Links a VBO to the VAO
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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