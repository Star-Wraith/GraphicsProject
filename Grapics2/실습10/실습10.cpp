#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

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
GLchar* vertexsource, * fragmentsource; //--- �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; //--- ���̴� ��ü
GLuint s_program;
void InitBuffer();
void InitShader();

GLvoid Keyboard(unsigned char key, int x, int y);
void make_vertexShader();
void make_fragmentShader();
void LT_conversion(int value);
void TR_conversion(int value);
void RP_conversion(int value);
void PV_conversion(int value);




GLfloat triShape[3][3] = { //---���� ��
 { -0.7,0.3,0 },{-0.3,0.7,0 },{-0.3,0.7,0} };
GLfloat colors[3][3] = { //--- �ﰢ�� ������ ����
	{0,0,0},{0,0,0},{0,0,0} };

GLfloat TR_shape[6][3] = { //---���� ��
{ 0.3,0.3,0 },{0.7,0.3,0},{0.5,0.7,0},
	{0.5,0.7,0},{0.7,0.3,0},{0.5,0.7,0} };
GLfloat colors1[6][3] = { //--- �ﰢ�� ������ ����
	{1,1, 0 },{1,1, 0 },{1,1, 0},
	{1,1, 0 },{1,1, 0 },{1,1, 0} };

GLfloat RP_shape[9][3] = { //---���� ��
	{-0.7,-0.8,0},{-0.3,-0.8,0},{-0.7,-0.4,0},
	{-0.3,-0.8,0},{-0.3,-0.4,0},{-0.7,-0.4,0},
	{-0.3,-0.4,0},{-0.5,-0.4,0},{-0.7,-0.4,0} };
GLfloat colors2[9][3] = { //--- �ﰢ�� ������ ����
	{0.67,1, 0.18 },{0.67,1, 0.18},{0.67,1, 0.18},
	{0.67,1, 0.18 },{0.67,1, 0.18},{0.67,1, 0.18},
	{0.67,1, 0.18 },{0.67,1, 0.18},{0.67,1, 0.18} };

GLfloat PV_shape[9][3] = { //---���� ��
	{0.3,-0.8,0},{0.5,-0.3,0},{0.2,-0.5,0},
	{0.3,-0.8,0},{0.7,-0.8,0},{0.5,-0.3,0},
	{0.7,-0.8,0},{0.8,-0.5,0},{0.5,-0.3,0} };

GLfloat colors3[9][3] = { //--- �ﰢ�� ������ ����
	{0.7,0, 0.0 },{0.7,0, 0.0},{0.7,0, 0.0},
	{0.7,0, 0.0 },{0.7,0, 0.0},{0.7,0, 0.0},
	{0.7,0, 0.0 },{0.7,0, 0.0},{0.7,0, 0.0} };



int COUNT = 1;
int TR_COUNT = 1;
int RP_COUNT = 1;
int PV_COUNT = 1;
GLfloat XY_LINE[4][3]
{ {-1,0,0},{1,0,0},{0,-1,0} ,{0,1,0}
};
GLfloat colors_Line[4][3] = { //--- �ﰢ�� ������ ����
	{0,0, 1 },{0,0, 1 },{0,0, 1 },{0,0, 1 } };
GLuint vao, vbo[2];
GLuint vao1, vbo1[2];
GLuint vao2, vbo2[2];
GLuint vao3, vbo3[2];
GLuint vao4, vbo4[2];

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


void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{

	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();

	InitBuffer();

	glutDisplayFunc(drawScene);

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����


	glutMainLoop();
}

void make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexshader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShader()
{

	fragmentsource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentshader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
		return;
	}
}



void InitBuffer()
{






	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�




	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao1); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao1); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo1); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�


	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), TR_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	////----------------------------------

	glGenVertexArrays(1, &vao2); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao2); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo2); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�


	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), RP_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	////----------------------------------

	glGenVertexArrays(1, &vao3); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao3); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo3); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�


	glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), PV_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &vao4); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao4); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo4); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�




	glBindBuffer(GL_ARRAY_BUFFER, vbo4[0]);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), XY_LINE, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo4[1]);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors_Line, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);


}

void InitShader()
{
	make_vertexShader(); //--- ���ؽ� ���̴� �����
	make_fragmentShader(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);
	//checkCompileErrors(s_program, "PROGRAM");
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);


	//--- Shader Program ����ϱ�
	glUseProgram(s_program);

}

GLvoid drawScene()
{


	glClearColor(rColor, gColor, bColor, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(s_program);
	//--- ����� VAO �ҷ�����

	glBindVertexArray(vao);
	//--- �ﰢ�� �׸���
	
	if (triShape[1][1] == triShape[2][1])
	{

		glDrawArrays(GL_LINES, 0, 3);
	}
	else
	{
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glBindVertexArray(vao1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(vao2);
	glDrawArrays(GL_TRIANGLES, 0, 9);

	glBindVertexArray(vao3);
	if (PV_shape[1][1] <= -0.49)
	{
		glDrawArrays(GL_POINTS, 0, 9);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 9);
	}
	


	glBindVertexArray(vao4);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 4);



	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�




}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}





GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'a':
		glutTimerFunc(100, LT_conversion, 1);
		break;
	case's':

		glutTimerFunc(100, TR_conversion, 1);

		break;
	case'd':
		glutTimerFunc(100, RP_conversion, 1);

		break;
	case'f':
		glutTimerFunc(100, PV_conversion, 1);
		break;


	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}



	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

void LT_conversion(int value)
{
	if (COUNT == 1)
	{
		if (triShape[1][0] >= -0.49)
		{
			triShape[1][0] -= 0.01;
			triShape[2][1] -= 0.02;

			if (triShape[1][0] <= -0.49)
			{
				COUNT = 0;
			}
		}
	}
	else
	{
		if (triShape[1][0] <= -0.31)
		{
			triShape[1][0] += 0.01;
			triShape[2][1] += 0.02;

			if (triShape[1][0] >= -0.31)
			{
				COUNT = 1;
			}
		}
	}
	if (triShape[1][1] != triShape[2][1])
	{
		colors[0][2] = 1;
		colors[1][2] = 1;
		colors[2][2] = 1;
	}
	else
	{
		colors[0][2] = 0;
		colors[1][2] = 0;
		colors[2][2] = 0;
	}
	
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glutPostRedisplay();
	glutTimerFunc(100, LT_conversion, 1);
}


void TR_conversion(int value)
{
	if (TR_COUNT == 1)
	{
		if (TR_shape[2][0] >= 0.31)
		{
			TR_shape[2][0] -= 0.01;
			TR_shape[3][0] -= 0.01;
			TR_shape[5][0] += 0.01;
			if (TR_shape[2][0] <= 0.31)
			{
				TR_COUNT = 0;
			}
		}
	}
	else
	{
		if (TR_shape[2][0] <= 0.49)
		{
			TR_shape[2][0] += 0.01;
			TR_shape[3][0] += 0.01;
			TR_shape[5][0] -= 0.01;
			if (TR_shape[2][0] >= 0.49)
			{
				TR_COUNT = 1;
			}
		}
	}



	glBindVertexArray(vao1); //--- VAO�� ���ε��ϱ�
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), TR_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo1[1]);

	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors1, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	glutPostRedisplay();
	glutTimerFunc(100, TR_conversion, 1);
}

void RP_conversion(int value)
{

	//GLfloat RP_shape[9][3] = { //---���� ��
	//{-0.7,-0.8,0},{-0.3,-0.8,0},{-0.7,-0.4,0},
	//{-0.3,-0.8,0},{-0.3,-0.4,0},{-0.7,-0.4,0},
	//{-0.3,-0.4,0},{-0.5,-0.4,0},{-0.7,-0.4,0} };
	if (RP_COUNT == 1)
	{
		if (RP_shape[2][0] >= -0.79)
		{
			RP_shape[2][0] -= 0.01;
			RP_shape[2][1] -= 0.01;
			RP_shape[4][0] += 0.01;
			RP_shape[4][1] -= 0.01;
			RP_shape[5][0] -= 0.01;
			RP_shape[5][1] -= 0.01;

			RP_shape[6][0] += 0.01;
			RP_shape[6][1] -= 0.01;
			RP_shape[7][1] += 0.005;
			RP_shape[8][0] -= 0.01;
			RP_shape[8][1] -= 0.01;
			if (RP_shape[2][0] <= -0.79)
			{
				RP_COUNT = 0;
			}
		}
	}
	else
	{
		RP_shape[2][0] += 0.01;
		RP_shape[2][1] += 0.01;
		RP_shape[4][0] -= 0.01;
		RP_shape[4][1] += 0.01;
		RP_shape[5][0] += 0.01;
		RP_shape[5][1] += 0.01;

		RP_shape[6][0] -= 0.01;
		RP_shape[6][1] += 0.01;
		RP_shape[7][1] -= 0.005;
		RP_shape[8][0] += 0.01;
		RP_shape[8][1] += 0.01;

		if (RP_shape[2][0] >= -0.71)
		{
			RP_COUNT = 1;
		}
	}



	glBindVertexArray(vao2); //--- VAO�� ���ε��ϱ�


	glBindBuffer(GL_ARRAY_BUFFER, vbo2[0]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), RP_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo2[1]);

	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), colors2, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glutPostRedisplay();
	glutTimerFunc(100, RP_conversion, 1);
}

void PV_conversion(int value)
{

	//GLfloat PV_shape[9][3] = { //---���� ��
	//{0.3,-0.8,0},{0.5,-0.3,0},{0.2,-0.5,0},
	//{0.3,-0.8,0},{0.7,-0.8,0},{0.5,-0.3,0},
	//{0.7,-0.8,0},{0.8,-0.5,0},{0.5,-0.3,0} };
	
	if (PV_COUNT == 1)
	{
		if (PV_shape[1][1] >= -0.49)
		{
			PV_shape[1][1] -= 0.01;
			PV_shape[0][0] += 0.01;
			PV_shape[0][1] += 0.015;
			PV_shape[2][0] += 0.015;
			
			PV_shape[3][0] += 0.01;
			PV_shape[3][1] += 0.015;
			PV_shape[4][0] -= 0.01;
			PV_shape[4][1] += 0.015;
			PV_shape[5][1] -= 0.01;

			PV_shape[6][0] -= 0.01;
			PV_shape[6][1] += 0.015;
			PV_shape[7][0] -= 0.015;
			PV_shape[8][1] -= 0.01;
			if (PV_shape[1][1] <= -0.49)
			{
				PV_COUNT = 0;
			}
		}
	}
	else
	{
		if (PV_shape[1][1] <= -0.31)
		{
			PV_shape[1][1] += 0.01;
			PV_shape[0][0] -= 0.01;
			PV_shape[0][1] -= 0.015;
			PV_shape[2][0] -= 0.015;

			PV_shape[3][0] -= 0.01;
			PV_shape[3][1] -= 0.015;
			PV_shape[4][0] += 0.01;
			PV_shape[4][1] -= 0.015;
			PV_shape[5][1] += 0.01;

			PV_shape[6][0] += 0.01;
			PV_shape[6][1] -= 0.015;
			PV_shape[7][0] += 0.015;
			PV_shape[8][1] += 0.01;
			if (PV_shape[1][1] >= -0.31)
			{
				PV_COUNT = 1;
			}
		}
	}
	if (PV_shape[1][1] <=-0.49)
	{
		colors3[0][0] = 0.0;
		colors3[1][0] = 0.0;
		colors3[2][0] = 0.0;
		colors3[3][0] = 0.0;
		colors3[4][0] = 0.0;
		colors3[5][0] = 0.0;
		colors3[6][0] = 0.0;
		colors3[7][0] = 0.0;
		colors3[8][0] = 0.0;
	}
	else
	{
		colors3[0][0] = 0.7;
		colors3[1][0] = 0.7;
		colors3[2][0] = 0.7;
		colors3[3][0] = 0.7;
		colors3[4][0] = 0.7;
		colors3[5][0] = 0.7;
		colors3[6][0] = 0.7;
		colors3[7][0] = 0.7;
		colors3[8][0] = 0.7;
	}

	
	glBindVertexArray(vao3); //--- VAO�� ���ε��ϱ�


	glBindBuffer(GL_ARRAY_BUFFER, vbo3[0]);
	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), PV_shape, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//----------------------------------
	glBindBuffer(GL_ARRAY_BUFFER, vbo3[1]);

	glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(GLfloat), colors3, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);



	glutPostRedisplay();
	glutTimerFunc(100, PV_conversion, 1);
}