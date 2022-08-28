#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;

out vec3 vertexColor;
void main()
{
	gl_Position = vec4(inputPosition, 1.0);
	vertexColor = inputColor;
}

#shader fragment
#version 330 core

out vec4 fragmentColor;
in vec3 vertexColor;

void main()
{
	fragmentColor = vec4(vertexColor, 1.0f);
}