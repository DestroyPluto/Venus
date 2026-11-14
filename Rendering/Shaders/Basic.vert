#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 projection;
void main()
{
	gl_Position = projection * model * vec4(aPos, 1.0);
	vertexColor = vec3(0.7,0.7,0.7); //just grey for now.
}