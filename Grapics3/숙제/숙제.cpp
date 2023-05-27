// Reading Obj file
#define  _CRT_SECURE_NO_WARNINGS


#include "shader.h"
#include "objRead.h"
#include <conio.h>

using namespace std;
int update = 0;
int COUNT = 0;
int hflag = 1;
int SH_COUNT = 2;
GLuint g_window_w = 960;
GLuint g_window_h = 960;

GLfloat TX = 0.0f;
GLfloat TY = 0.0f;
GLfloat TZ = 0.0f;


GLuint VAO[10];
GLuint VBO[3];
GLuint VBO1[3];
GLuint VBO2[3];
GLuint VBO3[3];





int Down_flag = 0;
int CUBE_flag = 0;
int Camera_flag = 1;
int input_number_X = 15;
int input_number_Y = 15;
int Max_input = 8100;
int total = input_number_X * input_number_Y * 36;
int polygon_mode = 1;


GLfloat xPos = 0.0f;
GLfloat yPos = 0.3f;
GLfloat zPos = 0.3f;


void Display();
void Display_Camera();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();
void PrintScreen();

GLfloat testCUBE[8100][3] = {
	//0x0
	{0,0,0}
};

GLfloat testColor[8100][3] = {
	//0x0
	{ 0,0,0},
};

int K = 0;
void Cubevalue()
{
	for(int i = 0; i < input_number_Y; i++)
	{
		for (int j = 0; j < input_number_X; j++)
		{
			testCUBE[36 * K][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 1][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 1][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 2][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 2][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 3][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 3][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 4][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 4][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 5][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 5][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 6][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 6][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 7][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 7][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 8][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 8][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 9][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 9][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 10][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 10][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 11][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 11][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 12][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 12][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 13][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 13][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 14][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 14][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 15][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 15][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 16][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 16][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 17][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 17][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 18][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 18][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 19][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 19][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 20][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 20][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 21][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 21][2] = -5 + i * (10.0 / input_number_Y);


			testCUBE[36 * K + 22][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 22][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 23][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 23][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 24][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 24][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 25][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 25][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 26][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 26][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 27][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 27][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 28][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 28][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 29][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 29][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 30][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 30][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 31][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 31][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 32][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 32][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K + 33][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 33][2] = -5 + i * (10.0 / input_number_Y);

			testCUBE[36 * K + 34][0] = -5 + j * (10.0 / input_number_X);
			testCUBE[36 * K + 34][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);


			testCUBE[36 * K + 35][0] = -5 + j * (10.0 / input_number_X) + (10.0 / input_number_X);
			testCUBE[36 * K + 35][2] = -5 + i * (10.0 / input_number_Y) + (10.0 / input_number_Y);

			testCUBE[36 * K][1] = 2;
			testCUBE[36 * K + 1][1] = 1;
			testCUBE[36 * K + 2][1] = 1;
			testCUBE[36 * K + 3][1] = 2;
			testCUBE[36 * K + 4][1] = 1;
			testCUBE[36 * K + 5][1] = 2;
			testCUBE[36 * K + 6][1] = 1;
			testCUBE[36 * K + 7][1] = 1;
			testCUBE[36 * K + 8][1] = 1;
			testCUBE[36 * K + 9][1] = 1;
			testCUBE[36 * K + 10][1] = 1;
			testCUBE[36 * K + 11][1] = 1;
			testCUBE[36 * K + 12][1] = 1;
			testCUBE[36 * K + 13][1] = 2;
			testCUBE[36 * K + 14][1] = 2;
			testCUBE[36 * K + 15][1] = 1;
			testCUBE[36 * K + 16][1] = 2;
			testCUBE[36 * K + 17][1] = 1;
			testCUBE[36 * K + 18][1] = 1;
			testCUBE[36 * K + 19][1] = 2;
			testCUBE[36 * K + 20][1] = 1;
			testCUBE[36 * K + 21][1] = 2;
			testCUBE[36 * K + 22][1] = 2;
			testCUBE[36 * K + 23][1] = 1;
			testCUBE[36 * K + 24][1] = 1;
			testCUBE[36 * K + 25][1] = 2;
			testCUBE[36 * K + 26][1] = 1;
			testCUBE[36 * K + 27][1] = 2;
			testCUBE[36 * K + 28][1] = 2;
			testCUBE[36 * K + 29][1] = 1;
			testCUBE[36 * K + 30][1] = 2;
			testCUBE[36 * K + 31][1] = 2;
			testCUBE[36 * K + 32][1] = 2;
			testCUBE[36 * K + 33][1] = 2;
			testCUBE[36 * K + 34][1] = 2;
			testCUBE[36 * K + 35][1] = 2;
			K++;
		}
	}

	K = 0;

}

void CubeColor()
{
	for (int i = 0; i < input_number_X * input_number_Y; i++)
	{
		GLfloat R = (GLfloat)rand() / RAND_MAX;
		GLfloat B = (GLfloat)rand() / RAND_MAX;
		GLfloat G = (GLfloat)rand() / RAND_MAX;

		for (int j = 0; j < 36; j++)
		{
			testColor[36 * i + j][0] = R;
			testColor[36 * i + j][1] = G;
			testColor[36 * i + j][2] = B;
		}


		//testColor[i][0] = 0.52;
		//testColor[i][1] = 0.80;
		//testColor[i][2] = 0.98;
	}
}
//바닥
GLfloat Floor[6][3] = {


	{-5,0,5},{5,0,-5},{-5,0,-5},
	{-5,0,5},{5,0,5},{5,0,-5},
};
//바닥 색깔
GLfloat Floor_Color[6][3] = {


	{1,0.98,0.98},
	{1,0.98,0.98},
	{1,0.98,0.98},
	{1,0.98,0.98},
	{1,0.98,0.98},
	{1,0.98,0.98}
};


GLfloat CUBE[36][3] = {

	{-4.5,0.5, -5},
	{-4.5,0,-5},
	{-5,0,-5},
	{-4.5,0.5,-5},
	{-5,0,-5},
	{-5,0.5,-5},
	{-4.5,0,-5},
	{-4.5,0,-4.5},
	{-5,0,-4.5},
	{-4.5,0,-5},
	{-5,0,-4.5},
	{-5,0,-5},
	{-5,0,-4.5},
	{-5,0.5,-4.5},
	{-5,0.5,-5},
	{-5,0,-4.5},
	{-5,0.5,-5},
	{-5,0,-5},
	{-4.5,0,-5},
	{-4.5,0.5,-5},
	{-4.5,0,-4.5},
	{-4.5,0.5,-5},
	{-4.5,0.5,-4.5},
	{-4.5,0,-4.5},
	{-4.5,0,-4.5},
	{-4.5,0.5,-4.5},
	{-5,0,-4.5},
	{-4.5,0.5,-4.5},
	{-5,0.5,-4.5},
	{-5,0,-4.5},
	{-4.5,0.5,-5},
	{-5,0.5,-5},
	{-4.5,0.5,-4.5},
	{-5,0.5, -5},
	{-5,0.5,-4.5},
	{-4.5,0.5,-4.5},
};


GLfloat CUBECOPY[36][3] = {

	{-4.5,0.5, -5},
	{-4.5,0,-5},
	{-5,0,-5},
	{-4.5,0.5,-5},
	{-5,0,-5},
	{-5,0.5,-5},
	{-4.5,0,-5},
	{-4.5,0,-4.5},
	{-5,0,-4.5},
	{-4.5,0,-5},
	{-5,0,-4.5},
	{-5,0,-5},
	{-5,0,-4.5},
	{-5,0.5,-4.5},
	{-5,0.5,-5},
	{-5,0,-4.5},
	{-5,0.5,-5},
	{-5,0,-5},
	{-4.5,0,-5},
	{-4.5,0.5,-5},
	{-4.5,0,-4.5},
	{-4.5,0.5,-5},
	{-4.5,0.5,-4.5},
	{-4.5,0,-4.5},
	{-4.5,0,-4.5},
	{-4.5,0.5,-4.5},
	{-5,0,-4.5},
	{-4.5,0.5,-4.5},
	{-5,0.5,-4.5},
	{-5,0,-4.5},
	{-4.5,0.5,-5},
	{-5,0.5,-5},
	{-4.5,0.5,-4.5},
	{-5,0.5, -5},
	{-5,0.5,-4.5},
	{-4.5,0.5,-4.5},
};

GLfloat CUBE_Color[36][3] = {
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




//objRead objReader3; //SPHERE2
//GLint Object3 = objReader3.loadObj_normalize_center3("sphere1.obj");
void Downcube(int value)
{
	if (testCUBE[0][1] > 1)
	{
		for (int i = 0; i < total; ++i)
		{
			testCUBE[i][1] -= 0.1f;

		}

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
		glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
		GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
		glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute1);

		glutPostRedisplay();
		glutTimerFunc(100, Downcube, 1);
	}
	else {
		Down_flag = 1; 
	}


}

int main(int argc, char** argv)
{
	// create window using freeglut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_window_w, g_window_h);
	glutInitWindowPosition(0, 0);

	srand(time(NULL));


		printf("가로를 입력하세요(5~15):");
		scanf_s("%d", &input_number_X);
		if (input_number_X > 15 || input_number_X < 5)
		{
			printf("올바른 범위가 아닙니다.");
			return 0;
		}
		printf("세로를 입력하세요(5~15):");
		scanf_s("%d", &input_number_Y);

		if (input_number_Y > 15 || input_number_Y < 5)
		{
			printf("올바른 범위가 아닙니다.");
			return 0;
		}
		Cubevalue();
		CubeColor();


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


	PrintScreen();
	//////////////////////////////////////////////////////////////////////////////////////
	//// Create shader program an register the shader
	//////////////////////////////////////////////////////////////////////////////////////

	GLuint vShader[10];
	GLuint fShader[10];

	vShader[0] = MakeVertexShader("vertex.glsl", 0);			// Sun
	fShader[0] = MakeFragmentShader("fragment.glsl", 0);

	// shader Program
	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vShader[0]);
	glAttachShader(s_program[0], fShader[0]);

	glLinkProgram(s_program[0]);
	checkCompileErrors(s_program[0], "PROGRAM");

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


	// 2 triangles for quad floor
	glUseProgram(s_program[0]);
	// 바닥!
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Floor, GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Floor_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
	glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2[1]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);


	//-------------------------------------------------------------------------------








}


void Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glFrontFace(GL_CCW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	if (Down_flag == 0)
	{
		glutTimerFunc(100, Downcube, 1);
	}


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
	S = glm::scale(S, glm::vec3(0.3, 0.3, 0.3));

	model = glm::translate(model, glm::vec3(TX, TY, TZ));

	Rz = glm::rotate(Rz, glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));
	Rz2 = glm::rotate(Rz2, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));

	RR = model * Rz2 * Rz * S;

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(RR));




	Display_Camera();
	//glutSwapBuffers();

}

GLfloat pPro = -5;
GLfloat pPro1 = 5;
int PRO_Flag = 0;

GLfloat CxPos = 0.55f;
GLfloat CyPos = 0.1f;
GLfloat CzPos = 0.4f;

GLfloat CxVis = 0.5f;
GLfloat CyVis = 0.1f;
GLfloat CzVis = 0.0f;
void Display_Camera()
{
	glViewport(0, 0, 960, 960);
	if (Camera_flag == 0)
	{
		
		glUseProgram(s_program[0]);
		
		glm::vec3 cameraPos2 = glm::vec3(CxPos, CyPos, CzPos); //--- 카메라 위치
		glm::vec3 cameraDirection2 = glm::vec3(CxVis, CyVis, CzVis); //--- 카메라 바라보는 방향
		glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
		glm::mat4 view2 = glm::mat4(1.0f);

		view2 = glm::lookAt(cameraPos2, cameraDirection2, cameraUp2);
		unsigned int viewLocation2 = glGetUniformLocation(s_program[0], "viewTransform"); //--- 뷰잉 변환 설정
		glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, &view2[0][0]);
		glm::mat4 projection2 = glm::mat4(1.0f);
		if (PRO_Flag == 1)
		{
			projection2 = glm::ortho(pPro, pPro1, pPro, pPro1, pPro, pPro1);
		}
		else if (PRO_Flag == 0)
		{
			projection2 = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
			projection2 = glm::translate(projection2, glm::vec3(0.0, 0.0, -5.0));


		}


		unsigned int projectionLocation2 = glGetUniformLocation(s_program[0], "projectionTransform"); //--- 투영 변환 값 설정
		glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection2[0][0]);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, total);

		if (CUBE_flag == 1)
		{
			glBindVertexArray(VAO[2]);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
	}
	else
	{
		glUseProgram(s_program[0]);
		glm::vec3 cameraPos = glm::vec3(xPos, yPos, zPos); //--- 카메라 위치
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
			projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));


		}


		unsigned int projectionLocation = glGetUniformLocation(s_program[0], "projectionTransform"); //--- 투영 변환 값 설정
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, total);

		if (CUBE_flag == 1)
		{
			glBindVertexArray(VAO[2]);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}


	}

	
	glViewport(800, 800, 160, 160);

	glUseProgram(s_program[0]);
	glm::vec3 cameraPos1 = glm::vec3(xPos, 0.5f, 0.1f); //--- 카메라 위치
	glm::vec3 cameraDirection1 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp1 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view1 = glm::mat4(1.0f);

	view1 = glm::lookAt(cameraPos1, cameraDirection1, cameraUp1);
	unsigned int viewLocation1 = glGetUniformLocation(s_program[0], "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation1, 1, GL_FALSE, &view1[0][0]);
	glm::mat4 projection1 = glm::mat4(1.0f);
	if (PRO_Flag == 1)
	{
		projection1 = glm::ortho(pPro, pPro1, pPro, pPro1, pPro, pPro1);
	}
	else if (PRO_Flag == 0)
	{
		projection1 = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		projection1 = glm::translate(projection1, glm::vec3(0.0, 0.0, -5.0));


	}


	unsigned int projectionLocation1 = glGetUniformLocation(s_program[0], "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation1, 1, GL_FALSE, &projection1[0][0]);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, total);

	if (CUBE_flag == 1)
	{
		glBindVertexArray(VAO[2]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}



	glutSwapBuffers();

}

int C_YROCOUNT = 0;
int CY_flag = 1;
int CY_flag1 = 1;
void C_YRO(int index) // y/Y부터!!!!!!!
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

	glutPostRedisplay();
	glutTimerFunc(100, C_YRO, 1);
}
int K1 = 0;
int random_flag = 10;
int Random_ONE = 0;

GLfloat randomMax[8100] = { 0 };
GLfloat randomy[8100] = { 0 };
int Random_Flag[8100] = { 0 };
void Cuberandom(int value)
{
	
	if (random_flag == 1)
	{
		for (int i = 0; i < input_number_Y; i++)
		{
			for (int j = 0; j < input_number_X; j++)
			{
				if (Random_ONE == 0)
				{
					randomMax[K1] = rand() % 3 + 2.0;
					//cout << randomMax[K1] << endl;
					randomy[K1] = (GLfloat)rand() / RAND_MAX;
					//cout << randomy[K1] << endl;
					//if (testCUBE[36 * K1][1] < randomMax[K1] == TRUE)
					//{
					//	printf("맞아염");
					//}
				}
				if (testCUBE[36 * K1][1] < randomMax[K1] && Random_Flag[K1] == 0)
				{
					testCUBE[36 * K1][1] += randomy[K1];

					testCUBE[36 * K1 + 3][1] += randomy[K1];		
					testCUBE[36 * K1 + 5][1] += randomy[K1];	
					testCUBE[36 * K1 + 13][1] += randomy[K1];
					testCUBE[36 * K1 + 14][1] += randomy[K1];			
					testCUBE[36 * K1 + 16][1] += randomy[K1];			
					testCUBE[36 * K1 + 19][1] += randomy[K1];			
					testCUBE[36 * K1 + 21][1] += randomy[K1];
					testCUBE[36 * K1 + 22][1] += randomy[K1];			
					testCUBE[36 * K1 + 25][1] += randomy[K1];			
					testCUBE[36 * K1 + 27][1] += randomy[K1];
					testCUBE[36 * K1 + 28][1] += randomy[K1];	
					testCUBE[36 * K1 + 30][1] += randomy[K1];
					testCUBE[36 * K1 + 31][1] += randomy[K1];
					testCUBE[36 * K1 + 32][1] += randomy[K1];
					testCUBE[36 * K1 + 33][1] += randomy[K1];
					testCUBE[36 * K1 + 34][1] += randomy[K1];
					testCUBE[36 * K1 + 35][1] += randomy[K1];
				}
				else if(testCUBE[36 * K1][1] >= randomMax[K1])
				{
					Random_Flag[K1] = 1;
				}
				if (Random_Flag[K1] == 1 )
				{
					testCUBE[36 * K1][1] -= randomy[K1];
					testCUBE[36 * K1 + 3][1] -= randomy[K1];
					testCUBE[36 * K1 + 5][1] -= randomy[K1];
					testCUBE[36 * K1 + 13][1] -= randomy[K1];
					testCUBE[36 * K1 + 14][1] -= randomy[K1];
					testCUBE[36 * K1 + 16][1] -= randomy[K1];
					testCUBE[36 * K1 + 19][1] -= randomy[K1];
					testCUBE[36 * K1 + 21][1] -= randomy[K1];
					testCUBE[36 * K1 + 22][1] -= randomy[K1];
					testCUBE[36 * K1 + 25][1] -= randomy[K1];
					testCUBE[36 * K1 + 27][1] -= randomy[K1];
					testCUBE[36 * K1 + 28][1] -= randomy[K1];
					testCUBE[36 * K1 + 30][1] -= randomy[K1];
					testCUBE[36 * K1 + 31][1] -= randomy[K1];
					testCUBE[36 * K1 + 32][1] -= randomy[K1];
					testCUBE[36 * K1 + 33][1] -= randomy[K1];
					testCUBE[36 * K1 + 34][1] -= randomy[K1];
					testCUBE[36 * K1 + 35][1] -= randomy[K1];

					if (testCUBE[36 * K1][1] <= 2)
					{
						Random_Flag[K1] = 0;
					}
				}

				K1++;
			}
		}
		Random_ONE = 1;
		K1 = 0;

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
		glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
		GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
		glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(pAttribute1);
	}


	glutPostRedisplay();
	glutTimerFunc(100, Cuberandom, 1);
}




//미로 리셋
void Reset_miro()
{   
	int K = 0;
	int Flag = 0;
	int miroflag = 1;
	for (int i = 0; i < 36; i++)
	{
		testCUBE[i][0] = 0.0f;
		testCUBE[i][1] = 0.0f;
		testCUBE[i][2] = 0.0f;
		if (i == 35)
		{
			K++;
		}
	}
	while (Flag == 0)
	{
		for (int j = 0; j < input_number_X; ++j)
		{
			for (int i = 0; i < 36; i++)
			{

				if (total - 36 * input_number_X <= 36 * K * input_number_X)
				{
					Flag = 1;
					break;
				}
				testCUBE[36 * K * input_number_X + (36 * j) + i][0] = 0.0f;
				testCUBE[36 * K * input_number_X + (36 * j) + i][1] = 0.0f;
				testCUBE[36 * K * input_number_X + (36 * j) + i][2] = 0.0f;

				if (j == input_number_X - 1 && i == 35)
				{
					if (total - 1 == 36 * K * input_number_X + (36 * j) + i || total - 36 * input_number_X  == 36 * K * input_number_X )
					{
						Flag = 1;
					}
					if (total - 1 == 36 * (K + 1) * input_number_X + (36 * j) + i)
					{
						for (int p = 0; p < 36; p++)
						{
							testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][0] = 0.0f;
							testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][1] = 0.0f;
							testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][2] = 0.0f;
						}


						Flag = 1;
					}
					else
					{
						if (miroflag == 1)
						{
							for (int p = 0; p < 36; p++)
							{
								testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][0] = 0.0f;
								testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][1] = 0.0f;
								testCUBE[36 * (K + 1) * input_number_X + (36 * j) + p][2] = 0.0f;
							}
						}
						else
						{
							for (int p = 0; p < 36; p++)
							{
								testCUBE[36 * (K + 1) * input_number_X  + p][0] = 0.0f;
								testCUBE[36 * (K + 1) * input_number_X  + p][1] = 0.0f;
								testCUBE[36 * (K + 1) * input_number_X  + p][2] = 0.0f;
							}
						}


					}
					if (total - 1 == 36 * (K + 2) * input_number_X + (36 * j) + i)
					{
						for (int p = 0; p < 36; p++)
						{
							testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][0] = 0.0f;
							testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][1] = 0.0f;
							testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][2] = 0.0f;
						}


						Flag = 1;
					}
					else
					{
						if (miroflag == 1)
						{
							for (int p = 0; p < 36; p++)
							{
								testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][0] = 0.0f;
								testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][1] = 0.0f;
								testCUBE[36 * (K + 2) * input_number_X + (36 * j) + p][2] = 0.0f;
							}
						}
						else
						{
							for (int p = 0; p < 36; p++)
							{
								testCUBE[36 * (K + 2) * input_number_X + p][0] = 0.0f;
								testCUBE[36 * (K + 2) * input_number_X + p][1] = 0.0f;
								testCUBE[36 * (K + 2) * input_number_X + p][2] = 0.0f;
							}
						}
					}
				}
			}
		}
		K += 2;
		if (miroflag == 1)
		{
			miroflag = 0;

		}
		else
		{
			miroflag = 1;
		}
	}

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);


}
int K2 = 0;
void stopmove()
{

	for (int i = 0; i < input_number_Y; i++)
	{
		for (int j = 0; j < input_number_X; j++)
		{
			if (testCUBE[36 * K2][1] != 0)
			{
				testCUBE[36 * K2][1] = 1;
				testCUBE[36 * K2 + 1][1] = 0;
				testCUBE[36 * K2 + 2][1] = 0;
				testCUBE[36 * K2 + 3][1] = 1;
				testCUBE[36 * K2 + 4][1] = 0;
				testCUBE[36 * K2 + 5][1] = 1;
				testCUBE[36 * K2 + 6][1] = 0;
				testCUBE[36 * K2 + 7][1] = 0;
				testCUBE[36 * K2 + 8][1] = 0;
				testCUBE[36 * K2 + 9][1] = 0;
				testCUBE[36 * K2 + 10][1] = 0;
				testCUBE[36 * K2 + 11][1] = 0;
				testCUBE[36 * K2 + 12][1] = 0;
				testCUBE[36 * K2 + 13][1] = 1;
				testCUBE[36 * K2 + 14][1] = 1;
				testCUBE[36 * K2 + 15][1] = 0;
				testCUBE[36 * K2 + 16][1] = 1;
				testCUBE[36 * K2 + 17][1] = 0;
				testCUBE[36 * K2 + 18][1] = 0;
				testCUBE[36 * K2 + 19][1] = 1;
				testCUBE[36 * K2 + 20][1] = 0;
				testCUBE[36 * K2 + 21][1] = 1;
				testCUBE[36 * K2 + 22][1] = 1;
				testCUBE[36 * K2 + 23][1] = 0;
				testCUBE[36 * K2 + 24][1] = 0;
				testCUBE[36 * K2 + 25][1] = 1;
				testCUBE[36 * K2 + 26][1] = 0;
				testCUBE[36 * K2 + 27][1] = 1;
				testCUBE[36 * K2 + 28][1] = 1;
				testCUBE[36 * K2 + 29][1] = 0;
				testCUBE[36 * K2 + 30][1] = 1;
				testCUBE[36 * K2 + 31][1] = 1;
				testCUBE[36 * K2 + 32][1] = 1;
				testCUBE[36 * K2 + 33][1] = 1;
				testCUBE[36 * K2 + 34][1] = 1;
				testCUBE[36 * K2 + 35][1] = 1;
			}
			
			K2++;
		}
	}

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBufferData(GL_ARRAY_BUFFER, input_number_X * input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
	GLint pAttribute1 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute1);
	K2 = 0;
}

GLfloat Move = 0.25f;

void CUBE_LEFT()
{
	
	for (int i = 0; i < 36; ++i)
	{
		CUBE[i][0] -= Move;
	}
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

}
void CUBE_RIGHT()
{

	for (int i = 0; i < 36; ++i)
	{
		CUBE[i][0] += Move;
	}
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

}

void CUBE_UP()
{

	for (int i = 0; i < 36; ++i)
	{
		CUBE[i][2] -= Move;
	}
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

}

void CUBE_DOWN()
{

	for (int i = 0; i < 36; ++i)
	{
		CUBE[i][2] += Move;
	}
	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[0]);
	glBufferData(GL_ARRAY_BUFFER, 36 * 3 * sizeof(GLfloat), CUBE, GL_STATIC_DRAW);
	GLint pAttribute2 = glGetAttribLocation(s_program[0], "aPos");
	glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute2);

}

void PrintScreen()
{
	printf("\n ========================================================================\n");
	printf("o/p: 투영을 선택한다. (o:직각투영/ p:원근투영)(기본은 원근투영)\n");
	printf("z/Z: 원근 투영 시 z축으로 이동할 수 있게 한다.\n");
	printf("m/M: 육면체들이 위아래로 움직인다./ 멈춘다.\n");
	printf("y/Y: 카메라가 바닥의 y축을 기준으로 양/음 방향으로 회전한다. 한번더 누르면 멈춘다.\n");
	printf("r: 미로를 제작한다.\n");
	printf("v: 육면체들 움직임이 멈추고 낮은 높이로 변한다 다시 누르면 움직임이 다시 시작된다\n");
	printf("s: 미로에서 객체가 나타난다. -> 객체를 소환하면 h(depthtest)를 눌러주세요\n");
	printf("4/6/8/5 좌/우/상/하로 객체가 이동한다.\n");
	printf("+/-: 육면체 이동하는 속도 증가/감소\n");
	printf("1/3: 카메라 시점 1인칭(*구현 실패*)/3인칭 변환\n");
	printf("c: 모든 값 초기화\n");
	printf("q: 프로그램 종료");
	printf("\n =================================기타====================================\n");
	printf("h: depth테스트 끄기/켜기(객체가 많이 깨지니 미로할때만 사용\n");
	printf("j/l/i/k: 좌/우/상/하로 1인칭 시점 (실패한) 화면 이동 1번을 눌러야 사용가능 \n");
	printf("\n ========================================================================\n");
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
	case'b':

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
	case'w':
		polygon_mode = 1;
		break;

	case'W':
		polygon_mode = 2;
		break;



	case'o':
		PRO_Flag = 1;
		break;
	case'p':
		PRO_Flag = 0;
		break;

	case'z':
		if (PRO_Flag == 0)
		{
			zPos += 0.1f;
		}

		break;
	case'Z':
		if (PRO_Flag == 0)
		{
			zPos -= 0.1f;
		}
		break;


	case'y':
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
	case'Y':
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

	case'm':
		if (random_flag == 10)
		{
			random_flag = 1;
			glutTimerFunc(100, Cuberandom, 1);
		}
		random_flag = 1;

		break;
	case'M':
		if (random_flag != 10)
		{
			random_flag = 0;
		}
		break;

	case'r':
		Reset_miro();
		break;

	case'v':
		if (random_flag == 1)
		{
			stopmove();
			random_flag = 0;

		}
		else 
		{
			random_flag = 1;
		}
		break;
	case's':
		CUBE_flag = 1;
		break;

	case'4':
		CUBE_LEFT();
		
		break;
	case'6':
		CUBE_RIGHT();

		break;
	case'8':
		CUBE_UP();

		break;
	case'5':
		CUBE_DOWN();

		break;

	case'+':
		if (Move < 0.5f)
		{
			Move += 0.05f;
		}
		else
		{
			printf("이 이상은 한계입니다.\n");
		}


		break;
	case'-':
		if (Move > 0.1f)
		{
			Move -= 0.05f;
		}
		else
		{
			printf("너무 느려 답답합니다.\n");
		}

		

		break;
	case'1':

		Camera_flag = 0;
		break;
	case'3':

		Camera_flag = 1;

		break;
	case'i':
		CzPos += 0.1f;
		break;
	case'k':
		CzPos -= 0.1f;
		break;
	case'j':
		CxPos -= 0.1f;
		break;
	case'l':

		CxPos += 0.1f;
		break;

	case'c':

		update = 0;
		COUNT = 0;
		hflag = 1;
		SH_COUNT = 0;
		polygon_mode = 1;
		PRO_Flag = 0;

		Down_flag = 0;
		CUBE_flag = 0;
		Camera_flag = 1;
		input_number_X = 15;
		input_number_Y = 15;
		xPos = 0.0f;
		yPos = 0.3f;
		zPos = 0.3f;

		C_YROCOUNT = 10;
		CY_flag = 1;
		CY_flag1 = 1;
		random_flag = 2;

		K = 0;
		K1 = 0;
		K2 = 0;
		Random_ONE = 0;
		//randomMax[8100] = { 0 };
		//randomy[8100] = { 0 };
		//Random_Flag[8100] = { 0 };


		Move = 0.25f;

		for (int i = 0; i < 36; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				CUBE[i][j] = CUBECOPY[i][j];
			}
		}

		

		printf("가로를 입력하세요(5~15):");
		scanf_s("%d", &input_number_X);
		if (input_number_X > 15 || input_number_X < 5)
		{
			printf("올바른 범위가 아닙니다.");
			return;
		}
		printf("세로를 입력하세요(5~15):");
		scanf_s("%d", &input_number_Y);

		if (input_number_Y > 15 || input_number_Y < 5)
		{
			printf("올바른 범위가 아닙니다.");
			return;
		}
		cout << input_number_X << endl;
		cout << input_number_Y << endl;
		Cubevalue();
		CubeColor();

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
		glBufferData(GL_ARRAY_BUFFER, input_number_X* input_number_Y * 36 * 3 * sizeof(GLfloat), testCUBE, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO1[1]);
		glBufferData(GL_ARRAY_BUFFER, input_number_X* input_number_Y * 36 * 3 * sizeof(GLfloat), testColor, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);

		PrintScreen();
		break;
	case'q':
		glutLeaveMainLoop();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}






