#version 330

uniform float uTime;

in vec4 vPosition;
in vec4 vColor;

out vec4 color;
out vec4 position;

void main()
{
	float uThetaX = -45;
	float uThetaY = 16 * uTime;
	
	float rad1 = uThetaX / 180.0 * 3.141592f;
	mat4 x_mat = mat4(1.0);							// x - rotation
	x_mat[1][1] = cos(rad1);	x_mat[2][1] = -sin(rad1);
	x_mat[1][2] = sin(rad1);	x_mat[2][2] = cos(rad1);

	float rad3 = uThetaY / 160.0f * 3.141592;
	mat4 y_mat = mat4(1.0);							// y - rotation
	y_mat[0][0] = cos(rad3);	y_mat[0][2] = sin(rad3);
	y_mat[2][0] = -sin(rad3);	y_mat[2][2] = cos(rad3);

	gl_Position = vPosition * y_mat * x_mat * waveMat;
	gl_Position.w = 1.0f;

	// 컬러, 위치 F쉐이더로 전달
	color = vColor;
	position = vPosition;
}