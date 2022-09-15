#shader vertex
#version 330 core

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;
layout(location = 2) in vec2 inputTextureCoords;

out vec3 fragPosition;
out vec3 Normal;
out vec2 TextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragPosition = vec3(model * vec4(inputPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * inputNormal;
	gl_Position = projection * view * model * vec4(inputPosition, 1.0);

    TextureCoords = inputTextureCoords;
}

#shader fragment
#version 330 core

out vec4 fragmentColor;

struct Material {
    sampler2D  diffuse;
    sampler2D  specular;
    float      shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

in vec3 fragPosition;
in vec3 Normal;
in vec2 TextureCoords;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoords));

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureCoords));

    // specular
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureCoords));

    // attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    fragmentColor = vec4(ambient + diffuse + specular, 1.0);
}