#version 330

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

void main()
{
	mat4 rot1 = mat4(1);
	mat4 rot2 = mat4(1);
	float t1 = -30.0f/180.0f*3.141592;
	float t2 = 30.0f/180.0f*3.141592;

	rot1[1][1] = cos(t1);	rot1[2][1] =-sin(t1);
	rot1[1][2] = sin(t1);	rot1[2][2] = cos(t1);

	rot2[0] = vec4(cos(t2),0,sin(t2),0);
	rot2[2] = vec4(-sin(t2),0,cos(t2),0);

	color = vColor;
	gl_Position = rot2*rot1*vPosition;

}
