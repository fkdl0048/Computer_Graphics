# LectureNote

## CG01

- 컴퓨터 그래픽
  - 컴퓨터 그래픽은 모델링, 렌더링, 애니메이션을 다룸
  - 모델링은 단순하게 데이터로 존재
  - 이후 빛과 광원을 계산하여 표면에 그려내는 것이 렌더링

- 컴퓨터 상의 모든 시각 정보는 표면으로 표현 surface

1차방정식, 2차방정식으로 다양하게 다루는데 가장 간단한 폴리곤 모델(삼각형으로 다룸)

카메라(시야)로 부터 2d화면을 보기까지 3d물체를 화면 어디에 위치시키는지 계산하는 것 *표면으로*

- 쉐이딩: 빛의 반사를 계산하는 것
  - 빛을 쏘고 해당 빛이 반사되는 좌표를 계산

레이어 순서, 그리고 명암도 계산에 들어가야함

재질(머터리얼)은 빛을 어떻게 반사할지 결정

- 빛은 간접광과 직접광이 있음
  - 직접광은 단순하게 그려낼 수 있다.
  - 하지만 간접광은 빛이 반사되는 과정을 계산해야함 (이에 알고리즘이 필요)
  - ex) 단순 해변의 햇빛을 받는 과정은 계산이 명로하지만 강의실내 면으로 된 여러 전등에 의한 간접광은 계산이 힘듬

수업은 OpenGL로 실습.

## GC02

- 물체를 그리기 위해 필요한 정보
  - 카메라 정보, 시각 정보(위치, 원근감): Viewer
  - 조명 정보(빛의 위치, 색상, 세기): Light Source
  - 물체 정보(물체의 위치, 모양, 재질): Objects
  - ++ Attributes(Material, Texture, Transparency, ...)

- OpenGL은 위 정보를 쉽게 다룰 수 있도록 도와줌

모든 시작은 광원에서 시작 -> 빛에서 광자가 나오고 이 광자가 물체에 반사되어 눈에 보이는 것

- 빛이 물체를 만나면 일어나는 3가지
  - 반사: 빛이 물체에 반사되어 눈에 보이는 것
  - 투과: 빛이 물체를 통과하여 눈에 보이는 것
  - 흡수: 빛이 물체에 흡수되어 눈에 보이지 않는 것
    - 여기서 흡수는 빨간색 물체가 있다고 한다면 나머지 색상을 흡수하고 빨간색만 반사하는 것
    - 즉, 색을 가지는 것이 흡수

### Ray Tracing (매우 중요)

- 빛을 쏘고 반사되는 과정을 계산하는 것

실제 세상의 경우 빛에서 발원한 광자가 물체에 반사되는데 이때 단일 반사가 아닌 여러 반사가 일어남

이를 컴퓨터로 표현은 가능하지만 그 수가 매우 기하급수적으로 늘어나기 때문에 불가능

따라서 이를 흉내내는 기술이 매우 발달하게 되는데 이것이 컴퓨터 그래픽의 핵심

실제 물리적인 빛의 반사를 컴퓨터로 표현하게 되면 매우 느리고 많이 무겁다.

대신 좀 더 사실적인 표현이 가능 -> 거울에 여러 다반사로 인해 연속적인 비침, 굴절 등등

매우 무겁기 때문에 이를 흉내내기 위해 실제 시야각(초점)에서 빛을 쏘고 반사되는 과정을 계산(역추적)

따라서 이런 실제 세상을 흉내내기 위한 야매?적인 방법이 생기게 되는데

초창기 가장 혁신적인 형태의 레이트레이싱은 스트리밍 방식이다.

![image](https://github.com/fkdl0048/ToDo/assets/84510455/b6b5bd7b-b3e7-42e5-8e30-3f8ab72fe383)

- Pipeline architecture
  - Vertex Processor: 3D object -> 2D image
    - 3D object를 2D image로 변환
    - 화면의 정보를 점으로 읽음
    - 꼭지점을 읽음
  - Clipper and Primitive Assembler: 2D image -> Primitives
    - 점을 선으로 연결, 주어진 도형 가장 많이 삼각형으로 사용
  - Rasterizer: Primitives -> Fragments
    - 선을 삼각형으로 채움
  - Fragment Processor: Fragments -> 2D image
    - 삼각형을 채워서 2D image로 변환
    - 삼각형의 내부를 채워서 색을 채움

이 과정을 스트리밍으로 진행하여 메모리 문제를 해결

1980년대 후반에 픽사가 이 기술을 사용하여 애니메이션을 제작

하지만 고질적인 빛 문제를 해결하지 못한

여기서 보여지는 기술인 야매적인 방법으로 면의 형태를 읽어 빛이 반사되는 과정을 계산

즉, 벡터로 면의 방향을 읽어 외적, 내적을 통해 빛이 반사되는 과정을 계산

실제로 해당 영상을 보면 간접광이 없이 빛이 하나로 이어지고 면의 색이 일정함 즉, 어색함

## GC03

### 복습

- Vertex 꼭지점을 읽음 이 과정이 Projection
- Rasterization: 칠해야할 픽셀들, 점들 -> Fragment
  - 각각의 점마다 색을 결정함 이 과정을 -> Fragment Processing
  - Fragment Processing: Fragment -> 2D image
    - 색을 결정하는 과정
    - 여기서 빛의 반사를 계산하는 것이 중요
    - 꼭지점으로 이뤄진 삼각형의 색을 결정하는 것이다.

위의 연산은 벡터, 행렬 연산 즉, 실수 계산으로 이뤄짐

이 계산을 얼마나 빠르게 하느냐가 속도에 영향을 줌

![Alt text](image-1.png)

병렬처리에 매우 적합

CPU는 더 복잡한 연산을 수행(메모리 관리, 프로그램 실행 등등) 대부분의 컴퓨터가 4~16개가 있다.

CPU는 비용이 쎄서 이를 대체하기 위해 GPU가 등장

GPU는 병렬처리에 매우 적합하다.

단순한 일 처리에 적합

초창기엔 Graphics processor라고 불렸다.

하지만 발전에 따라 Vertex Processor, Fragment Processor를 직접 프로그래밍할 수 있게 되고

좀 더 많은 일을 담당하게 되었다.

### OpenGL

*OpenGL을 사용하기 앞서 말한 행렬을 반환하는 기능들을 담고 있는 라이브러리*

강의 교안에 따라 설치작업

*개인적으로 Vscode 사용법 알아오기*

## GC04

## GC06

## GC07

쉐이더는 GPU의 계산에 따라 보이는 위치, 색 등을 결정할 수 있다.

Vertex Shader: Vertex Processor

Fragment Shader: Fragment Processor

OpenGL의 쉐이더는 GLSL이라는 언어로 작성

- C언어와 유사
  - 하지만 동적할당, 재귀, 다이나믹 등등은 제한
- 빌트인 수학, 벡터, 행렬 연산등의 함수가 있음
  
모든 쉐이더는 main함수를 가지고 있어야함

```c
void main(void) {
  ...
}
```

### GLSL Data Types

- float, int, bool
- vec2, vec3, vec4 (float vector)
- ivec2, ivec3, ivec4 (int vector)
- bvec2, bvec3, bvec4 (bool vector)
- mat2, mat3, mat4 (float matrix)
- sampler2D (texture)

생성자처럼 사용 가능함

```c
vec3 v = vec3(1.0, 2.0, 3.0);
```

또한 벡터 데이터는 다음과 같이 접근 가능

- x, y, z, w
- r, g, b, a
- s, t, p, q
- 배열과 같이 [0]...

```c
vec3 v = vec3(1.0, 2.0, 3.0);
v.x = 4.0;
v[1] = 5.0;
```

### GLSL Matrix

- mat2, mat3, mat4

```c
mat2 m = mat2(1.0, 2.0, 3.0, 4.0);

// [1.0, 2.0]
// [3.0, 4.0]
```

실제로 선형대수학을 컴퓨터에 맞게 사용하려면 row-major가 아닌 column-major로 사용해야함

### GLSL Example

```c
#version 330

uniform	float uTheta1;
uniform	float uTheta2;

in vec4 vPosition;
in vec4 vColor;

out vec4 color;

void main()
{
	float rad1 = uTheta1 / 180.0 * 3.141592;
	mat4 m = mat4(1.0);
	m[0][0] = cos(rad1); m[1][0] = 0; m[2][0] = sin(rad1); m[3][0] = 0; 
	m[0][1] = 0; m[1][1] = 1; m[2][1] = 0; m[3][1] = 0;
	m[0][2] =  -sin(rad1); m[1][2] = 0; m[2][2] = cos(rad1); m[3][2] = 0;
	m[0][3] = 0; m[1][3] = 0; m[2][3] = 0; m[3][3] = 1;

	float rad2 = uTheta2 / 180.0 * 3.141592;
	mat4 n = mat4(1.0);
	n[0][0] = 1; n[1][0] = 0; n[2][0] = 0; n[3][0] = 0; 
	n[0][1] = 0; n[1][1] = cos(rad2); n[2][1] = -sin(rad2) ; n[3][1] = 0;
	n[0][2] = 0; n[1][2] = sin(rad2); n[2][2] = cos(rad2); n[3][2] = 0;
	n[0][3] = 0; n[1][3] = 0; n[2][3] = 0; n[3][3] = 1; 
	
	gl_Position = m*n*vPosition;

	color = vColor;
}
```

이 쉐이더 코드에서 in, out은 다음과 같이 사용

- in: Vertex Shader -> Fragment Shader
- out: Fragment Shader -> Frame Buffer

즉 넘겨주는 역할

![Alt text](image-2.png)

여기서 gl_Position은 Vertex Shader의 내장 변수로 Vertex Shader의 결과를 저장하는 변수

Uniform은 CPU에서 GPU로 데이터를 전달하는 역할

즉 실제 코드에서 쉐이더관련을 직접 제어하기 좋음

