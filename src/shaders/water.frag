#version 460 core

out vec4 FragColor;

in vec3 FragPos;
flat in vec3 Normal;

uniform vec3 lightDir;   
uniform vec3 lightColor; 
uniform vec3 viewPos;   

void main()
{
    vec3 waterColor = vec3(0.1, 0.3, 0.7);

    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightDir);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5; 
    vec3 viewDirection = normalize(viewPos - FragPos); 
    vec3 reflectDir = reflect(-lightDirection, norm); 
    
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 32); 
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * waterColor;

    FragColor = vec4(result, 1.0);
}
