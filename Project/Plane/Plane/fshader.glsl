#version 330

in vec4 color;
in vec4 position;
in float height;

out vec4 fColor;

void main()
{
	fColor = (height < 0) ? color + vec4(-height*3, 0.0, 0.0, 1.0) : color + vec4(0, 0, height*3, 1);
}