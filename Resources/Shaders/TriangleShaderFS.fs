#version 300 es
precision mediump float;

in vec3 vColor;
layout(location = 0) out mediump vec4 o_color;

void main()
{
	o_color = vec4(vColor, 1.0);
}
