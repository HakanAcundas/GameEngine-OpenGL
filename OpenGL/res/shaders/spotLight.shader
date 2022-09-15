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
    TextureCoords = inputTextureCoords;

	gl_Position = projection * view * model * vec4(inputPosition, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linearSpot;
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
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoords));

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextureCoords));

    // specular
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextureCoords));

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linearSpot * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}