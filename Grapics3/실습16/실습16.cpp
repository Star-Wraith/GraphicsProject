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
GLuint VBO5[3];
GLuint VBO6[3];
GLuint VBO7[3];
GLuint VBO8[3];
GLuint VBO9[3];

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
	//{1,0,0},
	//{0,0,0},
	//{0,0,1},
	//{1,0,1},
	//{1,0,0},
	//{0,0,1},
	//{0.5,1.2,0.5},
	//{0,0,1},
	//{0,0,0},
	//{1,0,0},
	//{0.5,1.2,0.5},
	//{0,0,0},
	//{1,0,1},
	//{0.5,1.2,0.5},
	//{1,0,0},
	//{0.5,1.2,0.5},
	//{1,0,1},
	//{0,0,1},
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
objRead objReader; //CUBE
GLint Object = objReader.loadObj_normalize_center("test.obj");
//
objRead objReader1; //PIRAMID
GLint Object1 = objReader1.loadObj_normalize_center1("pyramid.obj");

objRead objReader2; //SPHERE
GLint Object2 = objReader2.loadObj_normalize_center2("test1.obj");

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
	vShader[3] = MakeVertexShader("vertex3.glsl", 3);			// Sun
	fShader[3] = MakeFragmentShader("fragment3.glsl", 3);

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

	s_program[3] = glCreateProgram();
	glAttachShader(s_program[3], vShader[3]);
	glAttachShader(s_program[3], fShader[3]);
	glLinkProgram(s_program[3]);
	checkCompileErrors(s_program[3], "PROGRAM");
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
	glGenBuffers(3, VBO5);
	glGenBuffers(3, VBO6);
	glGenBuffers(3, VBO7);
	glGenBuffers(3, VBO8);
	glGenBuffers(3, VBO9);


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
	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(glm::vec3), Pyramid, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[2], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);
	


	glBindBuffer(GL_ARRAY_BUFFER, VBO3[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), tri_color, GL_STATIC_DRAW);
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
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(0.4, 0.4, 0.4));

	model = glm::translate(model, glm::vec3(TX, TY, TZ));

	Rz = glm::rotate(Rz, glm::radians(Y), glm::vec3(0.0, 1.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(X), glm::vec3(1.0, 0.0, 0.0));
	
	RR = model * Rz2 * Rz * S;

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));




	//------------------------------------------------------------------------------
	//선분 회전시켜놓기
	glm::mat4 R_Line = glm::mat4(1.0f);
	glm::mat4 R_Line2 = glm::mat4(1.0f);

	glm::mat4 RO = glm::mat4(1.0f);
	glUseProgram(s_program[1]);
	R_Line = glm::rotate(R_Line, glm::radians(Y_L), glm::vec3(0.0, 1.0, 0.0));
	R_Line2 = glm::rotate(R_Line2, glm::radians(Y_L1), glm::vec3(1.0, 0.0, 0.0));

	RO = R_Line2 * R_Line;

	unsigned int lineLocation = glGetUniformLocation(s_program[1], "modelTransform1");
	glUniformMatrix4fv(lineLocation, 1, GL_FALSE, glm::value_ptr(RO));

	glUseProgram(s_program[2]);
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




	unsigned int modelLocation1 = glGetUniformLocation(s_program[2], "modelTransform2");
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(RR1));

	Display_Camera();
	//glutSwapBuffers();

}
GLfloat pPro = -2;
GLfloat pPro1 = 2;
int PRO_Flag = 1;
void C_YRO(int value)
{

}
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
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//glm::vec3 cameraPos1 = glm::vec3(0.0f, 0.0f, 0.3f); //--- 카메라 위치
	//glm::vec3 cameraDirection1 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	//glm::vec3 cameraUp1 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	//glm::mat4 view1 = glm::mat4(1.0f);

	//view1 = glm::lookAt(cameraPos1, cameraDirection1, cameraUp1);
	//glUseProgram(s_program[3]);
	//unsigned int viewLocation3 = glGetUniformLocation(s_program[3], "viewTransform3"); //--- 뷰잉 변환 설정
	//glUniformMatrix4fv(viewLocation3, 1, GL_FALSE, &view1[0][0]);
	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 12, 12);
	//glBindVertexArray(VAO[1]);

	glUseProgram(s_program[2]);

	unsigned int viewLocation2 = glGetUniformLocation(s_program[2], "viewTransform2"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, &view[0][0]);

	unsigned int projectionLocation2 = glGetUniformLocation(s_program[2], "projectionTransform2"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection[0][0]);

	if (COUNT1 == 1)
	{
		glBindVertexArray(VAO[3]);
		glDrawArrays(GL_TRIANGLES, 0, Object1);
	}


	glUseProgram(s_program[1]);
	unsigned int viewLocation1 = glGetUniformLocation(s_program[1], "viewTransform1"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation1, 1, GL_FALSE, &view[0][0]);

	unsigned int projectionLocation1 = glGetUniformLocation(s_program[1], "projectionTransform1"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation1, 1, GL_FALSE, &projection[0][0]);
	glBindVertexArray(VAO[2]);

	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	//glUseProgram(s_program[3]);
	glUseProgram(s_program[0]);
	glutSwapBuffers();

}

void LRmove(int index)
{
	if (XCOUNT == 1)
	{
		if (testCUBE[23][1] < 1)
		{
			for (int i = 12; i < 24; i++)
			{
				testCUBE[i][1] += 0.1f;
			}
		}



	}
	else if (XCOUNT == 2)
	{
		if (testCUBE[23][1] > -1)
		{
			for (int i = 12; i < 24; i++)
			{
				testCUBE[i][1] -= 0.1f;
			}
		}
	}


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), testCUBE, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);



	glutPostRedisplay();
	glutTimerFunc(100, LRmove, 1);
}
void UPmove(int index)
{
	glm::mat4 TL = glm::mat4(1.0f);
	glm::mat4 TL1 = glm::mat4(1.0f);
	glm::mat4 RR = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Rz1 = glm::mat4(1.0f);
	TL = glm::translate(TL, glm::vec3(0, -1, 0));

	Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));
	TL1 = glm::translate(TL1, glm::vec3(0, 1, 0));

	if (XCOUNT1 == 1)
	{

		for (int i = 30; i < 36; i++)
		{
			glm::vec4 a(testCUBE[i][0], testCUBE[i][1], testCUBE[i][2], 1.0f);
			a = TL1 * Rz * TL * a;
			testCUBE[i][0] = a[0];
			testCUBE[i][1] = a[1];
			testCUBE[i][2] = a[2];
		}

	}
	else if (XCOUNT1 == 2)
	{


			//for (int i = 30; i < 36; i++)
			//{

			//	testCUBE[i][0] = ;
			//	testCUBE[i][1] = ;
			//	testCUBE[i][2] = ;
			//}
	}


	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), testCUBE, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);





	glutPostRedisplay();
	glutTimerFunc(100, UPmove, 1);
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

void FRONTmove(int index)
{
	glm::mat4 TL = glm::mat4(1.0f);
	glm::mat4 TL1 = glm::mat4(1.0f);
	glm::mat4 RR = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Rz1 = glm::mat4(1.0f);
	TL = glm::translate(TL, glm::vec3(0, 1, -1));

	Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));
	Rz1 = glm::rotate(Rz, glm::radians(FR_minus), glm::vec3(1.0, 0.0, 0.0));
	TL1 = glm::translate(TL1, glm::vec3(0, -1, 1));

	if (YCOUNT2 == 1)
	{
		if (FR < 18)
		{
			for (int i = 24; i < 30; i++)
			{
				glm::vec4 a(testCUBE[i][0], testCUBE[i][1], testCUBE[i][2], 1.0f);
				a = TL1 * Rz * TL * a;
				testCUBE[i][0] = a[0];
				testCUBE[i][1] = a[1];
				testCUBE[i][2] = a[2];
			}

			FR++;
		}

	}
	else if (YCOUNT2 == 2)
	{
		if (FR > 0)
		{
			for (int i = 24; i < 30; i++)
			{
				glm::vec4 a(testCUBE[i][0], testCUBE[i][1], testCUBE[i][2], 1.0f);
				a = TL1 * Rz1 * TL * a;
				testCUBE[i][0] = a[0];
				testCUBE[i][1] = a[1];
				testCUBE[i][2] = a[2];
			}
			FR--;
		}

	}

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(glm::vec3), testCUBE, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);




	glutPostRedisplay();
	glutTimerFunc(100, FRONTmove, 1);
}

int TRIR = 0;


void TriR(int value)
{
	// 7~9
	glm::mat4 TL = glm::mat4(1.0f);
	glm::mat4 TL1 = glm::mat4(1.0f);
	glm::mat4 TL2 = glm::mat4(1.0f);
	glm::mat4 TL3 = glm::mat4(1.0f);
	glm::mat4 TLR = glm::mat4(1.0f);
	glm::mat4 TLR1 = glm::mat4(1.0f);
	glm::mat4 TLR2 = glm::mat4(1.0f);
	glm::mat4 TLR3 = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 Rz1 = glm::mat4(1.0f);
	glm::mat4 Rz2 = glm::mat4(1.0f);
	glm::mat4 Rz3 = glm::mat4(1.0f);
	glm::mat4 RzR = glm::mat4(1.0f);
	glm::mat4 RzR1 = glm::mat4(1.0f);
	glm::mat4 RzR2 = glm::mat4(1.0f);
	glm::mat4 RzR3 = glm::mat4(1.0f);
	TL = glm::translate(TL, glm::vec3(1, 0, 0));

	TL1 = glm::translate(TL1, glm::vec3(0, 0, 1));

	TL2 = glm::translate(TL2, glm::vec3(-1, 0, 0));

	TL3 = glm::translate(TL3, glm::vec3(0, 0, -1));

	Rz = glm::rotate(Rz, glm::radians(5.0f), glm::vec3(0.0, 0.0, 1.0));
	RzR = glm::rotate(RzR, glm::radians(-5.0f), glm::vec3(0.0, 0.0, 1.0));

	TLR = glm::translate(TLR, glm::vec3(-1, 0, 0));

	TLR1 = glm::translate(TLR1, glm::vec3(0, 0, -1));

	Rz1 = glm::rotate(Rz1, glm::radians(-5.0f), glm::vec3(1.0, 0.0, 0.0));
	RzR1 = glm::rotate(RzR1, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));

	TLR2 = glm::translate(TLR2, glm::vec3(1, 0, 0));

	Rz2 = glm::rotate(Rz2, glm::radians(-5.0f), glm::vec3(0.0, 0.0, 1.0));
	RzR2 = glm::rotate(RzR2, glm::radians(5.0f), glm::vec3(0.0, 0.0, 1.0));

	TLR3 = glm::translate(TLR3, glm::vec3(0, 0, 1));

	Rz3 = glm::rotate(Rz3, glm::radians(5.0f), glm::vec3(1.0, 0.0, 0.0));
	RzR3 = glm::rotate(RzR3, glm::radians(-5.0f), glm::vec3(1.0, 0.0, 0.0));
	if (YCOUNT1 == 1)
	{
		if (TRIR < 52)
		{
			for (int i = 6; i < 9; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR * Rz * TL * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 9; i < 12; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR1 * Rz1 * TL1 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 12; i < 15; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR2 * Rz2 * TL2 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 15; i < 18; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR3 * Rz3 * TL3 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			TRIR++;
		}





	}
	else if (YCOUNT1 == 2)
	{
		if (TRIR > 0)
		{
			for (int i = 6; i < 9; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR * RzR * TL * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 9; i < 12; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR1 * RzR1 * TL1 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 12; i < 15; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR2 * RzR2 * TL2 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}
			for (int i = 15; i < 18; i++)
			{
				glm::vec4 a(Pyramid[i][0], Pyramid[i][1], Pyramid[i][2], 1.0f);
				a = TLR3 * RzR3 * TL3 * a;
				Pyramid[i][0] = a[0];
				Pyramid[i][1] = a[1];
				Pyramid[i][2] = a[2];
			}

			TRIR--;
		}




	}

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3[0]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(glm::vec3), Pyramid, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(5);


	glutPostRedisplay();
	glutTimerFunc(100, TriR, 1);
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
			
		case'3':
			COUNT = 1;
			COUNT1 = 0;
			break;
		case'4':
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
		case'1':
			if (XCOUNT == 0)
			{
				glutTimerFunc(100, LRmove, 1);
			}
			XCOUNT = 1;
			break;

		case'2':
			if (XCOUNT == 0)
			{
				glutTimerFunc(100, LRmove, 1);
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
		case't':
			if (XCOUNT1 == 0)
			{
				glutTimerFunc(100, UPmove, 1);
			}
			XCOUNT1 = 1;
			break;

		case'T':
			if (XCOUNT1 == 0)
			{
				glutTimerFunc(100, UPmove, 1);
			}
			XCOUNT1 = 2;
			break;
		case'f':
			if (YCOUNT2 == 0)
			{
				glutTimerFunc(100, FRONTmove, 1);
			}
			YCOUNT2 = 1;
			break;
		case'F':
			if (YCOUNT2 == 0)
			{
				glutTimerFunc(100, FRONTmove, 1);
			}
			YCOUNT2 = 2;

			break;

		case'o':
			if (YCOUNT1 == 0)
			{
				glutTimerFunc(100, TriR, 1);
			}
			YCOUNT1 = 1;
			break;
		case'O':
			if (YCOUNT1 == 0)
			{
				glutTimerFunc(100, TriR, 1);
			}
			YCOUNT1 = 2;
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






