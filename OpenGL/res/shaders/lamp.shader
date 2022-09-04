#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;

uniform mat4 modelLamp;
uniform mat4 viewLamp;
uniform mat4 projectionLamp;

void main()
{
	gl_Position = projectionLamp * viewLamp * modelLamp * vec4(inputPosition, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(1.0); // Set alle 4 vector values to 1.0f
}