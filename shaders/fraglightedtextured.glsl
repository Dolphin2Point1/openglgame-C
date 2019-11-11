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
    // 0 = Directional, 1 = Point, 2 = Spot
    float cutOff;
    int type;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

//    bool attenuation;
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    if (light.type == 0) {
        lightDir = normalize(light.direction);
    } else if(light.type == 1) {
        lightDir = normalize(light.position - FragPos);
    } else {
        return;
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // attenuation
    if(light.type != 0) {
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        ambient  *= attenuation;
        diffuse   *= attenuation;
        specular *= attenuation;
    }
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

