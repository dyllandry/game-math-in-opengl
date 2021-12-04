#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

void main()
{
        gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * transform * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

