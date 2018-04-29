#version 430 core

in vec2 TextureCoordinates;

uniform sampler2D textureSampler;

out vec4 color;

void main()
{
    color = texture(textureSampler, TextureCoordinates);
}