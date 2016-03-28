#version 410
layout(location = 0) in vec4 Position;

uniform mat4 projectionView;

void main()
{
	gl_Position = projectionView * Position;
}
