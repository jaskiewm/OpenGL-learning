#version 330 core
layout (location = 0) in vec3 aPos; //Coordinates
layout (location = 1) in vec3 aColor; // Colours

// Outputs Fragment Shader colour
out vec3 color;

//Controls scale of vertices
uniform float scale;


void main()
{
	//Outputs coordinates of vertices
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);

	// Sets color variable (output) to equatl the layout aColour
	color = aColor;
}