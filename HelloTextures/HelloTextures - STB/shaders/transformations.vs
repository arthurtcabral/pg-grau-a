#version 430 core

layout (location = 0) in vec3 positionCoord;
layout (location = 1) in vec2 textureCoord;

out vec2 TextureCoordinates;
  
uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(positionCoord, 1.0f);
	TextureCoordinates = vec2(textureCoord.x, 1.0 - textureCoord.y);
}