#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colors;
layout (location = 2) in vec2 texCoords;

out vec4 vertexColor;
out vec2 textureCoords;

uniform mat4 projectionMatrixUniform;
uniform mat4 viewMatrixUniform;
uniform mat4 transformUniform;

void main()
{
    gl_Position = projectionMatrixUniform * viewMatrixUniform * transformUniform * vec4(position.x, position.y, position.z, 1.0);
    vertexColor = vec4(colors.x, colors.y, colors.z, 1.0);
    textureCoords = vec2(texCoords.x, 1.0 - texCoords.y);
}
