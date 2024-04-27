#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	// ID reference for VAO (vertex array object)
	GLuint ID;
	// Constructor generatres VAO ID
	VAO();

	// Links VBO & VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// Binds VAO
	void Bind();

	// Unbinds VAO
	void Unbind();

	// Deletes VAO
	void Delete();
};

#endif