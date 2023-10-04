#ifndef __PLANE_H__
#define __PLANE_H__

#include <vec.h>
#include <vgl.h>
#include <InitShader.h>
#include <string>

class Plane
{
public:
	Plane();
	void init();
	void increaseLength();
	void declineLength();
	void draw(float cur_time);
	//~MyColorCube();

private:
	int NumVertex;
	int length;
	GLuint prog;
	GLuint vao;
	GLuint vbo;
	GLuint uTime;
	GLuint vPosition;
	GLuint vColor;

	vec4* positions;
	vec4* colors;

	vec4 vertex_color[2] = {
		vec4(0.5f, 0.5f, 0.5f, 1),
		vec4(0.3f, 0.3f, 0.3f, 1)
	};

	const int MIN_LENGHT = 2;
	const int MAX_LENGHT = 300;

	void makePlane();
	void bufferLogic();
};

Plane::Plane()
{
	length = 2;
	NumVertex = 2 * 3 * length * length; // 초기값 설정
	positions = nullptr;
	colors = nullptr;
}

void Plane::init()
{
	makePlane();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	prog = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(prog);

	vPosition = glGetAttribLocation(prog, "vPosition");
	vColor = glGetAttribLocation(prog, "vColor");

	uTime = glGetUniformLocation(prog, "uTime");

	bufferLogic();
}

void Plane::increaseLength()
{
	if (length + 1 > MAX_LENGHT)
		return;

	length++;
	makePlane();
	bufferLogic();
}

void Plane::declineLength()
{
	if (length - 1 < MIN_LENGHT)
		return;

	length--;
	makePlane();
	bufferLogic();
}

void Plane::draw(float cur_time)
{
	glBindVertexArray(vao);
	glUseProgram(prog);

	glUniform1f(uTime, cur_time);

	glDrawArrays(GL_TRIANGLES, 0, NumVertex);
}

void Plane::makePlane()
{
	NumVertex = 2 * 3 * (length * length);

	positions = new vec4[NumVertex];
	colors = new vec4[NumVertex];

	int cur = 0;
	float pivot = (float)1 / length;

	float x = -0.5;
	float y = -0.5;
	for (int i = 0; i < length; i++)
	{
		y += pivot;
		for (int j = 0; j < length; j++)
		{
			positions[cur] = vec4(x			, 0, y			, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;
			positions[cur] = vec4(x			, 0, y - pivot	, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;
			positions[cur] = vec4(x + pivot	, 0, y - pivot	, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;

			positions[cur] = vec4(x			, 0, y			, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;
			positions[cur] = vec4(x + pivot	, 0, y - pivot	, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;
			positions[cur] = vec4(x + pivot	, 0, y			, 1);	colors[cur] = vertex_color[(j + i) % 2]; cur++;

			x += pivot;
		}
		x = -0.5;
	}
}

void Plane::bufferLogic()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * NumVertex, positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex, sizeof(vec4) * NumVertex, colors);

	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * NumVertex));
}
#endif
