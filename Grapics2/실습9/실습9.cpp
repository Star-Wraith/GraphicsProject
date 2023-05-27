#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

double MAX = 32767;
GLfloat rColor = 1;  
GLfloat gColor = 1;
GLfloat bColor = 1;

GLfloat r = 0.00;
GLfloat D = 6;
GLfloat r1 = 0.00;
GLfloat D1 = 6;
GLfloat r2 = 0.00;
GLfloat D2 = 6;

using namespace std;

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체
GLuint s_program;
void InitBuffer();
void InitShader();

GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void make_vertexShader();
void make_fragmentShader();

GLfloat tx = 0, ty = 0.45;
GLfloat tx1 = 0, ty1 = 0.45;

GLfloat R = 1, G = 1, B = 1;


GLfloat triShape[212] = { //---점의 값
{ 0 } };
GLfloat colors[212] = { //--- 삼각형 꼭지점 색상
	0 };

GLfloat triShape1[212] = { //---점의 값
{ 0 } };
GLfloat colors1[212] = { //--- 삼각형 꼭지점 색상
	0 };


int VC = 3;
int COUNT = 1;
int NCOUNT = 1;
int SCOUNT = 1;
int VC1 = 3;
int VC2 = 0;

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
	for (int i = 0; i < 212; i++)
	{
		colors[i] = 1;
	}
	for (int i = 0; i < 212; i++)
	{
		colors1[i] = 1;
	}
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 800);
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
	glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao1); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao1); //--- VAO를 바인드하기
	glGenBuffers(2, vbo1); //--- 2개의 VBO를 지정하고 할당하기


	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	//----------------------------------


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
	glPointSize(3);
	glDrawArrays(GL_POINTS, 0, COUNT-1); 

	if (SCOUNT >= 69)
	{
		glBindVertexArray(vao1);
		glDrawArrays(GL_POINTS, 0, NCOUNT-1);
	}

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


void Get_tornado(int value)
{
	if (COUNT == 1)
	{

		triShape[0] = tx;
		triShape[1] = ty;
		triShape[2] = 0;


		
		glBindVertexArray(vao); //--- VAO를 바인드하기
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(0);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);
		colors[0] = 1;
		colors[1] = 1;
		colors[2] = 1;
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		COUNT++;
		VC = VC + 3;
	}
	else if (COUNT >= 2 && D<=408)
	{

		
		triShape[VC] = tx + r * cos(D);
		triShape[VC+1] = ty + r * sin(D);
		triShape[VC + 2] = 0;

		colors[VC] = 1;
		colors[VC+1] = 1;
		colors[VC+2] = 1;





		glBindVertexArray(vao); //--- VAO를 바인드하기
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //모르겠다.//여기서부터
		glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		//glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		COUNT++;
		SCOUNT++;

		D += 6;
		if (D <= 408)
		{
			VC = VC + 3;
			r += 0.002;
		}
	}
	else if (D >= 408 && D1<=396)
	{
		if (NCOUNT == 1)
		{
			printf("\t%dafdfdfads", VC);

			tx1 = triShape[VC] + triShape[VC] - triShape[0]+0.01;
			ty1 = ty;
			VC2 = VC;
			r2 = r;
			D2 = D-24;

			for (int j = 0; j <= VC2; j += 3)
			{
				triShape1[j] = tx1 - r2 * cos(D2);
				triShape1[j+1] = ty1 - r2 * sin(D2);
				triShape1[j + 2] = 0;
				//colors1[j] = 1;
				//colors1[j+1] = 1;
				//colors1[j+2] = 1;
				r2 -= 0.002;
				D2 -= 6;
				printf("%d\t", j);
				printf("%lf 값\n", triShape1[j]);
			}

			colors1[0] = 1;
			colors1[1] = 1;
			colors1[2] = 1;

			glBindVertexArray(vao1); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


			//glEnableVertexAttribArray(0);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
			colors1[VC1] = 1;
			colors1[VC1 + 1] = 1;
			colors1[VC1 + 2] = 1;
			VC1 = VC1 + 3;
			NCOUNT++;
		}
		colors1[VC1] = 1;
		colors1[VC1 + 1] = 1;
		colors1[VC1 + 2] = 1;


			glBindVertexArray(vao1); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]); //모르겠다.//여기서부터
			glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


			//glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

			glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);

		
			VC1 = VC1 + 3;
			//r1 += 0.002;
			D1 += 6;
			NCOUNT++;
	

	}
	glutPostRedisplay();

	glutTimerFunc(100, Get_tornado, 1);
}
void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		for (int i = 0; i < 212; i++)
		{
			triShape[i] = 0;

		}
		for (int i = 0; i < 212; i++)
		{
			triShape1[i] = 0;
		}


		rColor = (GLfloat)(rand() / MAX);
		gColor = (GLfloat)(rand() / MAX);
		bColor = (GLfloat)(rand() / MAX);
		for (int i = 0; i <= 212; i += 3)
		{
			colors[i] = rColor;
			colors[i + 1] = gColor;
			colors[i + 2] = bColor;
		}
		for (int i = 0; i <= 212; i += 3)
		{
			colors1[i] = rColor;
			colors1[i + 1] = gColor;
			colors1[i + 2] = bColor;

		}

		glBindVertexArray(vao); //--- VAO를 바인드하기
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
		glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		//glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		glBufferData(GL_ARRAY_BUFFER, VC * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		glBindVertexArray(vao1); //--- VAO를 바인드하기
		glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]); //모르겠다.//여기서부터
		glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		//glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

		glBufferData(GL_ARRAY_BUFFER, VC1 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		NCOUNT = 1;
		COUNT = 1;
		VC = 3;
		VC1 = 3;
		D = 0;
		D1 = 0;
		r = 0;
		std::cout << "x = " << x << "y = " << y << std::endl;	
			if (x >= 500)
			{
				tx = (x - 500.0) / 500.0;
				if (y >= 400)
				{

					ty = -(y - 400.0) / 400.0;
				}
				else
				{
					ty = 1 - y / 400.0;

				}
			}
			else if (0 < x && x < 500)
			{
				tx = -1.0 + x / 500.0;
				if (y >= 400)
				{

					ty = -(y - 400.0) / 400.0;

				}
				else
				{
					ty = 1 - y / 400.0;


				}
			}


		glutTimerFunc(100, Get_tornado, 1);
	}

	glutPostRedisplay();

}