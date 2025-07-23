#version 300 es

layout(location = 0) in highp vec3 a_posL;
layout(location = 1) in mediump vec2 a_uv;

uniform highp mat4 u_mvp;
uniform mediump float u_alpha;
uniform mediump float u_currentFrame;
uniform mediump float u_numFrames;
uniform mediump float u_currentAction;
uniform mediump float u_numActions;

out mediump vec2 v_uv;

void main()
{
	gl_Position = u_mvp * vec4(a_posL, 1.0);
	
	// column anim
	//v_uv = vec2 (a_uv.x*(1.0/u_numActions)+ u_currentAction/u_numActions, a_uv.y*(1.0/u_numFrames)+ u_currentFrame/u_numFrames);

	// row anim
	v_uv = vec2(a_uv.x * (1.0 / u_numFrames)+ u_currentFrame / u_numFrames, a_uv.y * (1.0 / u_numActions)+ u_currentAction / u_numActions);
}