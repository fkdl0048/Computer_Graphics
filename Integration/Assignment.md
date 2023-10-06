# Assignment

## 01

### Assignment

#### Main

```cpp
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Color Cube Example");

	glewExperimental = true;
	glewInit();

	myInit();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);


	glutMainLoop();

	return 0;
}
```

- main(int argc, char** argv)
  - argc: 실행시 전달되는 인자의 개수
  - argv: 실행시 전달되는 인자의 배열
- glutInit(&argc, argv)
  - glut 초기화
- glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
  - 디스플레이 모드 설정
  - GLUT_DOUBLE: 더블 버퍼 사용
    - 더블 버퍼를 사용하여 깜빡임을 없앰
    - 한 버퍼에서 다 그리면 다른 버퍼와 스왑
  - GLUT_RGBA: RGBA 컬러 모드 사용
  - GLUT_DEPTH: 깊이 버퍼 사용
    - z-buffer
    - z축 기준으로 그려야 하는 레이어 순위 정도로 생각
- glutInitWindowSize(512, 512)
  - 윈도우 크기 설정
- glutCreateWindow("Color Cube Example")
  - 윈도우 생성
  - 윈도우 이름 설정
- glewExperimental = true
  - GLEW 초기화
- glewInit()
  - GLEW 초기화
- myInit()
  - 개인 초기화 함수
- glutDisplayFunc()
  - 디스플레이 콜백 함수 등록
  - 화면에 그릴 때마다 호출
- glutIdleFunc()
  - Idle 콜백 함수 등록
  - 화면에 그릴 때마다 호출
- glutKeyboardFunc()
  - 키보드 콜백 함수 등록
  - 키보드 입력시 호출
- glutMainLoop()
  - 이벤트 루프 진입

```cpp
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	cube.draw(mytime);

	glutSwapBuffers();
}
```

glutDisplayFunc에 등록한 함수

즉, 화면이 그려질 때마다 호출

- glClear()
  - 컬러 버퍼와 깊이 버퍼를 초기화
  - GL_COLOR_BUFFER_BIT: 컬러 버퍼 초기화
  - GL_DEPTH_BUFFER_BIT: 깊이 버퍼 초기화
- glEnable(GL_DEPTH_TEST)
  - 깊이 버퍼 사용
- glutSwapBuffers()
  - 더블 버퍼링을 사용하기 때문에 백버퍼와 프론트 버퍼를 스왑

#### Cube

```cpp
class MyColorCube
{
public:

	int NumVertex;
	GLuint prog;
	GLuint vao;
	GLuint vbo;

	vec4* positions;
	vec4* colors;
	int cur;

	MyColorCube()					
	{
		NumVertex = 36;				// =  6 * 2 * 3;
		cur = 0;
		positions = nullptr;
		colors = nullptr;
	}

	void makeRect(int a, int b, int c, int d, vec4 vertex_pos[], vec4 vertex_color[])
	{
		positions[cur] = vertex_pos[a];	colors[cur] = vertex_color[a]; cur++;
		positions[cur] = vertex_pos[b];	colors[cur] = vertex_color[b]; cur++;
		positions[cur] = vertex_pos[c];	colors[cur] = vertex_color[c]; cur++;

		positions[cur] = vertex_pos[c];	colors[cur] = vertex_color[c]; cur++;
		positions[cur] = vertex_pos[d];	colors[cur] = vertex_color[d]; cur++;
		positions[cur] = vertex_pos[a];	colors[cur] = vertex_color[a]; cur++;
	}

	void makeCube()
	{
		vec4 vertex_pos[8] = {
				vec4(-0.5,-0.5, 0.5, 1),
				vec4(-0.5, 0.5, 0.5, 1),
				vec4(0.5, 0.5, 0.5, 1),
				vec4(0.5,-0.5, 0.5, 1),
				vec4(-0.5,-0.5,-0.5, 1),
				vec4(-0.5, 0.5,-0.5, 1),
				vec4(0.5, 0.5, -0.5, 1),
				vec4(0.5,-0.5, -0.5, 1)
		};

		vec4 vertex_color[8] = {
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1),
			vec4(1,0,0,1)
		};

		cur = 0;

		makeRect(0, 3, 2, 1, vertex_pos, vertex_color);
		makeRect(4, 5, 6, 7, vertex_pos, vertex_color);
		makeRect(0, 4, 7, 3, vertex_pos, vertex_color);
		makeRect(3, 7, 6, 2, vertex_pos, vertex_color);
		makeRect(2, 6, 5, 1, vertex_pos, vertex_color);
		makeRect(1, 5, 4, 0, vertex_pos, vertex_color);
	}

	void init()
	{
		positions = new vec4 [NumVertex];
		colors = new vec4 [NumVertex];

		makeCube();

		//1. Setup VAO (gen and bind)

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		//2. Setup VBO

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//3. Copy data to Buffer

		glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex * 2, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * NumVertex, positions);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex, sizeof(vec4) * NumVertex, colors);

		//4. Load Shaders

		prog = InitShader("vshader.glsl", "fshader.glsl");
		glUseProgram(prog);

		GLuint vPosition = glGetAttribLocation(prog, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		// vColor
		GLuint vColor = glGetAttribLocation(prog, "vColor");
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4)* NumVertex));


		delete[] positions;
		delete[] colors;

	}

	void draw(float cur_time)
	{
		glBindVertexArray(vao);
		glUseProgram(prog);

		GLuint uTime = glGetUniformLocation(prog, "uTime");
		glUniform1f(uTime, cur_time);

		glDrawArrays(GL_TRIANGLES, 0, NumVertex);
	}
};
```

- GLuint vao
  - VAO(Vertex Array Object)
  - VBO와 쉐이더를 연결하는 역할
- GLuint vbo
  - VBO(Vertex Buffer Object)
  - 버퍼 객체
  - GPU 메모리에 데이터를 저장하는 역할
- GLunit prog
  - 쉐이더 프로그램
  - 쉐이더를 컴파일하고 링크하여 사용할 수 있게 해주는 객체
- vec4* positions
  - 버퍼에 저장할 위치 데이터
- vec4* colors
  - 버퍼에 저장할 색상 데이터
- int cur
  - 버퍼에 저장할 데이터의 인덱스
- void makeRect(int a, int b, int c, int d, vec4 vertex_pos[], vec4 vertex_color[])
  - 사각형을 만드는 함수
  - a, b, c, d: 사각형을 만들기 위한 꼭지점 인덱스
  - vertex_pos: 꼭지점 위치 데이터
  - vertex_color: 꼭지점 색상 데이터
- void makeCube()
  - 큐브를 만드는 함수
  - 내부에서 makeRect()를 호출하여 큐브를 만듬
- void init()
  - 초기화 함수
  - VAO, VBO, 쉐이더 프로그램을 초기화
  - VAO와 VBO를 연결
  - 쉐이더 프로그램에 attribute 변수를 연결
  - 쉐이더 프로그램에 uniform 변수를 연결
  - positions, colors 메모리 해제
- void draw(float cur_time)
  - 그리기 함수
  - VAO와 쉐이더 프로그램을 바인딩
  - 쉐이더 프로그램에 uniform 변수를 전달
  - glDrawArrays()를 호출하여 큐브를 그림

#### Shader

```c
#version 330

uniform float uTime;

in vec4 vPosition;
in vec4 vColor;

out vec4 color;
out vec4 position;

void main()
{
	float uTheta1 = uTime*60;
	float uTheta2 = uTime*20;

	float rad1 = uTheta1 / 180.0 * 3.141592;
	mat4 m = mat4(1.0);							// y - rotation
	m[0][0] = cos(rad1);m[1][0] = 0;		m[2][0] = sin(rad1);m[3][0] = 0;
	m[0][1] = 0;		m[1][1] = 1;		m[2][1] = 0;		m[3][1] = 0;
	m[0][2] =-sin(rad1);m[1][2] = 0;		m[2][2] = cos(rad1);m[3][2] = 0;
	m[0][3] = 0;		m[1][3] = 0;		m[2][3] = 0;		m[3][3] = 1;

	float rad2 = uTheta2 / 180.0 * 3.141592;
	mat4 n = mat4(1.0);							// x - rotation
	n[0][0] = 1;		n[1][0] = 0;		n[2][0] = 0;		n[3][0] = 0;
	n[0][1] = 0;		n[1][1] = cos(rad2);n[2][1] =-sin(rad2);n[3][1] = 0;
	n[0][2] = 0;		n[1][2] = sin(rad2);n[2][2] = cos(rad2);n[3][2] = 0;
	n[0][3] = 0;		n[1][3] = 0;		n[2][3] = 0;		n[3][3] = 1;

	gl_Position = (sin(uTime) * 0.5 + 0.6) * n*m* vPosition;
	gl_Position.w = 1.0f;

	color = vColor;
	position = vPosition;
}
```

Vertex Shader

- uniform float uTime
  - 시간을 전달받는 변수
- in vec4 vPosition
  - 꼭지점 위치 데이터
- in vec4 vColor
  - 꼭지점 색상 데이터
- out vec4 color
  - 색상 데이터
- out vec4 position
  - 위치 데이터
- void main()
  - 메인 함수
  - uTime을 이용하여 회전각을 계산
  - 회전각을 이용하여 회전 행렬을 계산
  - 회전 행렬을 이용하여 꼭지점 위치를 변환
  - 변환된 꼭지점 위치를 gl_Position에 저장
  - 꼭지점 색상을 color에 저장
  - 꼭지점 위치를 position에 저장
```

```c
#version 330

in vec4 color;
in vec4 position;

out vec4 fColor;

void main()
{
	vec4 c = color;
	float d = 0.05f;

	if((position.x>0.5-d || position.x<-0.5+d) && (position.y>0.5-d || position.y<-0.5+d))
		c = vec4(0,1,0,1);
	if((position.x>0.5-d || position.x<-0.5+d) && (position.z>0.5-d || position.z<-0.5+d))
		c = vec4(0,1,0,1);
	if((position.z>0.5-d || position.z<-0.5+d) && (position.y>0.5-d || position.y<-0.5+d))
		c = vec4(0,1,0,1);
	

	fColor = c;
}
```

Fragment Shader

- in vec4 color
  - 색상 데이터
- in vec4 position
  - 위치 데이터
- out vec4 fColor
  - 색상 데이터
- void main()
  - 메인 함수
  - 색상 데이터를 fColor에 저장
  - 만약 위치 데이터가 큐브의 면에 있다면 색상을 녹색으로 변경

#### 1차 리팩터링

```cpp
#ifndef __MYCOLORCUBE_H__
#define __MYCOLORCUBE_H__

#include <vec.h>
#include <vgl.h>
#include <InitShader.h>

class MyColorCube
{
public:

	int NumVertex;
	GLuint prog;
	GLuint vao;
	GLuint vbo;
	GLuint uTime;

	vec4* positions;
	vec4* colors;
	int cur;

	MyColorCube();
	void init();
	void draw(float cur_time);
	//~MyColorCube();

private:
	void makeRect(int a, int b, int c, int d, vec4 vertex_pos[], vec4 vertex_color[]);
	void makeCube();
};

MyColorCube::MyColorCube()
{
	NumVertex = 36;				// =  6 * 2 * 3;
	cur = 0;
	positions = nullptr;
	colors = nullptr;
}

void MyColorCube::init()
{
	positions = new vec4[NumVertex];
	colors = new vec4[NumVertex];

	makeCube();

	//1. Setup VAO (gen and bind)

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//2. Setup VBO

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//3. Copy data to Buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4) * NumVertex, positions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * NumVertex, sizeof(vec4) * NumVertex, colors);

	//4. Load Shaders

	prog = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(prog);

	GLuint vPosition = glGetAttribLocation(prog, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// vColor
	GLuint vColor = glGetAttribLocation(prog, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * NumVertex));

	uTime = glGetUniformLocation(prog, "uTime");


	delete[] positions;
	delete[] colors;

}

void MyColorCube::draw(float cur_time)
{
	glBindVertexArray(vao);
	glUseProgram(prog);

	glUniform1f(uTime, cur_time);

	glDrawArrays(GL_TRIANGLES, 0, NumVertex);
}

void MyColorCube::makeRect(int a, int b, int c, int d, vec4 vertex_pos[], vec4 vertex_color[])
{
	positions[cur] = vertex_pos[a];	colors[cur] = vertex_color[a]; cur++;
	positions[cur] = vertex_pos[b];	colors[cur] = vertex_color[b]; cur++;
	positions[cur] = vertex_pos[c];	colors[cur] = vertex_color[c]; cur++;

	positions[cur] = vertex_pos[c];	colors[cur] = vertex_color[c]; cur++;
	positions[cur] = vertex_pos[d];	colors[cur] = vertex_color[d]; cur++;
	positions[cur] = vertex_pos[a];	colors[cur] = vertex_color[a]; cur++;
}

void MyColorCube::makeCube()
{
	vec4 vertex_pos[8] = {
			vec4(-0.5,-0.5, 0.5, 1),
			vec4(-0.5, 0.5, 0.5, 1),
			vec4(0.5, 0.5, 0.5, 1),
			vec4(0.5,-0.5, 0.5, 1),
			vec4(-0.5,-0.5,-0.5, 1),
			vec4(-0.5, 0.5,-0.5, 1),
			vec4(0.5, 0.5, -0.5, 1),
			vec4(0.5,-0.5, -0.5, 1)
	};

	vec4 vertex_color[8] = {
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1),
		vec4(1,0,0,1)
		//vec4(0,1,0,1),
		//vec4(0,0,1,1),
		//vec4(1,1,0,1),
		//vec4(0,1,1,1),
		//vec4(1,0,1,1),
		//vec4(1,1,1,1),
		//vec4(0,0,0,1)
	};

	cur = 0;

	makeRect(0, 3, 2, 1, vertex_pos, vertex_color);
	makeRect(4, 5, 6, 7, vertex_pos, vertex_color);
	makeRect(0, 4, 7, 3, vertex_pos, vertex_color);
	makeRect(3, 7, 6, 2, vertex_pos, vertex_color);
	makeRect(2, 6, 5, 1, vertex_pos, vertex_color);
	makeRect(1, 5, 4, 0, vertex_pos, vertex_color);
}
#endif
```

#### Plan

한 단계씩 진행

- 바닥 면을 띄우기
- 바닥 회전
- 바닥 개수 증가 및 감소

