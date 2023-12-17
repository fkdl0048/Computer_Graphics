# 기말고사 정리

## 개념 정리

- 범위 13강~25강

### Transformation Pipeline

- 객체 좌표계 -> 카메라 좌표계 -> 화면 좌표계
  - Modeling Coordinates
    - (Model Transform)local to world
  - World Coordinates
    - (View Transform)world to camera
  - Normalized Coordinates
    - (Projection Transform)camera to screen

로컬, 모델 좌표계에서 월드 좌표계로 이동 (Model Transform)

월드 좌표계에서 카메라 좌표계로 이동 (View Transform)

카메라 좌표계에서 화면 좌표계로 이동 (Projection Transform)

이 과정은 4x4 행렬로 표현된다.

### Instance Transformation

- 모델링 좌표계에서의 변환
  - 이동, 회전, 스케일링

### Hierarchical Modeling

일종의 트리 구조로 모델링을 한다.

### Current Transformation Matrix

일명 CTM

- 현재 변환 행렬
  - 현재 변환 행렬을 곱해주면 된다.

모델 뷰와 projection 행렬에서 사용한다.

### The lookAt Function

- gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz)
  - ex, ey, ez : eye position
  - cx, cy, cz : focus position
  - ux, uy, uz : up vector
- 월드 프레임을 카메라 프레임으로 변환
  - Compose a rotation R with translation T
  - T를 사용하여 회전 R을 구성한다.
  - W = T R
- 보기 변환 V를 얻기 위해 W를 반전시킨다.
  - V = W^-1 = R^-1 T^-1

### World Frame to Camera Frame

- 카메라 포인트는 z축을 따라 -1로 이동한다.
- n방향은 f-e 방향으로 정규화한다.

### Projection Matrices

프로젝션은 3차원 공간을 2차원 공간으로 변환한다.

투영은 되돌릴 수 없다.

4x4 행렬로 표현된다.

동형 좌표가 중요함

평행 및 원근 투영이 있다.

### Parallel Projection

평행선을 통해 3D 객체를 2D로 투영한다.

*선들이 사영에 반드시 직교하는 것은 아니다.*

- 불가능한 문제로 이어질 수 있다.

### Orthographic Projection

- 단순하게 2D로 투영하기에 단순하지만 현실적이지 않다.
- 주로 2D 도면을 만들 때 사용한다.

4x4 행렬에서 z축을 0으로 만들어주면 된다. (단순 투영)

openGL에서는 glOrtho()를 사용한다.

- glOrtho(left, right, bottom, top, near, far)
  - left, right : x축의 범위
  - bottom, top : y축의 범위
  - near, far : z축의 범위

이 과정에서 Normalizetion이 일어난다.

### Orthogonal Matrix

- 가장 먼저 Centering을 한다. (원점으로 중심이동)
  - T(-(left+right)/2, -(bottom+top)/2, -(near+far)/2)
  - 마지막인자를 near로 하는 경우도 있다.
- Scaling을 한다. (정규화)
  - S(2/(right-left), 2/(top-bottom), 2/(far-near))

### Perspective Projection

16

## 문제풀이