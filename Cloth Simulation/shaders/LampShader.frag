#version 440 core
out vec4 FragColor;

in vec4 vertexColor;

void main()
{
    FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
}
