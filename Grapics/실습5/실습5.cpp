#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <ctime>
#include <stdint.h>
GLvoid drawScene(GLvoid);
GLvoid drawRect();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
int count = 0;
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);
bool left_button = false;
double max = 32767;
GLfloat x_p;
GLfloat y_p;
GLfloat COLOR[300] = { 0 };
GLfloat POS[200] = { 0 };
GLfloat R_x1 = -0.15f;
GLfloat R_y1 = -0.15f;
GLfloat R_x2 = 0.15f;
GLfloat R_y2 = 0.15f;


void main(int argc, char** argv)
{
	srand(time(NULL));
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(500, 500); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성

		//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	

	x_p = (GLfloat)(rand() / max);
	y_p = (GLfloat)(rand() / max);



	glutMainLoop();

}
GLvoid drawScene()
{
	glClearColor(1, 1, 1, 1.0f);  // 설정된 색으로 전체를 칠하기
	glClear(GL_COLOR_BUFFER_BIT);
	drawRect();
	glutSwapBuffers();
}
GLvoid drawRect()
{       
	if (count == 0)
	{


		x_p = (GLfloat)(rand() / max);
		y_p = (GLfloat)(rand() / max);

		int j = 0;
		for (int i = 0; i < 298; i = i + 3)
		{

			COLOR[i] = (GLfloat)((rand() / (max / 2)) - 1);
			COLOR[i + 1] = (GLfloat)((rand() / (max / 2)) - 1);
			COLOR[i + 2] = (GLfloat)((rand() / (max / 2)) - 1);

			glColor3f(COLOR[i], COLOR[i + 1], COLOR[i + 2]);
			if (i < 198)
			{
				POS[j] = (GLfloat)(rand() / (max / 2));
				POS[j + 1] = (GLfloat)(rand() / (max / 2));
				glRectf(-1 + POS[j], -1 + POS[j + 1], -0.8 + POS[j], -0.8 + POS[j + 1]);
				j += 2;
			}
		}
		count++;
	}
	else
	{
		int j = 0;
		for (int i = 0; i < 298; i = i + 3)
		{

		

			glColor3f(COLOR[i], COLOR[i + 1], COLOR[i + 2]);
			if (i < 198)
			{
				
				glRectf(-1 + POS[j], -1 + POS[j + 1], -0.8 + POS[j], -0.8 + POS[j + 1]);
				j += 2;
			}
		}

		if (left_button == true)
		{
			glColor3f(0.2, 0.2, 0.2);
			glRectf(R_x1, R_y1, R_x2, R_y2);
		}
	}

}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		left_button = true;
		
	}
	else
	{
		left_button = false;
		
	}

}
void Motion(int x, int y)
{
	if (left_button == true)
	{

		if (x >= 250)
		{
			R_x1 = -0.15 + (x - 250.0) / 250.0;
			R_x2 = 0.15 + (x - 250.0) / 250.0;
			if (y >= 250)
			{

				R_y1 = -0.15 - (y - 250.0) / 250.0;
				R_y2 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y1 = -0.15 + 1 - y / 250.0;
				R_y2 = 0.15 + 1 - y / 250.0;

			}
		}
		else if (0 < x && x < 250)
		{
			R_x1 = -0.15 - 1.0 + x / 250.0;
			R_x2 = 0.15 - 1.0 + x / 250.0;
			if (y >= 250)
			{

				R_y1 = -0.15 - (y - 250.0) / 250.0;
				R_y2 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y1 = -0.15 + 1 - y / 250.0;
				R_y2 = 0.15 + 1 - y / 250.0;

			}
		}
		
		int j = 0;
		for (int i = 0; i < 298; i = i + 3)
		{
			

			if ((-1 + POS[j]) <= R_x2 && (-0.8 + POS[j]) >=R_x1 && (-0.8 + POS[j + 1])>= R_y1 && (-1 + POS[j + 1])<= R_y2)
			{
				COLOR[i] = 1;
				COLOR[i+1] = 1;
				COLOR[i+2] = 1;
			}
			if (i < 198)
			{


				j += 2;
			}
		}

	}

	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		count = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
	default:
		break;
	}


	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}
