#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;
layout(location = 2) in vec2 inputTextureCoordinates;

out vec3 vertexColor;
out vec2 vertexTextureCoordinates;
void main()
{
	gl_Position = vec4(inputPosition, 1.0);
	vertexColor = inputColor;
	vertexTextureCoordinates = inputTextureCoordinates;
}

#shader fragment
#version 330 core

out vec4 fragmentColor;
in vec3 vertexColor;
in vec2 vertexTextureCoordinates;

uniform sampler2D fragmentTexture;

void main()
{
	fragmentColor = texture(fragmentTexture, vertexTextureCoordinates);
}