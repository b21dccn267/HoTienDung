#version 300 es
layout(location = 0) in vec3 a_posL;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

void main()
{
	gl_Position = vec4(a_posL, 1.0);
	vColor = aColor;
}
   