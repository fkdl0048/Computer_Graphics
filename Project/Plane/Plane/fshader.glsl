#version 330

in vec4 color;
in vec4 position;

out vec4 fColor;

void main()
{
	vec4 c = color;
	float d = 0.05f;

	fColor = c;
}