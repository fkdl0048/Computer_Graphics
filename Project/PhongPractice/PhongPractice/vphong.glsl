#version 330

in  vec4 vPosition;
in  vec4 vColor;
in  vec3 vNormal;
out vec4 color;

uniform mat4 uProjMat;
uniform mat4 uModelMat;

void main()
{
	gl_Position  = uProjMat * (uModelMat * vPosition);
	gl_Position *= vec4(1,1,-1,1);	// z�� ������ �ݴ���





    
	color = vColor;
}
