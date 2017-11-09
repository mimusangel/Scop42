#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 vColor;

void main()
{
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vertexPosition, 1);
	vColor = vertexColor;
}
