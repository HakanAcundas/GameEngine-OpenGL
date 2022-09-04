#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;
//layout(location = 1) in vec2 inputTextureCoordinates;

//out vec2 vertexTextureCoordinates;
out vec3 fragPosition;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragPosition = vec3(model * vec4(inputPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * inputNormal;
	gl_Position = projection * view * model * vec4(inputPosition, 1.0);
	//vertexTextureCoordinates = inputTextureCoordinates;
}

#shader fragment
#version 330 core

out vec4 fragmentColor;
//in vec2 vertexTextureCoordinates;
in vec3 fragPosition;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
//uniform sampler2D fragmentTexture;

void main()
{
	//fragmentColor = texture(fragmentTexture, vertexTextureCoordinates);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 1.2;
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragmentColor = vec4(result, 1.0);
}