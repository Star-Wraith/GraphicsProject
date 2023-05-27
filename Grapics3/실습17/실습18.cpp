// Reading Obj file
#define  _CRT_SECURE_NO_WARNINGS


#include "shader.h"
#include "objRead.h"
#include <conio.h>

int ALLSTOP = 1;

using namespace std;
int update = 0;
int COUNT = 0;
int COUNT1 = 0;
int COUNT_D = 0;
int hflag = 1;
int SH_COUNT = 2;
int XCOUNT = 0;
int YCOUNT = 0;
int ZCOUNT = 0;
int XCOUNT1 = 0;
int YCOUNT1 = 0;
int XCOUNT2 = 0;
int YCOUNT2 = 0;
int CFlag = 1;
GLuint g_window_w = 1280;
GLuint g_window_h = 960;
int vertexindex = 0;

int left_right_up = 1;
int FR = 0;
GLfloat FR_minus = -10.0f;
GLfloat TX = 0.0f;
GLfloat TY = 0.0f;
GLfloat TZ = 0.0f;

GLfloat TX1 = -0.5f;
GLfloat TY1 = 0.2f;
GLfloat TZ1 = 0.0f;

GLuint VAO[10];
GLuint VBO[3];
GLuint VBO1[3];
GLuint VBO2[3];
GLuint VBO3[3];
GLuint VBO4[3];
GLuint VBO5[3];
GLuint VBO6[3];
GLuint VBO7[3];
GLuint VBO8[3];
GLuint VBO9[3];

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat X1 = 0.0f;
GLfloat Y1 = 0.0f;
GLfloat Y2 = 0.0f;

GLfloat Y_L = 0.0f;
GLfloat Y_L1 = 0.0f;

int polygon_mode = 1;

const int num_vertices = 3;
const int num_triangles = 1;


void Display();
void Display_Camera();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();

int C_Yflag = 1;

GLfloat testCUBE[36][3] = {


	//{1,1,-1},
	//{1,-1,-1},
	//{-1,-1,-1},
	//{1,1,-1},
	//{-1,-1,-1},
	//{-1,1,-1},
	//{1,-1,-1},
	//{1,-1,1},
	//{-1,-1,1},
	//{1,-1,-1},
	//{-1,-1,1},
	//{-1,-1,-1},
	//{-1,-1,1},
	//{-1,1,1},
	//{-1,1,-1},
	//{-1,-1,1},
	//{-1,1,-1},
	//{-1,-1,-1},
	//{1,-1,-1},
	//{1,1,-1},
	//{1,-1,1},
	//{1,1,-1},
	//{1,1,1},
	//{1,-1,1},
	//{1,-1,1},
	//{1,1,1},
	//{-1,-1,1},
	//{1,1,1},
	//{-1,1,1},
	//{-1,-1,1},
	//{1,1,-1},
	//{-1,1,-1},
	//{1,1,1},
	//{-1,1,-1},
	//{-1,1,1},
	//{1,1,1},
	{1,1,-1},
	{1,0,-1},
	{-1,0,-1},
	{1,1,-1},
	{-1,0,-1},
	{-1,1,-1},
	{1,0,-1},
	{1,0,1},
	{-1,0,1},
	{1,0,-1},
	{-1,0,1},
	{-1,0,-1},
	{-1,0,1},
	{-1,1,1},
	{-1,1,-1},
	{-1,0,1},
	{-1,1,-1},
	{-1,0,-1},
	{1,0,-1},
	{1,1,-1},
	{1,0,1},
	{1,1,-1},
	{1,1,1},
	{1,0,1},
	{1,0,1},
	{1,1,1},
	{-1,0,1},
	{1,1,1},
	{-1,1,1},
	{-1,0,1},
	{1,1,-1},
	{-1,1,-1},
	{1,1,1},
	{-1,1,-1},
	{-1,1,1},
	{1,1,1},






};

GLfloat testCUBECOPY[36][3] = {


	//{1,1,-1},
	//{1,-1,-1},
	//{-1,-1,-1},
	//{1,1,-1},
	//{-1,-1,-1},
	//{-1,1,-1},
	//{1,-1,-1},
	//{1,-1,1},
	//{-1,-1,1},
	//{1,-1,-1},
	//{-1,-1,1},
	//{-1,-1,-1},
	//{-1,-1,1},
	//{-1,1,1},
	//{-1,1,-1},
	//{-1,-1,1},
	//{-1,1,-1},
	//{-1,-1,-1},
	//{1,-1,-1},
	//{1,1,-1},
	//{1,-1,1},
	//{1,1,-1},
	//{1,1,1},
	//{1,-1,1},
	//{1,-1,1},
	//{1,1,1},
	//{-1,-1,1},
	//{1,1,1},
	//{-1,1,1},
	//{-1,-1,1},
	//{1,1,-1},
	//{-1,1,-1},
	//{1,1,1},
	//{-1,1,-1},
	//{-1,1,1},
	//{1,1,1},
	{1,1,-1},
	{1,0,-1},
	{-1,0,-1},
	{1,1,-1},
	{-1,0,-1},
	{-1,1,-1},
	{1,0,-1},
	{1,0,1},
	{-1,0,1},
	{1,0,-1},
	{-1,0,1},
	{-1,0,-1},
	{-1,0,1},
	{-1,1,1},
	{-1,1,-1},
	{-1,0,1},
	{-1,1,-1},
	{-1,0,-1},
	{1,0,-1},
	{1,1,-1},
	{1,0,1},
	{1,1,-1},
	{1,1,1},
	{1,0,1},
	{1,0,1},
	{1,1,1},
	{-1,0,1},
	{1,1,1},
	{-1,1,1},
	{-1,0,1},
	{1,1,-1},
	{-1,1,-1},
	{1,1,1},
	{-1,1,-1},
	{-1,1,1},
	{1,1,1},






};
GLfloat CUBEsmall[36][3] = {



	{0.5,1.5,-0.5},
	{0.5,1,-0.5},
	{-0.5,1,-0.5},
	{0.5,1.5,-0.5},
	{-0.5,1,-0.5},
	{-0.5,1.5,-0.5},
	{0.5,1,-0.5},
	{0.5,1,0.5},
	{-0.5,1,0.5},
	{0.5,1,-0.5},
	{-0.5,1,0.5},
	{-0.5,1,-0.5},
	{-0.5,1,0.5},
	{-0.5,1.5,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1,-0.5},
	{0.5,1,-0.5},
	{0.5,1.5,-0.5},
	{0.5,1,0.5},
	{0.5,1.5,-0.5},
	{0.5,1.5,0.5},
	{0.5,1,0.5},
	{0.5,1,0.5},
	{0.5,1.5,0.5},
	{-0.5,1,0.5},
	{0.5,1.5,0.5},
	{-0.5,1.5,0.5},
	{-0.5,1,0.5},
	{0.5,1.5,-0.5},
	{-0.5,1.5,-0.5},
	{0.5,1.5,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1.5,0.5},
	{0.5,1.5,0.5},






};

GLfloat CUBEsmallCOPY[36][3] = {



	{0.5,1.5,-0.5},
	{0.5,1,-0.5},
	{-0.5,1,-0.5},
	{0.5,1.5,-0.5},
	{-0.5,1,-0.5},
	{-0.5,1.5,-0.5},
	{0.5,1,-0.5},
	{0.5,1,0.5},
	{-0.5,1,0.5},
	{0.5,1,-0.5},
	{-0.5,1,0.5},
	{-0.5,1,-0.5},
	{-0.5,1,0.5},
	{-0.5,1.5,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1,-0.5},
	{0.5,1,-0.5},
	{0.5,1.5,-0.5},
	{0.5,1,0.5},
	{0.5,1.5,-0.5},
	{0.5,1.5,0.5},
	{0.5,1,0.5},
	{0.5,1,0.5},
	{0.5,1.5,0.5},
	{-0.5,1,0.5},
	{0.5,1.5,0.5},
	{-0.5,1.5,0.5},
	{-0.5,1,0.5},
	{0.5,1.5,-0.5},
	{-0.5,1.5,-0.5},
	{0.5,1.5,0.5},
	{-0.5,1.5,-0.5},
	{-0.5,1.5,0.5},
	{0.5,1.5,0.5},






};
GLfloat CUBECL[36][3] = {



	{-0.2,2.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.2,2.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.4,2.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.2,1.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,1.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,1.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,2.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.2,2.5,-0.1},
	{-0.2,1.5,0.1},
	{-0.2,2.5,-0.1},
	{-0.2,2.5,0.1},
	{-0.2,1.5,0.1},
	{-0.2,1.5,0.1},
	{-0.2,2.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,2.5,0.1},
	{-0.4,2.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,2.5,-0.1},
	{-0.4,2.5,-0.1},
	{-0.2,2.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,2.5,0.1},
	{-0.2,2.5,0.1},






};

GLfloat CUBECLCOPY[36][3] = {



	{-0.2,2.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.2,2.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.4,2.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.2,1.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,1.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,1.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,2.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,1.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,1.5,-0.1},
	{-0.2,1.5,-0.1},
	{-0.2,2.5,-0.1},
	{-0.2,1.5,0.1},
	{-0.2,2.5,-0.1},
	{-0.2,2.5,0.1},
	{-0.2,1.5,0.1},
	{-0.2,1.5,0.1},
	{-0.2,2.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,2.5,0.1},
	{-0.4,2.5,0.1},
	{-0.4,1.5,0.1},
	{-0.2,2.5,-0.1},
	{-0.4,2.5,-0.1},
	{-0.2,2.5,0.1},
	{-0.4,2.5,-0.1},
	{-0.4,2.5,0.1},
	{-0.2,2.5,0.1},






};
GLfloat CUBECR[36][3] = {



	{0.2,2.5,-0.1},
	{0.2,1.5,-0.1},
	{0.4,1.5,-0.1},
	{0.2,2.5,-0.1},
	{0.4,1.5,-0.1},
	{0.4,2.5,-0.1},
	{0.2,1.5,-0.1},
	{0.2,1.5,0.1},
	{0.4,1.5,0.1},
	{0.2,1.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,1.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,2.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,1.5,-0.1},
	{0.2,1.5,-0.1},
	{0.2,2.5,-0.1},
	{0.2,1.5,0.1},
	{0.2,2.5,-0.1},
	{0.2,2.5,0.1},
	{0.2,1.5,0.1},
	{0.2,1.5,0.1},
	{0.2,2.5,0.1},
	{0.4,1.5,0.1},
	{0.2,2.5,0.1},
	{0.4,2.5,0.1},
	{0.4,1.5,0.1},
	{0.2,2.5,-0.1},
	{0.4,2.5,-0.1},
	{0.2,2.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,2.5,0.1},
	{0.2,2.5,0.1},






};

GLfloat CUBECRCOPY[36][3] = {



	{0.2,2.5,-0.1},
	{0.2,1.5,-0.1},
	{0.4,1.5,-0.1},
	{0.2,2.5,-0.1},
	{0.4,1.5,-0.1},
	{0.4,2.5,-0.1},
	{0.2,1.5,-0.1},
	{0.2,1.5,0.1},
	{0.4,1.5,0.1},
	{0.2,1.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,1.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,2.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,1.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,1.5,-0.1},
	{0.2,1.5,-0.1},
	{0.2,2.5,-0.1},
	{0.2,1.5,0.1},
	{0.2,2.5,-0.1},
	{0.2,2.5,0.1},
	{0.2,1.5,0.1},
	{0.2,1.5,0.1},
	{0.2,2.5,0.1},
	{0.4,1.5,0.1},
	{0.2,2.5,0.1},
	{0.4,2.5,0.1},
	{0.4,1.5,0.1},
	{0.2,2.5,-0.1},
	{0.4,2.5,-0.1},
	{0.2,2.5,0.1},
	{0.4,2.5,-0.1},
	{0.4,2.5,0.1},
	{0.2,2.5,0.1},






};
GLfloat test[36][3] = {


	{0,0,1}, //5
	{1,0,0}, //1
	{0,1,0}, //4
	{0,0,1}, //5
	{0,1,0}, //4
	{1,0.4,0}, //8
	{1,0,0},  //1
	{1,1,0},  //2
	{0.62,0.12,0.94},  //3
	{1,0,0},//1
	{0.62,0.12,0.94}, //3
	{0,1,0}, //4
	{0.62,0.12,0.94}, //3
	{1,0.75,0.8}, //7
	{1,0.4,0},//8
	{0.62,0.12,0.94}, //3
	{1,0.4,0},//8
	{0.62,0.12,0.94},//3
	{1,0,0},//1
	{0,0,1},//5
	{1,1,0},  //2
	{0,0,1},//5
	{0.5,0.8,0.9}, //6
	{0,1,0}, //4
	{0,0.5,0.5}, //2
	{0.5,0.8,0.9}, //6
	{0.62,0.12,0.94}, //3
	{0.5,0.8,0.9},//6
	{1,0.75,0.8},//7

	{1,1,0},  //2
	{0,0,1},//5
	{1,0.4,0},//8
	{0.5,0.8,0.9},//6
	{1,0.4,0},//8
	{1,0.75,0.8},//7
	{0.5,1,0.5},//6
	




};

GLfloat FLOOR[6][3] = {
	{-5,0,5},{5,0,-5},{-5,0,-5},
	{-5,0,5},{5,0,5},{5,0,-5},
};
GLfloat F_color[6][3] = {
	{0,1,0},{1,0,0},{1,1,0},
	{0,1,0},{0,0,1},{1,0,0},
};
GLfloat Line[6][3] = {
	{-1,0,0},{1,0,0},
	{0,-0.8,0},{0,0.8,0},
	{0,0,-1},{0,0,1},
};



GLfloat Line_color[6][3] = {
	{0,1,0},{0,1,0},
	{1,0,0},{1,0,0},
	{0,0,1},{0,0,1},
};

//--- load obj related variabales
//objRead objReader; //CUBE
//GLint Object = objReader.loadObj_normalize_center("test.obj");
////
//objRead objReader2; //SPHERE
//GLint Object2 = objReader2.loadObj_normalize_center2("test1.obj");

//objRead objReader3; //SPHERE2
//GLint Object3 = objReader3.loadObj_normalize_center3("sphere1.obj");


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

	GLuint vShader[10];
	GLuint fShader[10];

	vShader[0] = MakeVertexShader("vertex.glsl", 0);			// Sun
	fShader[0] = MakeFragmentShader("fragment.glsl", 0);
	vShader[1] = MakeVertexShader("vertex1.glsl", 1);			// Sun
	fShader[1] = MakeFragmentShader("fragment1.glsl", 1);
	vShader[2] = MakeVertexShader("vertex2.glsl", 2);			// Sun
	fShader[2] = MakeFragmentShader("fragment2.glsl", 2);

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

	s_program[2] = glCreateProgram();
	glAttachShader(s_program[2], vShader[2]);
	glAttachShader(s_program[2], fShader[2]);
	glLinkProgram(s_program[2]);
	checkCompileErrors(s_program[2], "PROGRAM");
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
	glGenVertexArrays(10, VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(3, VBO1);
	glGenBuffers(3, VBO2);
	glGenBuffers(3, VBO3);
	glGenBuffers(3, VBO4);
	glGenBuffers(3, VBO5);



	// 2 triangles for quad floor
	glUseProgram(s_program[0]);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), testCUBE, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBEsmall, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECR, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glUseProgram(s_program[1]);
	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Line, GL_STATIC_DRAW);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Line_color, GL_STATIC_DRAW);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(4);

	glUseProgram(s_program[2]);
	glBindVertexArray(VAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), FLOOR, GL_STATIC_DRAW);

	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), F_color, GL_STATIC_DRAW);

	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(6);
	//-------------------------------------------------------------------------------








}

void Display()	
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glFrontFace(GL_CCW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	// Drawing CUBE


	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Rz2 = glm::mat4(1.0f);
	glm::mat4 RR = glm::mat4(1.0f);
	glm::mat4 RR1 = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 S1 = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(0.2, 0.2, 0.2));
	S1 = glm::scale(S1, glm::vec3(0.4, 0.4, 0.4));
	model = glm::translate(model, glm::vec3(TX, TY, TZ));

	Rz = glm::rotate(Rz, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(X), glm::vec3(1.0, 0.0, 0.0));
	



		RR = model * Rz2 * Rz * S;
		RR1 = Rz2 * Rz * S1;

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));

	glUseProgram(s_program[2]);
	unsigned int modelLocation1 = glGetUniformLocation(s_program[2], "modelTransform2");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(RR1));


	//------------------------------------------------------------------------------
	//선분 회전시켜놓기
	glm::mat4 R_Line = glm::mat4(1.0f);
	glm::mat4 R_Line2 = glm::mat4(1.0f);
	glm::mat4 S_Line = glm::mat4(1.0f);
	glm::mat4 RO = glm::mat4(1.0f);
	glUseProgram(s_program[1]);
	S_Line = glm::scale(S_Line, glm::vec3(0.8, 0.8, 0.8));
	R_Line = glm::rotate(R_Line, glm::radians(Y_L), glm::vec3(0.0, 1.0, 0.0));
	R_Line2 = glm::rotate(R_Line2, glm::radians(Y_L1), glm::vec3(1.0, 0.0, 0.0));

		RO = R_Line2 * R_Line * S_Line;



	unsigned int lineLocation = glGetUniformLocation(s_program[1], "modelTransform1");
	glUniformMatrix4fv(lineLocation, 1, GL_FALSE, glm::value_ptr(RO));



	Display_Camera();
	//glutSwapBuffers();

}
GLfloat pPro = -2;
GLfloat pPro1 = 2;
int PRO_Flag = 1;
GLfloat xPos = 0.0f;
GLfloat yPos = 0.1f;
GLfloat zPos = 0.1f;
GLfloat radius = 0.0f;
GLfloat xVis = 0.0f;
GLfloat yVis = 0.0f;
GLfloat zVis = 0.0f;
GLfloat CY = 0;
GLfloat CameraY = 0.0f;
void Display_Camera()
{

	glUseProgram(s_program[0]);
	glm::vec3 cameraPos = glm::vec3(xPos, yPos, zPos); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(xVis, yVis, zVis); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);


	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);



	glm::mat4 projection = glm::mat4(1.0f);
	if (PRO_Flag == 0)
	{
		projection = glm::ortho(pPro, pPro1, pPro, pPro1, pPro, pPro1);
	}
	else if (PRO_Flag == 1)
	{
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));


	}


	unsigned int projectionLocation = glGetUniformLocation(s_program[0], "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	//glBindVertexArray(VAO[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(VAO[3]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(VAO[4]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(s_program[2]);

	unsigned int viewLocation2 = glGetUniformLocation(s_program[2], "viewTransform2"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, &view[0][0]);

	unsigned int projectionLocation2 = glGetUniformLocation(s_program[2], "projectionTransform2"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection[0][0]);

	glBindVertexArray(VAO[5]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glm::vec3 cameraPos1 = glm::vec3(xPos, yPos, zPos ); //--- 카메라 위치
	//glm::vec3 cameraDirection1 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	//glm::vec3 cameraUp1 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	//glm::mat4 view1 = glm::mat4(1.0f);

	//view1 = glm::lookAt(cameraPos1, cameraDirection1, cameraUp1);

	glUseProgram(s_program[1]);
	unsigned int viewLocation1 = glGetUniformLocation(s_program[1], "viewTransform1"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation1, 1, GL_FALSE, &view[0][0]);

	unsigned int projectionLocation1 = glGetUniformLocation(s_program[1], "projectionTransform1"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation1, 1, GL_FALSE, &projection[0][0]);
	glBindVertexArray(VAO[2]);

	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glUseProgram(s_program[0]);
	if (COUNT == 1)
	{
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO[4]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glutSwapBuffers();

}
int Xflag = 1;
int Xflag1 = 1;
void xmove(int index)
{
	if (ALLSTOP == 1)
	{
		if (XCOUNT == 1)
		{
			TX += 0.01;

			//radius += 0.1f;
			//xVis = sin(radius);
			//zVis = cos(radius);
		}
		else if (XCOUNT == 2)
		{
			TX -= 0.01;
			//radius -= 0.1f;
			//xVis = sin(radius);
			//zVis = cos(radius);
		}


	}



	glutPostRedisplay();
	glutTimerFunc(100, xmove, 1);
}

int C_YCOUNT = 0;
void C_Y(int index) // 카메라 자전 어떻게 하는뎀ㄹㅇㅁㄴㄹㅇㅁㄴㄻㄴㅇㄹㄴㅁㅇㄻㄴㄻㄶㅁㅎ
{
	if (C_YCOUNT == 1)
	{
		CameraY += 5.0f;
		xVis = 800.0f;
		//radius += 0.1f;
		//xVis = sin(radius);
		//zVis = cos(radius);
		cout << CameraY << endl;
	}
	else if (C_YCOUNT == 2)
	{
		CameraY -= 5.0f;
		//radius -= 0.1f;
		//xVis = sin(radius);
		//zVis = cos(radius);
	}


	glutPostRedisplay();
	glutTimerFunc(100, C_Y, 1);
}



int C_YROCOUNT = 0;
int CY_flag = 1;
int CY_flag1 = 1;
void C_YRO(int index) // y/Y부터!!!!!!!
{
	if (ALLSTOP == 1)
	{
		//zPos= 0.4f;
		glm::mat4 TLR = glm::mat4(1.0f);
		glm::mat4 TL = glm::mat4(1.0f);
		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);


		//TL = glm::translate(TL, glm::vec3(0, -0.1, -0.1));
		Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));
		//TLR = glm::translate(TLR, glm::vec3(0, 0.1, 0.1));
		if (C_YROCOUNT == 1)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}
		else if (C_YROCOUNT == 2)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz1 * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}
	}


	glutPostRedisplay();
	glutTimerFunc(100, C_YRO, 1);
}

int C_XROCOUNT = 0;
int CX_flag = 1;
int CX_flag1 = 1;
void C_XRO(int index) 
{
	if (ALLSTOP == 1)
	{
		//zPos= 0.4f;
		glm::mat4 TLR = glm::mat4(1.0f);
		glm::mat4 TL = glm::mat4(1.0f);
		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);


		//TL = glm::translate(TL, glm::vec3(0, -0.1, -0.1));
		Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(1.0, 0.0, 0.0));
		//TLR = glm::translate(TLR, glm::vec3(0, 0.1, 0.1));
		if (C_XROCOUNT == 1)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}
		else if (C_XROCOUNT == 2)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz1 * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}

	}

	glutPostRedisplay();
	glutTimerFunc(100, C_XRO, 1);
}

int C_ZROCOUNT = 0;
int CZ_flag = 1;
int CZ_flag1 = 1;
void C_ZRO(int index)
{
	if (ALLSTOP == 1)
	{
		//zPos= 0.4f;
		glm::mat4 TLR = glm::mat4(1.0f);
		glm::mat4 TL = glm::mat4(1.0f);
		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);


		//TL = glm::translate(TL, glm::vec3(0, -0.1, -0.1));
		Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(0.0, 0.0, 1.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(0.0, 0.0, 1.0));
		//TLR = glm::translate(TLR, glm::vec3(0, 0.1, 0.1));
		if (C_ZROCOUNT == 1)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}
		else if (C_ZROCOUNT == 2)
		{
			glm::vec4 a(xPos, yPos, zPos, 1.0f);
			a = Rz1 * a;
			xPos = a[0];
			yPos = a[1];
			zPos = a[2];
		}

	}

	glutPostRedisplay();
	glutTimerFunc(100, C_ZRO, 1);
}
//int CameraYflag = 0;
//void CYRot(int index)
//{
//	if (CameraYflag == 1)
//	{
//		CY += 5.0f;
//	}
//	else if (CameraYflag == 2)
//	{
//		CY -= 5.0f;
//	}
//	glutPostRedisplay();
//	glutTimerFunc(100, CYRot, 1);
//}
int Yflag = 1;
int Yflag1 = 1;
GLfloat YR = 0;
void Ymove(int index)
{
	if (ALLSTOP == 1)
	{

		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);

		Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));


		if (YCOUNT2 == 1)
		{

			for (int i = 0; i < 36; i++)
			{
				glm::vec4 a(CUBEsmall[i][0], CUBEsmall[i][1], CUBEsmall[i][2], 1.0f);
				a = Rz * a;
				CUBEsmall[i][0] = a[0];
				CUBEsmall[i][1] = a[1];
				CUBEsmall[i][2] = a[2];

				glm::vec4 b(CUBECL[i][0], CUBECL[i][1], CUBECL[i][2], 1.0f);
				b = Rz * b;

				CUBECL[i][0] = b[0];
				CUBECL[i][1] = b[1];
				CUBECL[i][2] = b[2];

				glm::vec4 c(CUBECR[i][0], CUBECR[i][1], CUBECR[i][2], 1.0f);
				c = Rz * c;

				CUBECR[i][0] = c[0];
				CUBECR[i][1] = c[1];
				CUBECR[i][2] = c[2];
			}
			YR += 5.0f;
		}
		else if (YCOUNT2 == 2)
		{


			for (int i = 0; i < 36; i++)
			{
				glm::vec4 a(CUBEsmall[i][0], CUBEsmall[i][1], CUBEsmall[i][2], 1.0f);
				a = Rz1 * a;
				CUBEsmall[i][0] = a[0];
				CUBEsmall[i][1] = a[1];
				CUBEsmall[i][2] = a[2];

				glm::vec4 b(CUBECL[i][0], CUBECL[i][1], CUBECL[i][2], 1.0f);
				b = Rz1 * b;

				CUBECL[i][0] = b[0];
				CUBECL[i][1] = b[1];
				CUBECL[i][2] = b[2];

				glm::vec4 c(CUBECR[i][0], CUBECR[i][1], CUBECR[i][2], 1.0f);
				c = Rz1 * c;

				CUBECR[i][0] = c[0];
				CUBECR[i][1] = c[1];
				CUBECR[i][2] = c[2];
			}
			YR -= 5.0f;
		}

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBEsmall, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);


		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECL, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);


		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO4[0]);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECR, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}


	glutPostRedisplay();
	glutTimerFunc(100, Ymove, 1);
}

int Zflag = 1;
int Zflag1 = 1;
void Zmove(int index)
{
	if (ALLSTOP == 1)
	{
		glm::mat4 TL = glm::mat4(1.0f);
		glm::mat4 TL1 = glm::mat4(1.0f);
		glm::mat4 TLR = glm::mat4(1.0f);
		glm::mat4 TLR1 = glm::mat4(1.0f);
		glm::mat4 RR = glm::mat4(1.0f);
		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);
		TL = glm::translate(TL, glm::vec3(0.3, -1.5, 0));

		Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(1.0, 0.0, 0.0));
		TLR = glm::translate(TLR, glm::vec3(-0.3, 1.5, 0));

		TL1 = glm::translate(TL1, glm::vec3(-0.3, -1.5, 0));
		TLR1 = glm::translate(TLR1, glm::vec3(0.3, 1.5, 0));

		glm::mat4 YRz = glm::mat4(1.0f);
		glm::mat4 YRzR = glm::mat4(1.0f);
		YRz = glm::rotate(YRz, glm::radians(-YR), glm::vec3(0.0, 1.0, 0.0));
		YRzR = glm::rotate(YRzR, glm::radians(YR), glm::vec3(0.0, 1.0, 0.0));
		if (ZCOUNT == 1)
		{

			if (FR < 18)
			{
				for (int i = 0; i < 36; i++)
				{

					glm::vec4 b(CUBECL[i][0], CUBECL[i][1], CUBECL[i][2], 1.0f);
					b = YRzR * TLR * Rz * TL * YRz * b;

					CUBECL[i][0] = b[0];
					CUBECL[i][1] = b[1];
					CUBECL[i][2] = b[2];

					glm::vec4 c(CUBECR[i][0], CUBECR[i][1], CUBECR[i][2], 1.0f);
					c = YRzR * TLR1 * Rz1 * TL1 * YRz * c;

					CUBECR[i][0] = c[0];
					CUBECR[i][1] = c[1];
					CUBECR[i][2] = c[2];
				}
				FR++;
			}





		}
		else if (ZCOUNT == 2)
		{
			if (FR > -18)
			{
				for (int i = 0; i < 36; i++)
				{

					glm::vec4 b(CUBECL[i][0], CUBECL[i][1], CUBECL[i][2], 1.0f);
					b = YRzR * TLR * Rz1 * TL * YRz * b;

					CUBECL[i][0] = b[0];
					CUBECL[i][1] = b[1];
					CUBECL[i][2] = b[2];

					glm::vec4 c(CUBECR[i][0], CUBECR[i][1], CUBECR[i][2], 1.0f);
					c = YRzR * TLR1 * Rz * TL1 * YRz * c;

					CUBECR[i][0] = c[0];
					CUBECR[i][1] = c[1];
					CUBECR[i][2] = c[2];
				}
				FR--;
			}

		}


		glBindVertexArray(VAO[3]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECL, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[4]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO4[0]);
		glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), CUBECR, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

	}

	glutPostRedisplay();
	glutTimerFunc(100, Zmove, 1);
}

int TRIR = 0;



int XUP = 0;

void C_XUP(int value)
{
	if (ALLSTOP == 1)
	{
		if (XUP == 1)
		{
			xPos += 0.01f;

		}
		else if (XUP == 2)
		{
			xPos -= 0.01f;

		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, C_XUP, 1);
}

int ZUP = 0;

int ZCOUNTSTART = 0;
int XCOUNTSTART = 0;
int YCOUNTSTART = 0;
int ZUPSTART = 0;
int YUPSTART = 0;
int XUPSTART = 0;
int CZSTART = 0;
int CYSTART = 0;
int CXSTART = 0;
int C_YSTART = 0;
void C_ZUP(int value)
{
	if (ALLSTOP == 1)
	{
		if (ZUP == 1)
		{
			zPos += 0.01f;

		}
		else if (ZUP == 2)
		{
			zPos -= 0.01f;

		}
	}

	glutPostRedisplay();
	glutTimerFunc(100, C_ZUP, 1);
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
		case'1':
			COUNT = 1;
			break;
		case'2':
			COUNT = 0;
			break;
		case'b':

			if (Xflag == 1)
			{
				if (XCOUNT == 0)
				{
					XCOUNTSTART = 1;
					glutTimerFunc(100, xmove, 1);
				}
				else if (XCOUNTSTART == 0)
				{
					XCOUNTSTART = 1;
					glutTimerFunc(100, xmove, 1);

				}
				XCOUNT = 1;

				Xflag = 0;
				Xflag1 = 1;
			}
			else
			{
				XCOUNT = 10;
				Xflag = 1;

			}
			break;
		case'B':
			if (Xflag1 == 1)
			{
				if (XCOUNT == 0)
				{
					XCOUNTSTART = 1;
					glutTimerFunc(100, xmove, 1);
				}
				else if (XCOUNTSTART == 0)
				{
					XCOUNTSTART = 1;
					glutTimerFunc(100, xmove, 1);

				}
				XCOUNT = 2;

				Xflag1 = 0;
				Xflag = 1;
			}
			else
			{
				XCOUNT = 10;
				Xflag1 = 1;

			}

			break;
		case'm':
			if (Yflag == 1)
			{
				if (YCOUNT2 == 0)
				{
					YCOUNTSTART = 1;
					glutTimerFunc(100, Ymove, 1);
				}
				else if (YCOUNTSTART == 0)
				{
					YCOUNTSTART = 1;
					glutTimerFunc(100, Ymove, 1);

				}
				YCOUNT2 = 1;
				
				Yflag = 0;
				Yflag1 = 1;
			}
			else
			{
				YCOUNT2 = 10;
				Yflag = 1;

			}
			break;
		case'M':
			if (Yflag1 == 1)
			{
				if (YCOUNT2 == 0)
				{
					YCOUNTSTART = 1;
					glutTimerFunc(100, Ymove, 1);
				}
				else if (YCOUNTSTART == 0)
				{
					YCOUNTSTART = 1;
					glutTimerFunc(100, Ymove, 1);

				}
				YCOUNT2 = 2;

				Yflag1 = 0;
				Yflag = 1;
			}
			else
			{
				YCOUNT2 = 10;
				Yflag1 = 1;

			}

			break;
		case't':
			if (Zflag == 1)
			{
				if (ZCOUNT == 0)
				{
					ZCOUNTSTART = 1;
					glutTimerFunc(100, Zmove, 1);
				}
				else if (ZCOUNTSTART == 0)
				{
					ZCOUNTSTART = 1;
					glutTimerFunc(100, Zmove, 1);

				}
				ZCOUNT = 1;
				Zflag = 0;
				Zflag1 = 1;
			}
			else
			{
				ZCOUNT = 10;
				Zflag = 1;

			}

			break;
		case'T':
			if (Zflag1 == 1)
			{
				if (ZCOUNT == 0)
				{
					ZCOUNTSTART = 1;
					glutTimerFunc(100, Zmove, 1);
				}
				else if (ZCOUNTSTART == 0)
				{
					ZCOUNTSTART = 1;
					glutTimerFunc(100, Zmove, 1);

				}
				ZCOUNT = 2;
				Zflag1 = 0;
				Zflag = 1;
			}
			else
			{
				ZCOUNT = 10;
				Zflag1 = 1;
			}


			break;

		case'z':
			if (ZUP == 0)
			{
				ZUPSTART = 1;
				glutTimerFunc(100, C_ZUP, 1);
			}
			else if (ZUPSTART == 0)
			{
				ZUPSTART = 1;
				glutTimerFunc(100, C_ZUP, 1);

			}
			ZUP = 1;

			break;
		case'Z':
			if (ZUP == 0)
			{
				ZUPSTART = 1;
				glutTimerFunc(100, C_ZUP, 1);
			}
			else if (ZUPSTART == 0)
			{
				ZUPSTART = 1;
				glutTimerFunc(100, C_ZUP, 1);

			}
			ZUP = 2;

			break;
		case'x':
			if (XUP == 0)
			{
				XUPSTART = 1;
				glutTimerFunc(100, C_XUP, 1);
			}
			else if (XUPSTART == 0)
			{
				XUPSTART = 1;
				glutTimerFunc(100, C_XUP, 1);

			}
			XUP = 1;

			break;
		case'X':
			if (XUP == 0)
			{
				XUPSTART = 1;
				glutTimerFunc(100, C_XUP, 1);
			}
			else if (XUPSTART == 0)
			{
				XUPSTART = 1;
				glutTimerFunc(100, C_XUP, 1);

			}
			XUP = 2;

			break;
		case'y':
			if (C_YCOUNT == 0)
			{
				C_YSTART = 1;
				glutTimerFunc(100, C_Y, 1);
			}
			else if (C_YSTART == 0)
			{
				C_YSTART = 1;
				glutTimerFunc(100, C_Y, 1);

			}
			C_YCOUNT = 1;

			break;
		case'Y':
			if (C_YCOUNT == 0)
			{
				C_YSTART = 1;
				glutTimerFunc(100, C_Y, 1);
			}
			else if (C_YSTART == 0)
			{
				C_YSTART = 1;
				glutTimerFunc(100, C_Y, 1);

			}
			C_YCOUNT = 2;

			break;

		//case'y':

		//	if (C_YCOUNT == 0)
		//	{
		//		glutTimerFunc(100, C_Y, 1);
		//	}
		//	C_YCOUNT = 1;

		//	break;
		//case'Y':

		//	if (C_YCOUNT == 0)
		//	{
		//		glutTimerFunc(100, C_Y, 1);
		//	}
		//	C_YCOUNT = 2;

		//	break;
		case'r':
			if (CY_flag == 1)
			{
				if (C_YROCOUNT == 0)
				{
					CYSTART = 1;
					glutTimerFunc(100, C_YRO, 1);
				}
				else if (CYSTART == 0)
				{
					CYSTART = 1;
					glutTimerFunc(100, C_YRO, 1);

				}
				C_YROCOUNT = 1;
				CY_flag = 0;
				CY_flag1 = 1;
			}
			else
			{
				C_YROCOUNT = 10;
				CY_flag = 1;

			}


			break;
		case'R':
			if (CY_flag1 == 1)
			{
				if (C_YROCOUNT == 0)
				{
					CYSTART = 1;
					glutTimerFunc(100, C_YRO, 1);
					
				}
				else if (CYSTART == 0)
				{
					CYSTART = 1;
					glutTimerFunc(100, C_YRO, 1);

				}
				C_YROCOUNT = 2;
				CY_flag1 = 0;
				CY_flag = 1;
			}
			else
			{
				C_YROCOUNT = 10;
				CY_flag1 = 1;
			}


			break;
		case'a':
			if (CX_flag == 1)
			{
				if (C_XROCOUNT == 0)
				{
					CXSTART = 1;
					glutTimerFunc(100, C_XRO, 1);

				}
				else if (CXSTART == 0)
				{
					CXSTART = 1;
					glutTimerFunc(100, C_XRO, 1);

				}
				C_XROCOUNT = 1;
				CX_flag = 0;
				CX_flag1 = 1;
			}
			else
			{
				C_XROCOUNT = 10;
				CX_flag = 1;

			}


			break;
		case'A':
			if (CX_flag1 == 1)
			{
				if (C_XROCOUNT == 0)
				{
					glutTimerFunc(100, C_XRO, 1);
					CXSTART = 1;
				}
				else if (CXSTART == 0)
				{
					CXSTART = 1;
					glutTimerFunc(100, C_XRO, 1);
					
				}
				C_XROCOUNT = 2;
				CX_flag1 = 0;
				CX_flag = 1;
			}
			else
			{
				C_XROCOUNT = 10;
				CX_flag1 = 1;
			}


			break;
		case'n':
			if (CZ_flag == 1)
			{
				if (C_ZROCOUNT == 0)
				{
					CZSTART = 1;
					glutTimerFunc(100, C_ZRO, 1);

				}
				else if (CZSTART == 0)
				{
					CZSTART = 1;
					glutTimerFunc(100, C_ZRO, 1);
				}
				C_ZROCOUNT = 1;
				CZ_flag = 0;
				CZ_flag1 = 1;
			}
			else
			{
				C_ZROCOUNT = 10;
				CZ_flag = 1;

			}


			break;
		case'N':
			if (CZ_flag1 == 1)
			{
				if (C_ZROCOUNT == 0)
				{
					CZSTART = 1;
					glutTimerFunc(100, C_ZRO, 1);
					
				}
				else if (CZSTART == 0)
				{
					CZSTART = 1;
					glutTimerFunc(100, C_ZRO, 1);
				}

				C_ZROCOUNT = 2;
				CZ_flag1 = 0;
				CZ_flag = 1;
			}
			else
			{
				C_ZROCOUNT = 10;
				CZ_flag1 = 1;
			}


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
		case's':
			ALLSTOP = 0;
			break;
		case'S':
			ALLSTOP = 1;
			break;
		case'c':
			COUNT = 0;
			polygon_mode = 1;
			TX = 0.0f;
			TY = 0.0f;
			TZ = 0.0f;
			xPos = 0.0f;
			yPos = 0.1f;
			zPos = 0.1f;
			YR = 0;
			FR = 0;
			for (int i = 0; i < 36; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					testCUBE[i][j] = testCUBECOPY[i][j];
					CUBEsmall[i][j] = CUBEsmallCOPY[i][j];
					CUBECL[i][j] = CUBECLCOPY[i][j];
					CUBECR[i][j] = CUBECRCOPY[i][j];
				}
			}

			Xflag = 1;
			Xflag1 = 1;
			XCOUNT = 10;

			Yflag = 1;
			Yflag1 = 1;
			YCOUNT2 = 10;

			Zflag = 1;
			Zflag1 = 1;
			ZCOUNT = 10;
			ZUP = 10;
			XUP = 10;
			C_YCOUNT = 10;
			CY_flag = 1;
			CY_flag1 = 1;
			C_YROCOUNT = 10;
			CX_flag = 1;
			CX_flag1 = 1;
			C_XROCOUNT = 10;
			CZ_flag = 1;
			CZ_flag1 = 1;
			C_ZROCOUNT = 10;
			hflag == 1;
			SH_COUNT = 0;
			ALLSTOP = 1;
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
		default:
			break;
		}

	glutPostRedisplay();
}






