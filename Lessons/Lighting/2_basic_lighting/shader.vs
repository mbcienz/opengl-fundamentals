#version 460 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = projection * view * model * transform * vec4(aPos, 1.0);
    FragPos = vec3(model * transform * vec4(aPos, 1.0));
    // generally compute the inverse is better if done outside the shader, due to its high
    // computational cost. 
    //moreover we are computing the light in the world coordinate, in general this is done in 
    // vierw space.
    Normal = mat3(transpose(inverse(model))) * vec3(transform * vec4(aNormal, 1.0));
}    