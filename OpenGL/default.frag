#version 330 core
out vec4 FragColor; //Output colour in RGBA

//Inputs colours from Vertex Shader
in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0f);
}