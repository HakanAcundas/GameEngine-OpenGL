#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec2 inputTextureCoordinates;

out vec2 vertexTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inputPosition, 1.0);
	vertexTextureCoordinates = inputTextureCoordinates;
}

#shader fragment
#version 330 core

out vec4 fragmentColor;
in vec2 vertexTextureCoordinates;

uniform sampler2D fragmentTexture;

void main()
{
	fragmentColor = texture(fragmentTexture, vertexTextureCoordinates);
}