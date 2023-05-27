#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#define  _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

GLfloat rColor = 0;
GLfloat gColor = 0;
GLfloat bColor = 0;

int nFlag = 1;

int COUNT = 1;
bool left_button = false;
using namespace std;

glm::vec4* vertex;

glm::vec4* face;

int vertexNum = 0;
int faceNum = 0;
int vertIndex = 0;
int faceIndex = 0;

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

void ReadObj(const char* objFile);




GLfloat Vertex_Line[3][3]{
	{-0.2,0,0},
	{0.2,0,0},
	{0,0.4,0}

};



GLfloat colors[3][3]{
	{0,0,1},
	{0,0,1},
	{0,0,1}

};



GLuint vao, vbo[2];



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

void ReadObj(const char* obj)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[65535];
	char bind[65535];
	FILE* objFile;
	fopen_s(&objFile, obj, "rb");
	//int vertexNum = 0;
	//int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}
	//--- 2. 메모리 할당
	
	//glm::vec4* vertex;
	//glm::vec4* face;
	//int vertIndex = 0;
	//int faceIndex = 0;
	vertex = (glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	face = (glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);
	fopen_s(&objFile, obj, "rb");
	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);
		cout << bind[0] << endl;
		if (bind[0] == 'v' ) {
			fscanf(objFile, "%f %f %f",
				&vertex[vertIndex].x, &vertex[vertIndex].y,
				&vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f') {
			fscanf(objFile, "%f %f %f",
				&face[faceIndex].x, &face[faceIndex].y, &face[faceIndex].z);
			faceIndex++;
		}
	}
}




void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	if (COUNT == 1)
	{
		ReadObj("cube.obj");
		COUNT++;
	}

	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
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


	cout << vertex[0].x << endl;

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,  3 * vertexNum * sizeof(glm::vec3), vertex, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	//glBufferData(GL_ARRAY_BUFFER, 3 * faceNum * sizeof(GLfloat), face, GL_DYNAMIC_DRAW);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(1);

	//glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	//glBindVertexArray(vao); //--- VAO를 바인드하기
	//glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기




	//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Vertex_Line, GL_DYNAMIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(0);
	////----------------------------------
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glEnableVertexAttribArray(1);





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


	glClearColor(rColor, gColor, bColor, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(s_program);
	//--- 사용할 VAO 불러오기

	//glm::mat4 Tx = glm::mat4(1.0f);
	//glm::mat4 Rz = glm::mat4(1.0f);
	//glm::mat4 TR = glm::mat4(1.0f);

	//Tx = glm::translate(Tx, glm::vec3(0.5, 0.0, 0.0));
	//Rz = glm::rotate(Rz, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));

	//TR = Tx * Rz;

	//unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertIndex);






	glutSwapBuffers(); //--- 화면에 출력하기




}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}





GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{


	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}



	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		std::cout << "x = " << x << "y = " << y << std::endl;

		left_button = true;
	}
	else
	{
		left_button = false;
	}

}