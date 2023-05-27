// Reading Obj file
#define  _CRT_SECURE_NO_WARNINGS


#include "shader.h"
#include "objRead.h"
#include <conio.h>

using namespace std;
int update = 0;
int COUNT = 0;
int COUNT1 = 0;
int COUNT_D = 0;
int hflag = 1;
int SH_COUNT = 2;
int XCOUNT = 0;
int YCOUNT = 0;
int XCOUNT1 = 0;
int YCOUNT1 = 0;
int XCOUNT2 = 0;
int YCOUNT2 = 0;
int CFlag = 1;
GLuint g_window_w = 800;
GLuint g_window_h = 800;
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


GLfloat X = 10.0f;
GLfloat Y = 10.0f;
GLfloat X1 = 20.0f;
GLfloat Y1 = 20.0f;
GLfloat Y2 = 0.0f;

GLfloat Y_L = 20.0f;
GLfloat Y_L1 = 20.0f;

int polygon_mode = 1;

const int num_vertices = 3;
const int num_triangles = 1;


//22번 ------------------
GLfloat Light_R = 1.0f;
GLfloat Light_G = 1.0f;
GLfloat Light_B = 1.0f;
int RGBflag = 1;
GLfloat Light_Posx = 0.0f;
GLfloat Light_Posy = 0.0f;
GLfloat Light_Posz = 3.0f;
GLfloat Light_Distance = 0.0f;
//-----------------------
void Display();
void Display_Camera();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();

GLfloat testCUBE[36][3] = {


	{1,1,-1},
	{1,-1,-1},
	{-1,-1,-1},
	{1,1,-1},
	{-1,-1,-1},
	{-1,1,-1},
	{1,-1,-1},
	{1,-1,1},
	{-1,-1,1},
	{1,-1,-1},
	{-1,-1,1},
	{-1,-1,-1},
	{-1,-1,1},
	{-1,1,1},
	{-1,1,-1},
	{-1,-1,1},
	{-1,1,-1},
	{-1,-1,-1},
	{1,-1,-1},
	{1,1,-1},
	{1,-1,1},
	{1,1,-1},
	{1,1,1},
	{1,-1,1},
	{1,-1,1},
	{1,1,1},
	{-1,-1,1},
	{1,1,1},
	{-1,1,1},
	{-1,-1,1},
	{1,1,-1},
	{-1,1,-1},
	{1,1,1},
	{-1,1,-1},
	{-1,1,1},
	{1,1,1},







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

GLfloat Pyramid[18][3] = {

	{1,0,-1},
	{-1,0,-1},
	{-1,0,1},
	{1,0,1},
	{1,0,-1},
	{-1,0,1},
	{0,1.2,0},
	{-1,0,-1},
	{-1,0,1},
	{-1,0,-1},
	{0,1.2,0},
	{1,0,-1},
	{1,0,-1},
	{0,1.2,0},
	{1,0,1},
	{0,1.2,0},
	{1,0,1},
	{-1,0,1},



};

GLfloat tri_color[18][3] = {
	{1,0.64,0}, //2
	{1,0,0},//1
	{1,1,0},//3
	{0,1,0},//4
	{1,0.64,0},//2
	{1,1,0},//3
	{0,0,1},//5
	{1,0,0},//1
	{1,1,0},//3
	{1,0,0},//1
	{0,0,1},//5
	{1,0.64,0},//2
	{1,0.64,0},//2
	{0,0,1},//5
	{0,1,0},//4
	{0,0,1},//5
	{0,1,0},//4
	{1,1,0},//3







};

GLfloat Light_Circle[36][3] = {
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},
	{0,0,0},{0,0,0},{0,0,0},





};

GLfloat Light_Circle_Color[36][3] = {
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},
	{0.60, 0.80, 0.66},{0.60, 0.80, 0.66},{0.60, 0.80, 0.66}



};
GLfloat Light_Circle_Normal[36][3] = {
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},
	{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},{0.5 , 0.5 , 0.5},



};


//--- load obj related variabales
objRead objReader; //CUBE
GLint Object = objReader.loadObj_normalize_center("test.obj");
//
objRead objReader1; //PIRAMID
GLint Object1 = objReader1.loadObj_normalize_center1("pyramid.obj");

objRead objReader2; //CUBE
GLint Object2 = objReader2.loadObj_normalize_center2("test.obj");


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
	vShader[1] = MakeVertexShader("vertex2.glsl", 1);			// Sun
	fShader[1] = MakeFragmentShader("fragment2.glsl", 1);

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
	//glutDisplayFunc(Display_Camera);
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


	// 2 triangles for quad floor
	glUseProgram(s_program[0]);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), test, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);

	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO2[2]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
	GLint nAttribute1 = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute1);

	// 조명
	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);

	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO4[2]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
	GLint nAttribute4 = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute4);


	unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
	unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
	int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
	unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);




	glUseProgram(s_program[1]);
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader1.outvertex.size() * sizeof(glm::vec3), &objReader1.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[1], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), tri_color, GL_STATIC_DRAW);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1[2]);
	glBufferData(GL_ARRAY_BUFFER, objReader1.outnormal.size() * sizeof(glm::vec3), &objReader1.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute2 = glGetAttribLocation(s_program[1], "aNormal");
	glVertexAttribPointer(nAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute2);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
	GLint pAttribute3 = glGetAttribLocation(s_program[1], "aPos");
	glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute3);

	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3[2]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
	GLint nAttribute3 = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute3);

	// 조명
	glBindVertexArray(VAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);

	//cout << objReader.outvertex.size() << endl;
	glBindBuffer(GL_ARRAY_BUFFER, VBO4[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO4[2]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
	GLint nAttribute4 = glGetAttribLocation(s_program[0], "aNormal");
	glVertexAttribPointer(nAttribute4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute4);

	glUseProgram(s_program[1]);
	unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
	unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
	int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
	unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
	glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);

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
	else if (SH_COUNT == 0)
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
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(0.4, 0.4, 0.4));

	model = glm::translate(model, glm::vec3(TX, TY, TZ));

	Rz = glm::rotate(Rz, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(X), glm::vec3(1.0, 0.0, 0.0));

	RR = model * Rz2 * Rz * S;

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));





	glUseProgram(s_program[1]);
	glm::mat4 Rz3 = glm::mat4(1.0f);
	glm::mat4 Rz4 = glm::mat4(1.0f);
	glm::mat4 RR1 = glm::mat4(1.0f);
	glm::mat4 S1 = glm::mat4(1.0f);
	glm::mat4 model1 = glm::mat4(1.0f);
	S1 = glm::scale(S1, glm::vec3(0.6, 0.6, 0.6));

	//피라미드

	Rz3 = glm::rotate(Rz3, glm::radians(Y1), glm::vec3(0.0, 1.0, 0.0));
	Rz4 = glm::rotate(Rz4, glm::radians(X1), glm::vec3(1.0, 0.0, 0.0));


	RR1 = Rz4 * Rz3 * S1;

	unsigned int modelLocation1 = glGetUniformLocation(s_program[1], "modelTransform2");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(RR1));

	Display_Camera();
	//glutSwapBuffers();

}
GLfloat pPro = -4;
GLfloat pPro1 = 4;
int PRO_Flag = 1;

void Display_Camera()
{

	glUseProgram(s_program[0]);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.1f); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glm::mat4 projection = glm::mat4(1.0f);
	if (PRO_Flag == 1)
	{
		projection = glm::ortho(pPro, pPro1, pPro, pPro1, pPro, pPro1);
	}
	else if (PRO_Flag == 0)
	{
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0));


	}


	unsigned int projectionLocation = glGetUniformLocation(s_program[0], "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	if (COUNT == 1)
	{
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, Object);


		glBindVertexArray(VAO[2]);
		glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 36);
	}


	glUseProgram(s_program[1]);

	unsigned int viewLocation2 = glGetUniformLocation(s_program[1], "viewTransform2"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, &view[0][0]);

	unsigned int projectionLocation2 = glGetUniformLocation(s_program[1], "projectionTransform2"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection[0][0]);

	if (COUNT1 == 1)
	{
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, Object1);
		glBindVertexArray(VAO[3]);
		glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 36);
	}

	glUseProgram(s_program[0]);
	glutSwapBuffers();

}
void ymove(int index)
{
	if (YCOUNT == 1)
	{
		Y += 5.0;
		Y1 += 5.0;


	}

	glutPostRedisplay();
	glutTimerFunc(100, ymove, 1);
}


int TRIR = 0;

int C_YROCOUNT = 0;
int CY_flag = 1;
int CY_flag1 = 1;
int Circle_index = 0;
void C_YRO(int index) // y/Y부터!!!!!!!
{

		//zPos= 0.4f;
		glm::mat4 TLR = glm::mat4(1.0f);
		glm::mat4 TL = glm::mat4(1.0f);
		glm::mat4 Rz = glm::mat4(1.0f);
		glm::mat4 Rz1 = glm::mat4(1.0f);


		TL = glm::translate(TL, glm::vec3(0,0,0));
		Rz = glm::rotate(Rz, glm::radians(10.0f), glm::vec3(0.0, 1.0, 0.0));
		Rz1 = glm::rotate(Rz1, glm::radians(-10.0f), glm::vec3(0.0, 1.0, 0.0));
		TLR = glm::translate(TLR, glm::vec3(0,0,0));
		if (C_YROCOUNT == 1)
		{
			glm::vec4 a(Light_Posx, Light_Posy, Light_Posz, 1.0f);
			a = TLR * Rz * TL * a;
			Light_Posx = a[0];
			Light_Posy = a[1];
			Light_Posz = a[2];


			//cout << Light_Posx << endl;
			//cout << Light_Posy << endl;
			//cout << Light_Posz << endl;
			if (Circle_index < 36)
			{

					Light_Circle[Circle_index][0] = Light_Posx;
					Light_Circle[Circle_index][1] = Light_Posy;
					Light_Circle[Circle_index][2] = Light_Posz;

					Light_Circle_Color[Circle_index][0] = 1;
					Light_Circle_Color[Circle_index][1] = 1;
					Light_Circle_Color[Circle_index][2] = 1;




				Circle_index++;
			}
		}
		else if (C_YROCOUNT == 2)
		{
			glm::vec4 a(Light_Posx, Light_Posy, Light_Posz, 1.0f);
			a = TLR *  Rz1 * TL *  a;
			Light_Posx = a[0];
			Light_Posy = a[1];
			Light_Posz = a[2];

		}
	


		unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
		glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
		unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
		glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
		int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
		glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
		unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);


		if (COUNT == 1)
		{
			glUseProgram(s_program[0]);
			glBindVertexArray(VAO[2]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
			glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute1);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(1);


			glBindBuffer(GL_ARRAY_BUFFER, VBO2[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute1 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute1);


		}

		glUseProgram(s_program[1]);
		unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
		glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
		unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
		glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
		int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
		glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
		unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
		glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);

		if (COUNT1 == 1)
		{
			glUseProgram(s_program[1]);
			glBindVertexArray(VAO[3]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute3 = glGetAttribLocation(s_program[1], "aPos");
			glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute3);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(6);

			glBindBuffer(GL_ARRAY_BUFFER, VBO3[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute3 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute3);
		}

	glutPostRedisplay();
	glutTimerFunc(100, C_YRO, 1);
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
		COUNT1 = 0;
		break;
	case'2':
		COUNT1 = 1;
		COUNT = 0;
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

	case'p':
		PRO_Flag = 1;
		break;
	case'P':
		PRO_Flag = 0;
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

	case'm':
		if (RGBflag == 1)
		{
			Light_R = 0.0f;
			Light_G = 0.0f;
			Light_B = 0.0f;

			unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
			int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);

			glUseProgram(s_program[1]);
			unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
			int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			RGBflag = 0;
		}
		else
		{
			Light_R = 1.0f;
			Light_G = 1.0f;
			Light_B = 1.0f;

			unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
			int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);

			glUseProgram(s_program[1]);
			unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
			int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			RGBflag = 1;

		}

		break;
	

	case'r':
		if (CY_flag == 1)
		{
			if (C_YROCOUNT == 0)
			{

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

	case'z':
		Light_Distance += 0.3f;
		Light_Posz = Light_Posz + 0.3f;

		cout << Light_Posz << endl;
		if (COUNT == 1)
		{
			Circle_index = 0;
			unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
			int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);


			glUseProgram(s_program[0]);
			glBindVertexArray(VAO[2]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
			glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute1);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(1);

		}


		if (COUNT1 == 1)
		{
			Circle_index = 0;

			glBindBuffer(GL_ARRAY_BUFFER, VBO2[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute1 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute1);
			glUseProgram(s_program[1]);
			unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
			int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);


			glBindVertexArray(VAO[3]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute3 = glGetAttribLocation(s_program[1], "aPos");
			glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute3);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(6);

			glBindBuffer(GL_ARRAY_BUFFER, VBO3[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute3 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute3);
		}
		break;

	case'Z':
		Light_Distance -= 0.3f;
		Light_Posz -= 0.3f;

		if (COUNT == 1)
		{
			Circle_index = 0;
			unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation, Light_R, Light_G, Light_B);
			int objColorLocation = glGetUniformLocation(s_program[0], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation, Light_Posx, Light_Posy, Light_Posz);


			glUseProgram(s_program[0]);
			glBindVertexArray(VAO[2]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
			glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute1);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(1);

		}


		if (COUNT1 == 1)
		{
			Circle_index = 0;
			glBindBuffer(GL_ARRAY_BUFFER, VBO2[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute1 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute1);
			glUseProgram(s_program[1]);
			unsigned int lightPosLocation2 = glGetUniformLocation(s_program[1], "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
			glUniform3f(lightPosLocation2, Light_Posx, Light_Posy, Light_Posz);
			unsigned int lightColorLocation2 = glGetUniformLocation(s_program[1], "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
			glUniform3f(lightColorLocation2, Light_R, Light_G, Light_B);
			int objColorLocation2 = glGetUniformLocation(s_program[1], "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
			glUniform3f(objColorLocation2, 0.60, 0.80, 0.66);
			unsigned int viewPosLocation2 = glGetUniformLocation(s_program[1], "viewPos"); //--- viewPos 값 전달: 카메라 위치
			glUniform3f(viewPosLocation2, Light_Posx, Light_Posy, Light_Posz);


			glBindVertexArray(VAO[3]);
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle, GL_STATIC_DRAW);
			GLint pAttribute3 = glGetAttribLocation(s_program[1], "aPos");
			glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(pAttribute3);

			//cout << objReader.outvertex.size() << endl;
			glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), Light_Circle_Color, GL_STATIC_DRAW);
			glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(6);

			glBindBuffer(GL_ARRAY_BUFFER, VBO3[2]);
			glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(glm::vec3), Light_Circle_Normal, GL_STATIC_DRAW);
			GLint nAttribute3 = glGetAttribLocation(s_program[0], "aNormal");
			glVertexAttribPointer(nAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(nAttribute3);
		}

		break;

	case's':
		COUNT = 1;
		hflag = 1;
		SH_COUNT = 0;
		XCOUNT = 0;
		YCOUNT = 0;
		polygon_mode = 1;
		TX = 0.5;
		TY = 0;
		TX1 = -0.5;
		TY1 = 0.2;

		X = 5.0f;
		Y = -40.0f;
		X1 = 5.0f;
		Y1 = -40.0f;
		Y2 = 0.0f;
		Y_L = 20.0f;
		Y_L1 = 40.0f;
		update = 0;

		COUNT1 = 1;
		COUNT_D = 0;


		XCOUNT1 = 0;
		YCOUNT1 = 0;
		XCOUNT2 = 0;
		YCOUNT2 = 0;
		CFlag = 1;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}






