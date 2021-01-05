#version 460 core

layout(location = 0) in vec3 position;

uniform mat4 rotation;

void main()
{
	gl_Position = rotation * vec4(position, 1.0f);
    // gl_Position = vec4(position, 1.0f);
}