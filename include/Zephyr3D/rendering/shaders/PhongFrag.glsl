#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define EPSILON 0.00001f
#define POINTLIGHTS_COUNT 4
#define SPOTLIGHTS_COUNT 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPosition;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[POINTLIGHTS_COUNT];
uniform SpotLight spotLights[SPOTLIGHTS_COUNT];
uniform Material material;

bool NearZero(float value);
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec4 diffuse_texture;
vec4 specular_texture;

void main() {
    diffuse_texture = texture(material.diffuse, TexCoords);
    specular_texture = texture(material.specular, TexCoords);

    if (diffuse_texture.a < 0.1f) {
        discard;
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPosition - FragPos);

    vec3 result = CalcDirectionalLight(directionalLight, norm, viewDir);

    for (int i = 0; i < POINTLIGHTS_COUNT; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    for (int i = 0; i < SPOTLIGHTS_COUNT; i++) {
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    FragColor = vec4(result, 1.0f);
}

bool NearZero(float value) {
    return abs(value) < EPSILON;
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    if (NearZero(light.direction.x) && NearZero(light.direction.y) && NearZero(light.direction.z))
        return vec3(0.0f, 0.0f, 0.0f);

    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(diffuse_texture);
    vec3 diffuse = light.diffuse * diff * vec3(diffuse_texture);
    vec3 specular = light.specular * spec * vec3(specular_texture);
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    if (isinf(attenuation)) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    // combine results
    vec3 ambient = light.ambient * vec3(diffuse_texture);
    vec3 diffuse = light.diffuse * diff * vec3(diffuse_texture);
    vec3 specular = light.specular * spec * vec3(specular_texture);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    if (isinf(attenuation)) {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    // combine results
    vec3 ambient = light.ambient * vec3(diffuse_texture);
    vec3 diffuse = light.diffuse * diff * vec3(diffuse_texture);
    vec3 specular = light.specular * spec * vec3(specular_texture);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
