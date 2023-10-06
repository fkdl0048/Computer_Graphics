#ifndef __PLANE_H__
#define __PLANE_H__

#include <vec.h>
#include <vgl.h>
#include <InitShader.h>
#include <string>

struct VertexInfo
{
	vec4 pos;
	vec4 color;
};

class Plane
{
public:
	Plane();
	void init();
	void increaseLength();
	void declineLength();
	void draw(float cur_time);
	void wave();
	//~MyColorCube();

private:
	int NumVertex;
	int length;
	bool bWave;
	GLuint prog;
	GLuint vao;
	GLuint vbo;
	GLuint uTime;
	GLuint uWave;
	GLuint vPosition;
	GLuint vColor;

	VertexInfo* vertexInfo;

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
	NumVertex = 2 * 3 * length * length;
	vertexInfo = nullptr;
	bWave = false;
}

void Plane::init()
{
	makePlane();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	prog = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(prog);

	vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);


	vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);

	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), BUFFER_OFFSET(sizeof(vec4)));
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), BUFFER_OFFSET(0));

	uTime = glGetUniformLocation(prog, "uTime");
	uWave = glGetUniformLocation(prog, "uWave");

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

	vertexInfo = new VertexInfo[NumVertex];

	int cur = 0;
	float pivot = (float)1 / length;

	float x = -0.5;
	float y = -0.5;
	for (int i = 0; i < length; i++)
	{
		y += pivot;
		for (int j = 0; j < length; j++)
		{
			vertexInfo[cur].pos = vec4(x			, 0, y			, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;
			vertexInfo[cur].pos = vec4(x			, 0, y - pivot	, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;
			vertexInfo[cur].pos = vec4(x + pivot	, 0, y - pivot	, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;

			vertexInfo[cur].pos = vec4(x			, 0, y			, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;
			vertexInfo[cur].pos = vec4(x + pivot	, 0, y - pivot	, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;
			vertexInfo[cur].pos = vec4(x + pivot	, 0, y			, 1);	vertexInfo[cur].color = vertex_color[(j + i) % 2]; cur++;

			x += pivot;
		}
		x = -0.5;
	}
}

void Plane::bufferLogic()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * NumVertex, vertexInfo, GL_STATIC_DRAW);
}

void Plane::wave()
{
	bWave = !bWave;

	glUniform1f(uWave, bWave);
}
#endif
