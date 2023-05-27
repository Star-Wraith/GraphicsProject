#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

GLfloat rColor = 1;
GLfloat gColor = 1;
GLfloat bColor = 1;

int nFlag = 1;

bool left_button = false;
using namespace std;


GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체
GLuint s_program;
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void InitBuffer();
void InitShader();

GLvoid Keyboard(unsigned char key, int x, int y);
void make_vertexShader();
void make_fragmentShader();
void LT_conversion(int value);
void TR_conversion(int value);
void RP_conversion(int value);
void PV_conversion(int value);

int Rx = 200;
int Ry = 450;
int Rx1 = 200;
int Ry1 = 150;
int Rx2 = 600;
int Ry2 = 150;
int Rx3 = 600;
int Ry3 = 450;
int tmpy;
int COUNT = 0;


GLfloat Vertex_Line[8][3]{
	{-0.5,-0.5,0},{-0.5,0.5,0},
	{-0.5,0.5,0},{0.5,0.5,0},
	{0.5,0.5,0},{0.5,-0.5,0},
	{0.5,-0.5,0},{-0.5,-0.5,0}
};
GLfloat Y = -0.5, Y1 = 0.5, Y2 = 0.5, Y3 = 0.5, Y4 = 0.5, Y5 = -0.5, Y6 = -0.5, Y7 = -0.5;
GLfloat X = -0.5, X1 = -0.5, X2 = -0.5, X3 = 0.5, X4 = 0.5, X5 = 0.5, X6 = 0.5, X7 = -0.5;

GLfloat colors[8][3]{
	{1,0,0},{1,0.64,0},
	{1,1,0},{0,1,0},
	{0,0,1},{0,0,0.5},
	{1,0,1},{1,0.75,0.79}
};


GLfloat XY_LINE[4][3]
{ {-1,0,0},{1,0,0},{0,-1,0} ,{0,1,0}
};
GLfloat colors_Line[4][3] = { //--- 삼각형 꼭지점 색상
	{0,0, 0 },{0,0, 0 },{0,0, 0 },{0,0, 0 } };
GLuint vao, vbo[2];
GLuint vao1, vbo1[2];


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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
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
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), Vertex_Line, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao1); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao1); //--- VAO를 바인드하기
	glGenBuffers(2, vbo1); //--- 2개의 VBO를 지정하고 할당하기


	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), XY_LINE, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors_Line, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	////----------------------------------



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

	glBindVertexArray(vao);
	//--- 삼각형 그리기

	
		glDrawArrays(GL_LINES, 0, 2);
		glDrawArrays(GL_LINES, 2, 4);
		glDrawArrays(GL_LINES, 4, 6);
		glDrawArrays(GL_LINES, 6, 8);



	glBindVertexArray(vao1);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 4);



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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		std::cout << "x = " << x << "y = " << y << std::endl;

		left_button = true;
	}
	else
	{
		left_button = false;
	}

}

void Motion(int x, int y)
{

	
	//GLfloat Vertex_Line[8][3]{
	//	{-0.5,-0.5,0},{-0.5,0.5,0},
	//	{-0.5,0.5,0},{0.5,0.5,0},
	//	{0.5,0.5,0},{0.5,-0.5,0},
	//	{0.5,-0.5,0},{-0.5,-0.5,0}
	//};

	if (left_button == true && x >= Rx1 - 20 && x <= Rx1 + 20 && y >= Ry1 - 20 && y <= Ry1 + 20)
	{
		if (x >= 400)
		{
		
			Vertex_Line[1][0] = -0.5 + (x - 400.0) / 400.0;
			Vertex_Line[2][0] = -0.5 + (x - 400.0) / 400.0;
			


			if (y >= 300)
			{
				
				Vertex_Line[1][1] = 0.5 - (y - 300.0) / 300.0;
				Vertex_Line[2][1] = 0.5 - (y - 300.0) / 300.0;
				
			}
			else
			{
				
				Vertex_Line[1][1] = 0.5 + 1 - y / 300.0;
				Vertex_Line[2][1] = 0.5 + 1 - y / 300.0;
				

			}
		}
		else if (0 < x && x < 400)
		{

			
			Vertex_Line[1][0] =  - 1.0 + x / 400.0;
			Vertex_Line[2][0] =  - 1.0 + x / 400.0;
		

			if (y >= 300)
			{
				
				Vertex_Line[1][1] =  - (y - 300.0) / 300.0;
				Vertex_Line[2][1] =  - (y - 300.0) / 300.0;
			


			}
			else
			{
		
				Vertex_Line[1][1] =  + 1 - y / 300.0;
				Vertex_Line[2][1] =  + 1 - y / 300.0;



			}

		}


		Rx1 = 400 + (Vertex_Line[1][0] * 400);
		Ry1 = 300 - (Vertex_Line[1][1] * 300);


		X1 = Vertex_Line[1][0];
		X2 = Vertex_Line[2][0];

		Y1 = Vertex_Line[1][1];
		Y2 = Vertex_Line[2][1];


	}
	else if (left_button == true && x >= Rx - 20 && x <= Rx + 20 && y >= Ry - 20 && y <= Ry + 20)
	{
		if (x >= 400)
		{

			Vertex_Line[0][0] = -0.5 + (x - 400.0) / 400.0;
			Vertex_Line[7][0] = -0.5 + (x - 400.0) / 400.0;



			if (y >= 300)
			{

				Vertex_Line[0][1] = 0.5 - (y - 300.0) / 300.0;
				Vertex_Line[7][1] = 0.5 - (y - 300.0) / 300.0;

			}
			else
			{

				Vertex_Line[0][1] = 0.5 + 1 - y / 300.0;
				Vertex_Line[7][1] = 0.5 + 1 - y / 300.0;


			}
		}
		else if (0 < x && x < 400)
		{


			Vertex_Line[0][0] = -1.0 + x / 400.0;
			Vertex_Line[7][0] = -1.0 + x / 400.0;


			if (y >= 300)
			{

				Vertex_Line[0][1] = -(y - 300.0) / 300.0;
				Vertex_Line[7][1] = -(y - 300.0) / 300.0;



			}
			else
			{

				Vertex_Line[0][1] = +1 - y / 300.0;
				Vertex_Line[7][1] = +1 - y / 300.0;



			}

		}


		Rx = 400 + (Vertex_Line[0][0] * 400);
		Ry = 300 - (Vertex_Line[7][1] * 300);

		X = Vertex_Line[0][0];
		X7 = Vertex_Line[7][0];

		Y = Vertex_Line[0][1];
		Y7 = Vertex_Line[7][1];

	}
	else if (left_button == true && x >= Rx2 - 20 && x <= Rx2+ 20 && y >= Ry2 - 20 && y <= Ry2 + 20)
	{


			Vertex_Line[3][0] =  (x - 400.0) / 400.0;
			Vertex_Line[4][0] =  (x - 400.0) / 400.0;



				Vertex_Line[3][1] =  1 - y / 300.0;
				Vertex_Line[4][1] =  1 - y / 300.0;



		Rx2 = 400 + (Vertex_Line[3][0] * 400);
		Ry2 = 300 - (Vertex_Line[4][1] * 300);

		X3 = Vertex_Line[3][0];
		X4 = Vertex_Line[4][0];

		Y3 = Vertex_Line[3][1];
		Y4 = Vertex_Line[4][1];

	}
	else if (left_button == true && x >= Rx3 - 20 && x <= Rx3 + 20 && y >= Ry3 - 20 && y <= Ry3 + 20)
	{

		Vertex_Line[5][0] = + (x - 400.0) / 400.0;
		Vertex_Line[6][0] =  + (x - 400.0) / 400.0;

			Vertex_Line[5][1] = -(y - 300.0) / 300.0;
			Vertex_Line[6][1] = -(y - 300.0) / 300.0;
			//여기서부터





	 Rx3 = 400 + (Vertex_Line[5][0] * 400);
	 Ry3 = 300 - (Vertex_Line[6][1] * 300);

	 X5 = Vertex_Line[5][0];
	 X6 = Vertex_Line[6][0];

	 Y5 = Vertex_Line[5][1];
	 Y6 = Vertex_Line[6][1];

	}
    else if (left_button == true && x >= Rx && x <= Rx3 && y >= Ry1 && y <= Ry3)
	{


		if (x >= 400)
		{
			//Vertex_Line[0][0] = -0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[1][0] = -0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[2][0] = -0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[3][0] = 0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[4][0] = 0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[5][0] = 0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[6][0] = 0.5 + (x - 400.0) / 400.0;
			//Vertex_Line[7][0] = -0.5 + (x - 400.0) / 400.0;
			//
			Vertex_Line[0][0] = X + (x - 400.0) / 400.0;
			Vertex_Line[1][0] = X1+ (x - 400.0) / 400.0;
			Vertex_Line[2][0] = X2+ (x - 400.0) / 400.0;
			Vertex_Line[3][0] = X3+ (x - 400.0) / 400.0;
			Vertex_Line[4][0] = X4+ (x - 400.0) / 400.0;
			Vertex_Line[5][0] = X5+ (x - 400.0) / 400.0;
			Vertex_Line[6][0] = X6+ (x - 400.0) / 400.0;
			Vertex_Line[7][0] = X7+ (x - 400.0) / 400.0;

			
		
			if (y >= 300)
			{
				Vertex_Line[0][1] = Y - (y - 300.0) / 300.0;
				Vertex_Line[1][1] = Y1 - (y - 300.0) / 300.0;
				Vertex_Line[2][1] = Y2 - (y - 300.0) / 300.0;
				Vertex_Line[3][1] = Y3 - (y - 300.0) / 300.0;
				Vertex_Line[4][1] = Y4 - (y - 300.0) / 300.0;
				Vertex_Line[5][1] = Y5 - (y - 300.0) / 300.0;
				Vertex_Line[6][1] = Y6 - (y - 300.0) / 300.0;
				Vertex_Line[7][1] = Y7 - (y - 300.0) / 300.0;

			}
			else
			{
				Vertex_Line[0][1] = Y + 1 - y / 300.0;
				Vertex_Line[1][1] = Y1 + 1 - y / 300.0;
				Vertex_Line[2][1] = Y2 + 1 - y / 300.0;
				Vertex_Line[3][1] = Y3 + 1 - y / 300.0;
				Vertex_Line[4][1] = Y4 + 1 - y / 300.0;
				Vertex_Line[5][1] = Y5 + 1 - y / 300.0;
				Vertex_Line[6][1] = Y6 + 1 - y / 300.0;
				Vertex_Line[7][1] = Y7 + 1 - y / 300.0;

			}
		}
		else if (0 < x && x < 400)
		{

			Vertex_Line[0][0] = X -1+ x / 400.0;
			Vertex_Line[1][0] = X1 -1+ x / 400.0;
			Vertex_Line[2][0] = X2 -1+ x / 400.0;
			Vertex_Line[3][0] = X3 -1+ x / 400.0;
			Vertex_Line[4][0] = X4 -1+ x / 400.0;
			Vertex_Line[5][0] = X5 -1+ x / 400.0;
			Vertex_Line[6][0] = X6 -1+ x / 400.0;
			Vertex_Line[7][0] = X7 -1+ x / 400.0;

			if (y >= 300)
			{
				Vertex_Line[0][1] = Y - (y - 300.0) / 300.0;
				Vertex_Line[1][1] = Y1 - (y - 300.0) / 300.0;
				Vertex_Line[2][1] = Y2 - (y - 300.0) / 300.0;
				Vertex_Line[3][1] = Y3 - (y - 300.0) / 300.0;
				Vertex_Line[4][1] = Y4 - (y - 300.0) / 300.0;
				Vertex_Line[5][1] = Y5 - (y - 300.0) / 300.0;
				Vertex_Line[6][1] = Y6 - (y - 300.0) / 300.0;
				Vertex_Line[7][1] = Y7 - (y - 300.0) / 300.0;

	
			}
			else
			{
				Vertex_Line[0][1] = Y + 1 - y / 300.0;
				Vertex_Line[1][1] = Y1 + 1 - y / 300.0;
				Vertex_Line[2][1] = Y2 + 1 - y / 300.0;
				Vertex_Line[3][1] = Y3 + 1 - y / 300.0;
				Vertex_Line[4][1] = Y4 + 1 - y / 300.0;
				Vertex_Line[5][1] = Y5 + 1 - y / 300.0;
				Vertex_Line[6][1] = Y6 + 1 - y / 300.0;
				Vertex_Line[7][1] = Y7 + 1 - y / 300.0;



			}

		}



		Rx = 400 + (Vertex_Line[0][0] * 400);
		Rx1 = 400 + (Vertex_Line[1][0] * 400);
		Rx2 = 400 + (Vertex_Line[3][0] * 400);
		Rx3 = 400 + (Vertex_Line[5][0] * 400);

		Ry = 300 - (Vertex_Line[0][1] * 300);
		Ry1 = 300 - (Vertex_Line[1][1] * 300);
		Ry2 = 300 - (Vertex_Line[3][1] * 300);
		Ry3 = 300 - (Vertex_Line[5][1] * 300);


		


	
	}



	glBindVertexArray(vao); //--- VAO를 바인드하기




	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), Vertex_Line, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

		glutPostRedisplay();
}
