#version 330 core

layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float layer_z;
uniform mat4 matrix;

void main()
{
	TexCoord = vec2( texCoord.x, 1.0 - texCoord.y );
	gl_Position = matrix * vec4(vPosition, layer_z);
}