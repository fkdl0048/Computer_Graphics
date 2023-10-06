#version 330

in vec4 color;
in vec4 position;

out vec4 fColor;

void main()
{
	vec4 c = color;
	

	fColor = c;
}