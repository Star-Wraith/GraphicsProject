#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


using namespace std;

int COUNT = -1;
int flag = 1;
int K_flag = 1;
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLchar* vertexsource, * fragmentsource; //--- 소스코드 저장 변수
GLuint vertexshader, fragmentshader; //--- 세이더 객체
GLuint s_program;
void InitBuffer();
void InitShader();
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void make_vertexShader();
void make_fragmentShader();

GLfloat tx=0.5, ty=0.5;
GLfloat tx1 = -0.6 ,ty1 = -0.6;
GLfloat tx2 = 0.6, ty2 = -0.6;
GLfloat tx3 = -0.4, ty3 = 0.4;
GLfloat SIZE_tri = 0;

GLfloat R=0.3, G=0.0, B=0.0;
GLfloat R1 = 0.0, G1 = 1.0, B1 = 0.0;
GLfloat R2 = 0.0, G2 = 0.0, B2 = 1.0;
GLfloat R3 = 0.0, G3 = 0.5, B3 = 0.5;

 GLfloat triShape[3][3] = { //--- 삼각형 위치 값
{ -0.15+tx, -0.15+ty, 0.0 }, { 0.15 + tx, -0.15 + ty, 0.0 }, { 0.0 + tx, 0.3 + ty, 0.0} };
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
		if (K_flag == 1)
		{
			glBindVertexArray(vao);
			//--- 삼각형 그리기
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(vao1);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(vao2);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glBindVertexArray(vao3);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else if(K_flag==0)
		{
			glBindVertexArray(vao);
			//--- 삼각형 그리기
			glLineWidth(1);
			glDrawArrays(GL_LINE_LOOP, 0, 3);

			glBindVertexArray(vao1);
			glDrawArrays(GL_LINE_LOOP, 0, 3);

			glBindVertexArray(vao2);
			glDrawArrays(GL_LINE_LOOP, 0, 3);

			glBindVertexArray(vao3);
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}
		//else if (K_flag == 2)
		//{
		//	glBindVertexArray(vao);
		//	glDrawArrays(GL_POLYGON, 0, 3);

		//	glBindVertexArray(vao1);
		//	glDrawArrays(GL_POLYGON, 0, 3);

		//	glBindVertexArray(vao2);
		//	glDrawArrays(GL_POLYGON, 0, 3);

		//	glBindVertexArray(vao3);
		//	glDrawArrays(GL_POLYGON, 0, 3);
		//}

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
	case'a':
		K_flag = 1;

		break;
	case'b':
		K_flag = 0;
		break;
	//case'c':
	//	K_flag = 2;
	//	break;

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
		++COUNT;
		if (COUNT % 4 == 0)
		{
		
				//glDeleteProgram(vao);
			tx = -0.3 , ty = -0.6;
			triShape[0][0] = 0;
			triShape[0][1] = 0;
			triShape[1][0] = 0;
			triShape[1][1] = 0;
			triShape[2][0] = 0;
			triShape[2][1] = 0;

			glBindVertexArray(vao); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
				if (x >= 500)
				{
					tx =  (x - 500.0) / 500.0;
					if (y >= 400)
					{

						ty = - (y - 400.0) / 400.0;
					}
					else
					{
						ty =  1 - y / 500.0;

					}
				}
				else if (0 < x && x < 500)
				{
					tx = -1.0 + x / 500.0;
					if (y >= 400)
					{

						ty = - (y - 400.0) / 400.0;

					}
					else
					{
						ty =   1 - y / 400.0;


					}
				}
			if (flag == 1)
			{
					SIZE_tri += 0.02f;
			}
			else
			{
					SIZE_tri -= 0.02f;
			}

			
			triShape[0][0] = -0.15 + tx -SIZE_tri;
			triShape[0][1] = -0.15 +ty -SIZE_tri;
			triShape[1][0] =  0.15 + tx + SIZE_tri;
			triShape[1][1] = -0.15 + ty - SIZE_tri;
			triShape[2][0] = tx;
			triShape[2][1] = 0.3 + ty + SIZE_tri;
	
			
			//----------------------------------
		}
		if (COUNT % 4 == 1)
		{
			
			triShape1[0][0] = 0;
			triShape1[0][1] = 0;
			triShape1[1][0] = 0;
			triShape1[1][1] = 0;
			triShape1[2][0] = 0;
			triShape1[2][1] = 0;

			glBindVertexArray(vao1); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
			if (x >= 500)
			{
				tx1 = (x - 500.0) / 500.0;
				if (y >= 400)
				{

					ty1 = -(y - 400.0) / 400.0;
				}
				else
				{
					ty1 = 1 - y / 500.0;

				}
			}
			else if (0 < x && x < 500)
			{
				tx1 = -1.0 + x / 500.0;
				if (y >= 400)
				{

					ty1 = -(y - 400.0) / 400.0;

				}
				else
				{
					ty1 = 1 - y / 400.0;


				}
			}
			if (flag == 1)
			{
				SIZE_tri += 0.02f;
			}
			else
			{
				SIZE_tri -= 0.02f;
			}

			triShape1[0][0] = -0.15 + tx1 - SIZE_tri;
			triShape1[0][1] = -0.15 + ty1 - SIZE_tri;
			triShape1[1][0] = 0.15 + tx1 + SIZE_tri;
			triShape1[1][1] = -0.15 + ty1 - SIZE_tri;
			triShape1[2][0] = tx1;
			triShape1[2][1] = 0.3 + ty1 + SIZE_tri;

		}
		if (COUNT % 4 == 2)
		{
			
			triShape2[0][0] = 0;
			triShape2[0][1] = 0;
			triShape2[1][0] = 0;
			triShape2[1][1] = 0;
			triShape2[2][0] = 0;
			triShape2[2][1] = 0;

			glBindVertexArray(vao2); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape2, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
			if (x >= 500)
			{
				tx2 = (x - 500.0) / 500.0;
				if (y >= 400)
				{

					ty2 = -(y - 400.0) / 400.0;
				}
				else
				{
					ty2 = 1 - y / 500.0;

				}
			}
			else if (0 < x && x < 500)
			{
				tx2 = -1.0 + x / 500.0;
				if (y >= 400)
				{

					ty2 = -(y - 400.0) / 400.0;

				}
				else
				{
					ty2 = 1 - y / 400.0;


				}
			}
			if (flag == 1)
			{
				SIZE_tri += 0.02f;
			}
			else
			{
				SIZE_tri -= 0.02f;
			}


			triShape2[0][0] = -0.15 + tx2 - SIZE_tri;
			triShape2[0][1] = -0.15 + ty2 - SIZE_tri;
			triShape2[1][0] = 0.15 + tx2 + SIZE_tri;
			triShape2[1][1] = -0.15 + ty2 - SIZE_tri;
			triShape2[2][0] = tx2;
			triShape2[2][1] = 0.3 + ty2 + SIZE_tri;


		}
		if (COUNT % 4 == 3)
		{
			
			triShape3[0][0] = 0;
			triShape3[0][1] = 0;
			triShape3[1][0] = 0;
			triShape3[1][1] = 0;
			triShape3[2][0] = 0;
			triShape3[2][1] = 0;

			glBindVertexArray(vao3); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape3, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
			if (x >= 500)
			{
				tx3 = (x - 500.0) / 500.0;
				if (y >= 400)
				{

					ty3 = -(y - 400.0) / 400.0;
				}
				else
				{
					ty3 = 1 - y / 500.0;

				}
			}
			else if (0 < x && x < 500)
			{
				tx3 = -1.0 + x / 500.0;
				if (y >= 400)
				{

					ty3 = -(y - 400.0) / 400.0;

				}
				else
				{
					ty3 = 1 - y / 400.0;


				}
			}
			if (flag == 1)
			{
				SIZE_tri += 0.02f;
				flag = 0;
			}
			else
			{
				SIZE_tri -= 0.02f;
				flag = 1;
				
			}


			triShape3[0][0] = -0.15 + tx3 - SIZE_tri;
			triShape3[0][1] = -0.15 + ty3 - SIZE_tri;
			triShape3[1][0] = 0.15 + tx3 + SIZE_tri;
			triShape3[1][1] = -0.15 + ty3 - SIZE_tri;
			triShape3[2][0] = tx3;
			triShape3[2][1] = 0.3 + ty3 + SIZE_tri;


		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

		if (COUNT % 4 == 0)
		{
			glBindVertexArray(vao); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
		}
		if (COUNT % 4 == 1)
		{
			glBindVertexArray(vao1); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape1, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
		}
		if(COUNT % 4==2)
		{
			glBindVertexArray(vao2); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape2, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);

		}
		if (COUNT % 4 == 3)
		{
			glBindVertexArray(vao3); //--- VAO를 바인드하기
			glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape3, GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(GLfloat), triShape);

			glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(1);
		}
		
	}

	glutPostRedisplay();

}