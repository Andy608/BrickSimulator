#version 330 core
in vec4 vertexColor;
in vec2 textureCoords;

out vec4 color;

uniform sampler2D bountiveLogo;

void main()
{
    color = texture(bountiveLogo, textureCoords) * vertexColor;
} 