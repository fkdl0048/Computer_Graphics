#version 330

uniform float uTime;
uniform float uWave;

in vec4 vPosition;
in vec4 vColor;

out vec4 color;
out vec4 position;
out float height;

void main()
{
	float uThetaX = 45; 
	float uThetaY = -10 * uTime;
	
	float rad1 = uThetaX / 180.0 * 3.141592f;
	mat4 x_mat = mat4(1.0);							// x - rotation
	x_mat[1][1] = cos(rad1);	x_mat[2][1] = -sin(rad1);
	x_mat[1][2] = sin(rad1);	x_mat[2][2] = cos(rad1);

	float rad3 = uThetaY / 180.0f * 3.141592;
	mat4 y_mat = mat4(1.0);							// y - rotation
	y_mat[0][0] = cos(rad3);	y_mat[0][2] = sin(rad3);
	y_mat[2][0] = -sin(rad3);	y_mat[2][2] = cos(rad3);

	// wave
	vec4 temp = vPosition;
	float distance = (vPosition.x * vPosition.x + vPosition.z * vPosition.z);

	if (distance <= 0.25f && uWave >= 0.5f)
	{
		temp.y = sin((-uTime + distance * 3.141592 * 30));
		temp.y = temp.y * (0.25 -  distance);	
	}

    gl_Position = temp * y_mat * x_mat;
    gl_Position.w = 1.0;

	color = vColor;
	position = vPosition;
	height = temp.y;
}