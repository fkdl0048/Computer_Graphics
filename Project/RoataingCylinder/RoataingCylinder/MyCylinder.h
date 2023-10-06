#ifndef __MY_CYLINDER_H__
#define __MY_CYLINDER_H__
#include <vgl.h>
#include <vec.h>
#include <InitShader.h>

struct MyCylinderVertex
{
	vec4 pos;
	vec4 color;
};

class myCylinder
{
public:
	int m_numPoly;
	int m_NumVertex;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_prog;

	myCylinder()
	{
		m_numPoly = 0;
		m_NumVertex = 0;
	}

	void init(int poly)
	{
		if (m_numPoly == poly || poly < 3) return;

		m_NumVertex = m_numPoly * 2 * 3;

		MyCylinderVertex* vertices = new MyCylinderVertex[m_NumVertex];

		float r = 0.5f;
		float h = 1.0f;

		int cur = 0;
		float da = 2 * 3.141592 / m_numPoly;
		for (int i = 0; i < m_numPoly; i++)
		{
			float x1 = r * cos(i * da); // r * cos(theta)
			float z1 = r * sin(i * da); // r * sin(theta)

			float x2 = r * cos((i + 1) * da);
			float z2 = r * sin((i + 1) * da);

			vec4 a = vec4(x2, h / 2, z2, 1);
			vec4 b = vec4(x2, -h / 2, z2, 1);
			vec4 c = vec4(x1, -h / 2, z1, 1);
			vec4 d = vec4(x1, h / 2, z1, 1);

			float f = float(i) / m_numPoly;
			vec4 color = vec4(f, 0, 1 - f, 1);

			vertices[cur].pos = a; vertices[cur].color = color; cur++;
			vertices[cur].pos = b; vertices[cur].color = color; cur++;
			vertices[cur].pos = c; vertices[cur].color = color; cur++;

			vertices[cur].pos = c; vertices[cur].color = color; cur++;
			vertices[cur].pos = d; vertices[cur].color = color; cur++;
			vertices[cur].pos = a; vertices[cur].color = color; cur++;
		}

		// 1. vertex array object
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		// 2. vertex buffer object
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		// 3.send to buffer data
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyCylinderVertex) * m_NumVertex, vertices, GL_STATIC_DRAW);

		// 4. load program
		m_prog = InitShader("vShader.glsl", "fShader.glsl");
		glUseProgram(m_prog);

		// 5. connect buffer data to shader attributes
		GLuint vPosition = glGetAttribLocation(m_prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 
								sizeof(MyCylinderVertex), BUFFER_OFFSET(0));

		// vColor
		GLuint vColor = glGetAttribLocation(m_prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 
								sizeof(MyCylinderVertex), BUFFER_OFFSET(sizeof(vec4)));

		delete[] vertices;
	}

	void draw(float cur_time)
	{
		glBindVertexArray(m_vao);
		glUseProgram(m_prog);

		GLuint uTime = glGetUniformLocation(m_prog, "uTime");
		glUniform1f(uTime, cur_time);

		glDrawArrays(GL_TRIANGLES, 0, m_NumVertex);
	}

};

#endif