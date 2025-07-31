#version 300 es

layout(location = 0) in highp vec3 a_posL;
layout(location = 1) in mediump vec2 a_uv;

uniform highp mat4 u_mvp;
uniform mediump float u_alpha;
uniform mediump float u_frameX;
uniform mediump float u_numFrames;
uniform mediump float u_frameY;
uniform mediump float u_numActions;
uniform bool u_isFlipX;
uniform bool u_isFlipY;

out mediump vec2 v_uv;

void main()
{
	gl_Position = u_mvp * vec4(a_posL, 1.0);
	
	// x = row, y = column
	// sprite counted left to right, top to bottom, start at 0 
	v_uv = vec2(a_uv.x * (1.0 / u_numFrames)+ u_frameX / u_numFrames, a_uv.y * (1.0 / u_numActions)+ u_frameY / u_numActions);
	if(u_isFlipX == true) {
		v_uv.x = 1.0 - v_uv.x;
	}
	if(u_isFlipY == true) {
		v_uv.y = 1.0 - v_uv.y;
	}
}