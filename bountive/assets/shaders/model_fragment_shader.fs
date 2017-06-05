#version 330 core

in vec4 vertexColor;
in vec2 textureCoords;

out vec4 color;

uniform sampler2D texture0;

void main()
{
    //color = texture(texture0, textureCoords) * vertexColor;
    color = vertexColor;
} 