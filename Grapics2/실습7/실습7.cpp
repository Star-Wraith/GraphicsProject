#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>



using namespace std;

int COUNT = 0;
int COUNT1 = 0;
int COUNT2 = 0;
int COUNT3 = 0;
int flag = 1;
int K_flag = 1;
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체
GLuint s_program;
void InitBuffer();
void InitShader();

GLvoid Keyboard(unsigned char key, int x, int y);
void make_vertexShader();
void make_fragmentShader();

GLfloat tx = 0.5, ty = 0.5;
GLfloat tx1 = -0.6, ty1 = -0.6;
GLfloat tx2 = 0.6, ty2 = -0.6;
GLfloat tx3 = -0.4, ty3 = 0.4;
GLfloat SIZE_tri = 0;

GLfloat R = 0.3, G = 0.0, B = 0.0;
GLfloat R1 = 0.0, G1 = 1.0, B1 = 0.0;
GLfloat R2 = 0.0, G2 = 0.0, B2 = 1.0;
GLfloat R3 = 0.0, G3 = 0.5, B3 = 0.5;

GLfloat triShape[3][3] = { //--- 삼각형 위치 값
{ -0.15 + tx, -0.15 + ty, 0.0 }, { 0.15 + tx, -0.15 + ty, 0.0 }, { 0.0 + tx, 0.3 + ty, 0.0} };
GLfloat colors[3][3] = { //--- 삼각형 꼭지점 색상
{ R, G, B }, { R, G, B }, { R, G, B } };


GLfloat triShape1[3][3] = { //--- 삼각형 위치 값
{ -0.15 + tx1, -0.15 + ty1, 0.0 }, { 0.15 + tx1, -0.15 + ty1, 0.0 }, { 0.0 + tx1, 0.3 + ty1, 0.0} };
GLfloat colors1[3][3] = { //--- 삼각형 꼭지점 색상
{ R1, G1, B1 }, { R1, G1, B1 }, { R1, G1, B1 } };


GLfloat triShape2[3][3] = { //--- 삼각형 위치 값
{ -0.15 + tx2, -0.15 + ty2, 0.0 }, { 0.15 + tx2, -0.15 + ty2, 0.0 }, { 0.0 + tx2, 0.3 + ty2, 0.0} };
GLfloat colors2[3][3] = { //--- 삼각형 꼭지점 색상
{ R2, G2, B2 }, { R2, G2, B2 }, { R2, G2, B2 } };

GLfloat triShape3[3][3] = { //--- 삼각형 위치 값
{ -0.15 + tx3, -0.15 + ty3, 0.0 }, { 0.15 + tx3, -0.15 + ty3, 0.0 }, { 0.0 + tx3, 0.3 + ty3, 0.0} };
GLfloat colors3[3][3] = { //--- 삼각형 꼭지점 색상
{ R3, G3, B3 }, { R3, G3, B3 }, { R3, G3, B3 } };

GLuint vao, vbo[2];
GLuint vao1, vao2, vao3;
GLuint vbo1[2], vbo2[2], vbo3[3];
GLfloat X, X1, X2, X3, Y, Y1, Y2, Y3;

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fopen_s(&fptr, file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}


void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{

	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();

	InitBuffer();

	glutDisplayFunc(drawScene);

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정

	glutMainLoop();
}

void make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShader()
{

	fragmentsource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}



void InitBuffer()
{






	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	//----------------------------------

	glGenVertexArrays(1, &vao1);
	glBindVertexArray(vao1);
	glGenBuffers(2, vbo1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(2, vbo2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape2, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao3);
	glBindVertexArray(vao3);
	glGenBuffers(2, vbo3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape3, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);



}

void InitShader()
{
	make_vertexShader(); //--- 버텍스 세이더 만들기
	make_fragmentShader(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);
	//checkCompileErrors(s_program, "PROGRAM");
	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);


	//--- Shader Program 사용하기
	glUseProgram(s_program);

}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	GLfloat rColor, gColor, bColor;
	rColor = 1, gColor = 1, bColor = 1;

	glClearColor(rColor, gColor, bColor, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(s_program);
	//--- 사용할 VAO 불러오기

		glBindVertexArray(vao);
		//--- 삼각형 그리기
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vao3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	


	glutSwapBuffers(); //--- 화면에 출력하기




}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void move_Triangle(int value)
{


	

	if (COUNT == 0)
	{
		if (triShape[1][0] >= 0.99 )
		{
			triShape[2][0] = 1 - 0.45;
			
			triShape[0][1] = triShape[0][1] - 0.15;
			triShape[1][1] = triShape[0][1] + 0.3;
			triShape[2][1] = triShape[1][1] - 0.15;
			triShape[1][0] = 1;
			triShape[0][0] = 1;
			
			
			COUNT++;
			
			
		}
		triShape[0][0] += 0.02;
		triShape[0][1] -= 0.02;
		triShape[1][0] += 0.02;
		triShape[1][1] -= 0.02;
		triShape[2][0] += 0.02;
		triShape[2][1] -= 0.02;
	}
	if (COUNT % 4 == 1)
	{
		if (triShape[0][1] <= -0.99 || triShape[2][0] <= -0.99)
		{
			
			triShape[0][0] = triShape[0][0] - 0.15;
			triShape[0][1] = -1;
			triShape[1][0] = triShape[0][0] + 0.3;
			triShape[1][1] = -1;
			triShape[2][0] = triShape[0][0] + 0.15;
			triShape[2][1] = -1 + 0.45;
			++COUNT;
		}
		triShape[0][0] -= 0.02;
		triShape[0][1] -= 0.02;
		triShape[1][0] -= 0.02;
		triShape[1][1] -= 0.02;
		triShape[2][0] -= 0.02;
		triShape[2][1] -= 0.02;
	}
	if (COUNT % 4 == 2)
	{
		if (triShape[0][0] <= -0.99 || triShape[2][1] >= 0.99)
		{
			triShape[0][0] = -1;
			triShape[0][1] = triShape[0][1] + 0.15;
			triShape[1][0] = -1;
			triShape[1][1] = triShape[0][1] - 0.3;
			triShape[2][0] = -1 + 0.45;
			triShape[2][1] = triShape[0][1] - 0.15;

			++COUNT;
		}		

		triShape[0][0] -= 0.02;
		triShape[0][1] += 0.02;
		triShape[1][0] -= 0.02;
		triShape[1][1] += 0.02;
		triShape[2][0] -= 0.02;
		triShape[2][1] += 0.02;
	}
	if (COUNT %4 == 3)
	{


		if (triShape[0][1] >= 0.99 || triShape[2][0] >= 0.99)
		{
			triShape[0][0] = triShape[0][0] + 0.15;
			triShape[0][1] = 1;
			triShape[1][0] = triShape[0][0] - 0.3;
			triShape[1][1] = 1;
			triShape[2][0] = triShape[0][0] - 0.15;
			triShape[2][1] = 1 - 0.45;
			++COUNT;
		}


		triShape[0][0] += 0.02;
		triShape[0][1] += 0.02;
		triShape[1][0] += 0.02;
		triShape[1][1] += 0.02;
		triShape[2][0] += 0.02;
		triShape[2][1] += 0.02;
	}

	if (COUNT % 4 == 0 && COUNT != 0)
	{
		if (triShape[0][0] >= 0.99 || triShape[2][1] <= -0.99)
		{
			triShape[0][0] = 1;
			triShape[0][1] = triShape[0][1] - 0.15;
			triShape[1][0] = 1;
			triShape[1][1] = triShape[0][1] + 0.3;
			triShape[2][0] = 1 - 0.45;
			triShape[2][1] = triShape[0][1] + 0.15;
			++COUNT;
		}

		triShape[0][0] += 0.02;
		triShape[0][1] -= 0.02;
		triShape[1][0] += 0.02;
		triShape[1][1] -= 0.02;
		triShape[2][0] += 0.02;
		triShape[2][1] -= 0.02;
	}
	//----------------------------------
	if (COUNT1 %4 == 0)
	{


		if (triShape1[0][0] <= -0.99 || triShape1[2][1] >= 0.99)
		{
			triShape1[0][0] = -1;
			triShape1[0][1] = triShape1[0][1] + 0.15;
			triShape1[1][0] = -1;
			triShape1[1][1] = triShape1[0][1] - 0.3;
			triShape1[2][0] = -1 + 0.45;
			triShape1[2][1] = triShape1[0][1] - 0.15;
			

			++COUNT1;
		}



		triShape1[0][0] -= 0.015;
		triShape1[0][1] += 0.015;
		triShape1[1][0] -= 0.015;
		triShape1[1][1] += 0.015;
		triShape1[2][0] -= 0.015;
		triShape1[2][1] += 0.015;
	}
	if (COUNT1 % 4 == 1)
	{

		if (triShape1[0][1] >= 0.99 || triShape1[2][0] >= 0.99)
		{
			triShape1[0][0] = triShape1[0][0] + 0.15;
			triShape1[0][1] = 1;
			triShape1[1][0] = triShape1[0][0] - 0.3;
			triShape1[1][1] = 1;
			triShape1[2][0] = triShape1[0][0] - 0.15;
			triShape1[2][1] = 1 - 0.45;
			++COUNT1;
		}



		triShape1[0][0] += 0.015;
		triShape1[0][1] += 0.015;
		triShape1[1][0] += 0.015;
		triShape1[1][1] += 0.015;
		triShape1[2][0] += 0.015;
		triShape1[2][1] += 0.015;
	}
	if (COUNT1 % 4 == 2)
	{

		if (triShape1[0][0] >= 0.99 || triShape1[2][1] <= -0.99)
		{
			triShape1[0][0] = 1;
			triShape1[0][1] = triShape1[0][1] - 0.15;
			triShape1[1][0] = 1;
			triShape1[1][1] = triShape1[0][1] + 0.3;
			triShape1[2][0] = 1 - 0.45;
			triShape1[2][1] = triShape1[0][1] + 0.15;
			++COUNT1;
		}


		triShape1[0][0] += 0.015;
		triShape1[0][1] -= 0.015;
		triShape1[1][0] += 0.015;
		triShape1[1][1] -= 0.015;
		triShape1[2][0] += 0.015;
		triShape1[2][1] -= 0.015;
	}
	if (COUNT1 % 4 == 3)
	{

		if (triShape1[0][1] <= -0.99 || triShape1[2][0] >= 0.99)
		{
			triShape1[0][0] = triShape1[0][0] - 0.15;
			triShape1[0][1] = -1;
			triShape1[1][0] = triShape1[0][0] + 0.3;
			triShape1[1][1] = -1;
			triShape1[2][0] = triShape1[0][0] + 0.15;
			triShape1[2][1] = -1 + 0.45;
			++COUNT1;
		}


		triShape1[0][0] -= 0.015;
		triShape1[0][1] -= 0.015;
		triShape1[1][0] -= 0.015;
		triShape1[1][1] -= 0.015;
		triShape1[2][0] -= 0.015;
		triShape1[2][1] -= 0.015;
	}

	if (COUNT2 % 4 == 0)
	{
		if (triShape2[1][0] >= 0.99 || triShape2[2][1] >= 0.99)
		{
			triShape2[0][0] = 1;
			triShape2[0][1] = triShape2[0][1] - 0.15;
			triShape2[1][0] = 1;
			triShape2[1][1] = triShape2[0][1] + 0.3;
			triShape2[2][0] = 1 - 0.45;
			triShape2[2][1] = triShape2[0][1] + 0.15;
			++COUNT2;
		}

		triShape2[0][0] += 0.01;
		triShape2[0][1] += 0.01;
		triShape2[1][0] += 0.01;
		triShape2[1][1] += 0.01;
		triShape2[2][0] += 0.01;
		triShape2[2][1] += 0.01;
	}
	if (COUNT2 % 4 == 1)
	{
		if (triShape2[1][1] >= 0.95 || triShape2[2][0] <= -0.99)
		{

			triShape2[0][0] = triShape2[0][0] + 0.15;
			triShape2[0][1] = 1;
			triShape2[1][0] = triShape2[0][0] - 0.3;
			triShape2[1][1] = 1;
			triShape2[2][0] = triShape2[0][0] - 0.15;
			triShape2[2][1] = 1 - 0.45;
			++COUNT2;
		}
		triShape2[0][0] -= 0.01;
		triShape2[0][1] += 0.01;
		triShape2[1][0] -= 0.01;
		triShape2[1][1] += 0.01;
		triShape2[2][0] -= 0.01;
		triShape2[2][1] += 0.01;
	}
	if (COUNT2 % 4 == 2)
	{
		if (triShape2[1][0] <= -0.99 || triShape2[2][1] <= -0.99)
		{
			triShape2[0][0] = -1;
			triShape2[0][1] = triShape2[0][1] + 0.15;
			triShape2[1][0] = -1;
			triShape2[1][1] = triShape2[0][1] - 0.3;
			triShape2[2][0] = -1 + 0.45;
			triShape2[2][1] = triShape2[0][1] - 0.15;

			++COUNT2;
		}

		triShape2[0][0] -= 0.01;
		triShape2[0][1] -= 0.01;
		triShape2[1][0] -= 0.01;
		triShape2[1][1] -= 0.01;
		triShape2[2][0] -= 0.01;
		triShape2[2][1] -= 0.01;
	}
	if (COUNT2 % 4 == 3)
	{


		if (triShape2[1][1] <= -0.99 || triShape2[2][0] >= 0.99)
		{
			triShape2[0][0] = triShape2[0][0] - 0.15;
			triShape2[0][1] = -1;
			triShape2[1][0] = triShape2[0][0] + 0.3;
			triShape2[1][1] = -1;
			triShape2[2][0] = triShape2[0][0] + 0.15;
			triShape2[2][1] = -1 + 0.45;
			++COUNT2;
		}


		triShape2[0][0] += 0.01;
		triShape2[0][1] -= 0.01;
		triShape2[1][0] += 0.01;
		triShape2[1][1] -= 0.01;
		triShape2[2][0] += 0.01;
		triShape2[2][1] -= 0.01;
	}


	if (COUNT3 == 0)
	{
		if (triShape3[0][0] <= -0.99)
		{
			triShape3[2][0] = -1 + 0.45;

			triShape3[0][1] = triShape3[0][1] + 0.15;
			triShape3[1][1] = triShape3[0][1] - 0.3;
			triShape3[2][1] = triShape3[0][1] - 0.15;
			triShape3[1][0] = -1;
			triShape3[0][0] = -1;


			COUNT3++;


		}
		triShape3[0][0] -= 0.025;
		triShape3[0][1] -= 0.025;
		triShape3[1][0] -= 0.025;
		triShape3[1][1] -= 0.025;
		triShape3[2][0] -= 0.025;
		triShape3[2][1] -= 0.025;
	}
	if (COUNT3 % 4 == 1)
	{
		if (triShape3[1][1] <= -0.99 || triShape3[2][1] >= 0.99)
		{

			triShape3[0][0] = triShape3[0][0] - 0.15;
			triShape3[0][1] = -1;
			triShape3[1][0] = triShape3[0][0] + 0.3;
			triShape3[1][1] = -1;
			triShape3[2][0] = triShape3[0][0] + 0.15;
			triShape3[2][1] = -1 + 0.45;
			++COUNT3;
		}
		triShape3[0][0] += 0.025;
		triShape3[0][1] -= 0.025;
		triShape3[1][0] += 0.025;
		triShape3[1][1] -= 0.025;
		triShape3[2][0] += 0.025;
		triShape3[2][1] -= 0.025;
	}
	if (COUNT3 % 4 == 2)
	{
		if (triShape3[1][0] >= 0.99 || triShape3[2][1] >= 0.99)
		{
			triShape3[0][0] = 1;
			triShape3[0][1] = triShape3[0][1] - 0.15;
			triShape3[1][0] = 1;
			triShape3[1][1] = triShape3[0][1] + 0.3;
			triShape3[2][0] = 1 - 0.45;
			triShape3[2][1] = triShape3[0][1] + 0.15;

			++COUNT3;
		}

		triShape3[0][0] += 0.025;
		triShape3[0][1] += 0.025;
		triShape3[1][0] += 0.025;
		triShape3[1][1] += 0.025;
		triShape3[2][0] += 0.025;
		triShape3[2][1] += 0.025;
	}
	if (COUNT3 % 4 == 3)
	{


		if (triShape3[1][1] >= 0.99 || triShape3[2][0] <= -0.99)
		{
			triShape3[0][0] = triShape3[0][0] + 0.15;
			triShape3[0][1] = 1;
			triShape3[1][0] = triShape3[0][0] - 0.3;
			triShape3[1][1] = 1;
			triShape3[2][0] = triShape3[0][0] - 0.15;
			triShape3[2][1] = 1 - 0.45;
			++COUNT3;
		}


		triShape3[0][0] -= 0.025;
		triShape3[0][1] += 0.025;
		triShape3[1][0] -= 0.025;
		triShape3[1][1] += 0.025;
		triShape3[2][0] -= 0.025;
		triShape3[2][1] += 0.025;
	}
	if (COUNT3 % 4 == 0 && COUNT3 != 0)
	{
		if (triShape3[1][0] <= -0.99 || triShape[2][1] <= -0.99)
		{
			triShape3[0][0] = -1;
			triShape3[0][1] = triShape3[0][1] + 0.15;
			triShape3[1][0] = -1;
			triShape3[1][1] = triShape3[0][1] - 0.3;
			triShape3[2][0] = -1 + 0.45;
			triShape3[2][1] = triShape3[0][1] - 0.15;
			++COUNT3;
		}

		triShape3[0][0] -= 0.02;
		triShape3[0][1] -= 0.02;
		triShape3[1][0] -= 0.02;
		triShape3[1][1] -= 0.02;
		triShape3[2][0] -= 0.02;
		triShape3[2][1] -= 0.02;
	}
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glBindVertexArray(vao1); //--- VAO를 바인드하기
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glBindVertexArray(vao2); //--- VAO를 바인드하기
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape2, GL_DYNAMIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glBindVertexArray(vao3); //--- VAO를 바인드하기
	glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape3, GL_DYNAMIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glutPostRedisplay();
	glutTimerFunc(100, move_Triangle, 1);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'o':

		
		glutTimerFunc(100, move_Triangle, 1);
		break;


	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}



	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}
