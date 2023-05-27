// Reading Obj file
#define  _CRT_SECURE_NO_WARNINGS


#include "shader.h"
#include "objRead.h"

using namespace std;

int COUNT = 10;
int COUNT_D = 0;
GLuint g_window_w = 800;
GLuint g_window_h = 800;
int vertexindex = 0;

GLuint VAO[3];
GLuint VBO[3];
GLuint VBO1[3];
GLuint VBO2[3];

int polygon_mode = 1;

const int num_vertices = 3;
const int num_triangles = 1;


void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();

GLfloat test[36][3] = {
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{1,0,0},
	{1,0,0},
	{1,0,0},
	{1,0,0},
	{1,0,0},
	{1,0,0},
	{1,1,0},
	{1,1,0},
	{1,1,0},
	{1,1,0},
	{1,1,0},
	{1,1,0},
	{1,0,1},
	{1,0,1},
	{1,0,1},
	{1,0,1},
	{1,0,1},
	{1,0,1},
	{1,1,1},
	{1,1,1},
	{1,1,1},
	{1,1,1},
	{1,1,1},
	{1,1,1}
	


};

GLfloat tri_color[12][3] = {
	{0,0,1},
	{0,0,1},
	{0,0,1},
	{1,0,1},
	{1,0,1},
	{1,0,1},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{0,1,1},
	{0,1,1},
	{0,1,1},



};

GLfloat Line[4][3] = {
	{-2,0,0},{2,0,0},
	{0,-2,0},{0,2,0},
};

GLfloat Line_color[4][3] = {
	{1,0,0},{1,0,0},
	{0,1,0},{0,1,0},
};

//--- load obj related variabales
objRead objReader;
GLint Object = objReader.loadObj_normalize_center("test.obj");

objRead objReader1;
GLint Object1 = objReader1.loadObj_normalize_center1("tetrahedron.obj");

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
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(glm::vec3), &objReader1.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);
	
	cout << objReader1.outvertex.size() << endl;


	glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
	glBufferData(GL_ARRAY_BUFFER, 12 * 3 * sizeof(GLfloat), tri_color, GL_STATIC_DRAW);
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






	//glEnable(GL_DEPTH_TEST);

	//glEnable(GL_DEPTH_TEST);
}


void Display()	
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);

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

	S = glm::scale(S, glm::vec3(0.5, 0.5, 0.5));

	Rz = glm::rotate(Rz, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0));
	
	RR = Rz2 * Rz * S;

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));
	glUseProgram(s_program[0]);
	glBindVertexArray(VAO[0]);

	//std::vector<glm::vec3[20]>sttk;
	//glDrawArrays(GL_TRIANGLES, 0, Object);
	
	if (COUNT == 1)
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
	if (COUNT == 2)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);

	}
	if (COUNT == 3)
	{
		glDrawArrays(GL_TRIANGLES, 12, 6);

	}
	if (COUNT == 4)
	{
		glDrawArrays(GL_TRIANGLES, 18, 6);

	}
	if (COUNT == 5)
	{
		glDrawArrays(GL_TRIANGLES, 24, 6);

	}
	if (COUNT == 6)
	{
		glDrawArrays(GL_TRIANGLES, 30, 6);

	}





	if (COUNT_D == 1)
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_TRIANGLES, 12, 6);
	}
	if (COUNT_D == 2)
	{
		glDrawArrays(GL_TRIANGLES, 6, 6);
		glDrawArrays(GL_TRIANGLES, 18, 6);
	}
	if (COUNT_D == 3)
	{
		glDrawArrays(GL_TRIANGLES, 24, 6);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}



	glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, Object1);

	if (COUNT == 7)
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	if (COUNT == 8)
	{
		glDrawArrays(GL_TRIANGLES, 3, 3);
	}
	if (COUNT == 9)
	{
		glDrawArrays(GL_TRIANGLES, 6, 3);
	}
	if (COUNT == 0)
	{
		glDrawArrays(GL_TRIANGLES, 9, 3);
	}
	if (COUNT_D == 4)
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
	}
	if (COUNT_D == 5)
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 6, 3);
	}
	if (COUNT_D == 6)
	{
		glDrawArrays(GL_TRIANGLES, 9, 3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//glUseProgram(s_program[0]);

	glUseProgram(s_program[1]);
	glBindVertexArray(VAO[2]);
	glDrawArrays(GL_LINES, 0, 4);

	glUseProgram(s_program[0]);

	glutSwapBuffers();

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

	case'u':
		polygon_mode = 1;
		break;
	case'i':
		polygon_mode = 2;
		break;
	case'1':
		
		COUNT = 1;
		COUNT_D = 0;
		break;
	case'2':
		COUNT = 2;
		COUNT_D = 0;
		break;
	case'3':
		COUNT = 3;
		COUNT_D = 0;
		break;
	case'4':
		COUNT = 4;
		COUNT_D = 0;
		break;
	case'5':
		COUNT = 5;
		COUNT_D = 0;
		break;
	case'6':
		COUNT = 6;
		COUNT_D = 0;
		break;

	case'7':
		COUNT = 7;
		COUNT_D = 0;
		break;
	case'8':
		COUNT = 8;
		COUNT_D = 0;
		break;
	case'9':
		COUNT = 9;
		COUNT_D = 0;
		break;
	case'0':
		COUNT = 0;
		COUNT_D = 0;
		break;

	case'a':
		COUNT_D = 1;
		COUNT = 10;
		break;
	case'b':
		COUNT_D = 2;
		COUNT = 10;
		break;
	case'c':
		COUNT_D = 3;
		COUNT = 10;
		break;
	case'e':
		COUNT_D = 4;
		COUNT = 10;
		break;
	case'f':
		COUNT_D = 5;
		COUNT = 10;
		break;
	case'g':
		COUNT_D = 6;
		COUNT = 10;
		break;
	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}

	glutPostRedisplay();
}






