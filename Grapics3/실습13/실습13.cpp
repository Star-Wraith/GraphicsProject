// Reading Obj file
#define  _CRT_SECURE_NO_WARNINGS


#include "shader.h"
#include "objRead.h"
#include <conio.h>

#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80

using namespace std;

int COUNT = 10;
int COUNT_D = 0;
int hflag = 1;
int SH_COUNT = 2;
int XCOUNT = 0;
int YCOUNT = 0;
GLuint g_window_w = 800;
GLuint g_window_h = 800;
int vertexindex = 0;

GLfloat TX = 0.0f;
GLfloat TY = 0.0f;
GLfloat TZ = 0.0f;

GLuint VAO[3];
GLuint VBO[3];
GLuint VBO1[3];
GLuint VBO2[3];

GLfloat X = 5.0f;
GLfloat Y = -40.0f;

int polygon_mode = 1;

const int num_vertices = 3;
const int num_triangles = 1;


void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();

GLfloat test[36][3] = {
//
//	{0, 1, 1 },
//	{0, 1, 1 },
//	{0, 1, 1 },
//	{0, 1, 0},
//	{0, 1, 0},
//	{0, 1, 0},
//	{0.2,0.2,0.2},
//	{0.2,0.2,0.2},
//	{0.2,0.2,0.2},
//	{0,0,1},
//	{0,0,1},
//	{0,0,1},
//	{1,1,1},
//	{1,1,1},
//	{1,1,1},
//	{1,1,0},
//	{1,1,0},
//	{1,1,0},
//	{1,0,0},
//	{1,0,0},
//	{1,0,0},
//	{1,0,1},
//	{1,0,1},
//	{1,0,1},
//	{0, 1, 1 },
//{0, 1, 0},
//{0.2,0.2,0.2},
//{0,0,1},
//{1,1,1},
//{1,1,0},
//{1,0,0},
//{1,0,1},
//{1,1,1},
//{1,1,0},
//{1,0,0},
//{1,0,1},
	//{0, 1, 1 },
	//{0, 1, 0},
	//{0.2,0.2,0.2},
	//{0,0,1},
	//{1,1,1},
	//{1,1,0},
	//{1,0,0},
	//{1,0,1},
	//{0, 1, 1 },
	//{0, 1, 0},
	//{0.2,0.2,0.2},
	//{0,0,1},
	//{1,1,1},
	//{1,1,0},
	//{1,0,0},
	//{1,0,1},
	//{0, 1, 1 },
	//{0, 1, 0},
	//{0.2,0.2,0.2},
	//{0,0,1},
	//{1,1,1},
	//{1,1,0},
	//{1,0,0},
	//{1,0,1},
	//{0, 1, 1 },
	//{0, 1, 0},
	//{0.2,0.2,0.2},
	//{0,0,1},
	//{1,1,1},
	//{1,1,0},
	//{1,0,0},
	//{1,0,1},
	//{0, 1, 1 },
	//{0, 1, 0},
 //   {0.2,0.2,0.2},
	//{0,0,1}

	{0,0,1},
	{1,0,0},
	{0,1,0},
	{0,1,1},
	{1,1,0},
	{0.2,0.4,0.6},
	{0.5,1,0.5},
	{0,0.5,0.5},
	{0.3,0.7,0},
	{0.7,0.8,0.3},
	{0.4,0.8,0.1},
	{0.28,0.43,0.8},
	{0.2,0.6,0.1},
	{1,0.2,0.8},
	{0.1,0.15,0.9},
	{1,1,0.2},
	{0.3,0.3,0.3},
	{0.6,0.6,0.2},
	{0.2,0.4,0.6},
	{0.5,1,0.5},
	{0,0.5,0.5},
	{0.3,0.7,0},
	{0.7,0.8,0.3},
	{0.4,0.8,0.1},
	{1,1,1},
	{0.2,0.6,0.1},
	{1,0.2,0.8},
	{0.1,0.15,0.9},
	{1,1,0.2},
	{0.3,0.3,0.3},
	{0.6,0.6,0.2}
	
	//{0.2,0.2,0.2},
	//{1,0,0},
	//{1,1,0},
	//{0,1,0},
	//{0,0,1},
	//{1,0,1},
	//{1,1,1},
	//{0,1,1},
	//{0.2,0.2,0.2},
	//{1,0,0},
	//{1,1,0},
	//{0,1,0},
	//{0,0,1},
	//{1,0,1},
	//{1,0.6,1},
	//{0,1,1},
	//{0.2,0.2,0.2},
	//{1,0,0},
	//{0.2,0.2,0.2},
	//{1,0,0},
	//{1,1,0},
	//{0,1,0},
	//{0,0,1},
	//{1,0,1},
	//{1,1,1},
	//{0,1,1},
	//{0.2,0.2,0.2},
	//{1,0,0},
	//{1,1,0},
	//{0,1,0},
	//{0,0,1},
	//{1,0,1},
	//{1,0.6,1},
	//{0,1,1},
	//{0.2,0.2,0.2},
	//{1,0,0}



};

GLfloat tri_color[18][3] = {
	{0,0,2},
	{1,0,0},
	{0,1,0},
	{0,1,1},
	{1,1,0},
	{0.2,0.4,0.6},
	{0.5,1,0.5},
	{0,0.5,0.5},
	{0.3,0.7,0},
	{0.7,0.8,0.3},
	{0.4,0.8,0.1},
	{1,0.5,0.5},
	{0.2,0.6,0.1},
	{1,0.2,0.8},
	{0.1,0.15,0.9},
	{1,1,0.2},
	{0.3,0.3,0.3},
	{0.6,0.6,0.2},







};

GLfloat Line[4][3] = {
	{-3,0,0},{3,0,0},
	{0,-2,0},{0,2,0},
};



GLfloat Line_color[4][3] = {
	{1,0,0},{1,0,0},
	{0,1,0},{0,1,0},
};

//--- load obj related variabales
objRead objReader;
GLint Object = objReader.loadObj_normalize_center("test.obj");
//
objRead objReader1;
GLint Object1 = objReader1.loadObj_normalize_center1("pyramid.obj");

int main(int argc, char** argv)
{
	// create window using freeglut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_window_w, g_window_h);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Computer Graphics");

	//////////////////////////////////////////////////////////////////////////////////////
	//// initialize GLEW
	//////////////////////////////////////////////////////////////////////////////////////
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW OK\n";
	}

	//////////////////////////////////////////////////////////////////////////////////////
	//// Create shader program an register the shader
	//////////////////////////////////////////////////////////////////////////////////////

	GLuint vShader[4];
	GLuint fShader[4];

	vShader[0] = MakeVertexShader("vertex.glsl", 0);			// Sun
	fShader[0] = MakeFragmentShader("fragment.glsl", 0);
	vShader[1] = MakeVertexShader("vertex1.glsl", 1);			// Sun
	fShader[1] = MakeFragmentShader("fragment1.glsl", 1);
	cout << vShader[0] << endl;
	// shader Program
	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vShader[0]);
	glAttachShader(s_program[0], fShader[0]);
	glLinkProgram(s_program[0]);
	checkCompileErrors(s_program[0], "PROGRAM");


	s_program[1] = glCreateProgram();
	glAttachShader(s_program[1], vShader[1]);
	glAttachShader(s_program[1], fShader[1]);
	glLinkProgram(s_program[1]);
	InitBuffer();

	// callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// freeglut 윈도우 이벤트 처리 시작. 윈도우가 닫힐때까지 후한루프 실행.
	glutMainLoop();

	return 0;
}


void InitBuffer()
{
	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(3, VBO1);
	glGenBuffers(3, VBO2);

	cout << &objReader.outvertex << endl;

	// 2 triangles for quad floor
	glUseProgram(s_program[0]);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);


	//-------------------------------------------------------------------------
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader1.outvertex.size() * sizeof(glm::vec3), &objReader1.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);
	


	glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), tri_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	//-------------------------------------------------------------------------
	glUseProgram(s_program[1]);
	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), Line, GL_STATIC_DRAW);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), Line_color, GL_STATIC_DRAW);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(4);









}


void Display()	
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (SH_COUNT == 1)
	{
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
	else if(SH_COUNT == 0)
	{
		//glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
		

	if (polygon_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (polygon_mode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//*************************************************************************
	// Drawing circle


	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Rz2 = glm::mat4(1.0f);
	glm::mat4 RR = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(0.5, 0.5, 0.5));

	model = glm::translate(model, glm::vec3(TX, TY, TZ));

	Rz = glm::rotate(Rz, glm::radians(X), glm::vec3(1.0, 0.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
	
	RR = model *Rz2 * Rz * S;



	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));
	//glBindVertexArray(VAO[0]);

	//std::vector<glm::vec3[20]>sttk;
	if (COUNT == 1)
	{
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, Object);
	}




	//glBindVertexArray(VAO[1]);
	if (COUNT == 2)
	{
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, Object1);

	}
	glUseProgram(s_program[1]);

	glBindVertexArray(VAO[2]);
	
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);

	glUseProgram(s_program[0]);


	glutSwapBuffers();

}
void xmove(int index)
{
	if (XCOUNT == 1)
	{
		X += 5.0;

	}
	else if (XCOUNT == 2)
	{
		X -= 5.0;
	}






	glutPostRedisplay();
	glutTimerFunc(100, xmove, 1);
}

void ymove(int index)
{
	if (YCOUNT == 1)
	{
		Y += 5.0;

	}
	else if (YCOUNT == 2)
	{
		Y -= 5.0;
	}






	glutPostRedisplay();
	glutTimerFunc(100, ymove, 1);
}
void Reshape(int w, int h)
{
	g_window_w = w;
	g_window_h = h;
	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{


		switch (key)
		{
			

		case'c':

			COUNT = 1;
			break;
		case'p':
			COUNT = 2;
			break;

		case'h':
			if (hflag == 1)
			{
				SH_COUNT = 1;
				hflag = 0;
			}
			else
			{
				SH_COUNT = 0;
				hflag = 1;
			}
			break;
		case'x':
			if (XCOUNT == 0)
			{
				glutTimerFunc(100, xmove, 1);
			}
			XCOUNT = 1;
			break;

		case'X':
			if (XCOUNT == 0)
			{
				glutTimerFunc(100, xmove, 1);
			}
			XCOUNT = 2;
			break;
		case'y':
			if (YCOUNT == 0)
			{
				glutTimerFunc(100, ymove, 1);
			}
			YCOUNT = 1;
			break;

		case'Y':
			if (YCOUNT == 0)
			{
				glutTimerFunc(100, ymove, 1);
			}
			YCOUNT = 2;
			break;
		case'q':
			glutLeaveMainLoop();
			break;
		case'w':
			polygon_mode = 1;
			break;

		case'W':
			polygon_mode = 2;
			break;
		case '4':
			TX -= 0.5;
			break;
		case '5':
			TY -= 0.5;
			break;
		case '6':
			TX += 0.5;
			break;
		case '8':
			TY += 0.5;
			break;

		case'S':
			COUNT = 0;
			hflag = 1;
			SH_COUNT = 0;
			XCOUNT = 10;
			YCOUNT = 10;
			polygon_mode = 1;
			TX = 0;
			TY = 0;

			X = 5.0f;
			Y = -40.0f;
			break;
		default:
			break;
		}

	glutPostRedisplay();
}






