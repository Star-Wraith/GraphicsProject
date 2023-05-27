#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <ctime>

int count = 0;
int COUNT = 0;
GLvoid drawScene(GLvoid);
GLvoid drawRect();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
//void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);
void DG_func(int value);
void ZIG_func(int value);

//bool left_button = false;
GLfloat R_x1 = -0.15f;
GLfloat R_y1 = -0.15f;
GLfloat R_x2 = 0.15f;
GLfloat R_y2 = 0.15f;
GLfloat R_x11 = -0.15f;
GLfloat R_y11 = -0.15f;
GLfloat R_x21 = 0.15f;
GLfloat R_y21 = 0.15f;
GLfloat R_x12 = -0.15f;
GLfloat R_y12 = -0.15f;
GLfloat R_x22 = 0.15f;
GLfloat R_y22 = 0.15f;
GLfloat R_x13 = -0.15f;
GLfloat R_y13 = -0.15f;
GLfloat R_x23 = 0.15f;
GLfloat R_y23 = 0.15f;
GLfloat R_x14 = -0.15f;
GLfloat R_y14 = -0.15f;
GLfloat R_x24 = 0.15f;
GLfloat R_y24 = 0.15f;
GLfloat R1, R2, R3, R4, R5;
GLfloat G1, G2, G3, G4, G5;
GLfloat B1, B2, B3, B4, B5;
GLfloat X1, X11, X12, X13, X14, Y1, Y11, Y12, Y13, Y14, X2, X21, X22, X23, X24, Y2, Y21, Y22, Y23, Y24;



int Dg_flag = 1;
int DG_key = 1;
int Zig_flag = 1;
int ZIG_key = 1;
int Form_flag = 1;
int FORM_key = 1;
int D_flag = 1;
int D_flag1 = 1;
int D_flag2 = 1;
int D_flag3 = 1;
int D_flag4 = 1;
int Z_flag = 1;
int Z_flag1 = 1;
int Z_flag2 = 1;
int Z_flag3 = 1;
int Z_flag4 = 1;
int Z_switch = 1;
int Z_switch1 = 1;
int Z_switch2 = 1;
int Z_switch3 = 1;
int Z_switch4 = 1;

void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
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
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);

	glutMainLoop();

}

GLvoid drawScene()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // 설정된 색으로 전체를 칠하기
	glClear(GL_COLOR_BUFFER_BIT);
	drawRect();
	glutSwapBuffers();
}
GLvoid drawRect()
{
	
	if (count == 1)
	{
		R1 = rand() % 2;
		G1 = rand() % 2;
		B1 = rand() % 2;
		glColor3f(R1, G1, B1);
		glRectf(R_x1, R_y1, R_x2, R_y2);
	}
	else if (count == 2)
	{
		glColor3f(R1, G1, B1);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		R2 = rand() % 2;
		G2 = rand() % 2;
		B2 = rand() % 2;
		glColor3f(R2, G2, B2);
		glRectf(R_x11, R_y11, R_x21, R_y21);

	}
	else if (count == 3)
	{
		glColor3f(R1, G1, B1);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(R2, G2, B2);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		R3 = rand() % 2;
		G3 = rand() % 2;
		B3 = rand() % 2;
		glColor3f(R3, G3, B3);
		glRectf(R_x12, R_y12, R_x22, R_y22);
	}
	else if (count == 4)
	{
		glColor3f(R1, G1, B1);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(R2, G2, B2);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		glColor3f(R3, G3, B3);
		glRectf(R_x12, R_y12, R_x22, R_y22);
		R4 = rand() % 2;
		G4 = rand() % 2;
		B4 = rand() % 2;
		glColor3f(R4, G4, B4);
		glRectf(R_x13, R_y13, R_x23, R_y23);
	}
	else if (count == 5)
	{
		glColor3f(R1, G1, B1);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(R2, G2, B2);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		glColor3f(R3, G3, B3);
		glRectf(R_x12, R_y12, R_x22, R_y22);
		glColor3f(R4, G4, B4);
		glRectf(R_x13, R_y13, R_x23, R_y23);

		glColor3f(R5, G5, B5);
		glRectf(R_x14, R_y14, R_x24, R_y24);
	}
	else if (count == 6)
	{
		glutLeaveMainLoop();
	}
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
void DG_func(int value)
{
	if (Dg_flag == 1)
	{
		if (D_flag == 1)
		{
			
				R_x1 = R_x1 + 0.03f;
				R_y1 = R_y1 + 0.03f;
				R_x2 = R_x2 + 0.03f;
				R_y2 = R_y2 + 0.03f;
			
			if (R_x2 >= 1 || R_y2 >= 1)
			{
				D_flag = 0;
			}

		}
		else if (D_flag == 0)
		{
			R_x1 = R_x1 - 0.03f;
			R_y1 = R_y1 - 0.03f;
			R_x2 = R_x2 - 0.03f;
			R_y2 = R_y2 - 0.03f;
			if (R_x1 <= -1 || R_y1 <= -1)
			{
				D_flag = 1;
			}
		}

		if (D_flag1 == 1)
		{
			R_x11 = R_x11 + 0.03f;
			R_y11 = R_y11 + 0.03f;
			R_x21 = R_x21 + 0.03f;
			R_y21 = R_y21 + 0.03f;

			if (R_x21 >= 1 || R_y21 >= 1)
			{
				D_flag1 = 0;
			}
		}
		else
		{
			R_x11 = R_x11 - 0.03f;
			R_y11 = R_y11 - 0.03f;
			R_x21 = R_x21 - 0.03f;
			R_y21 = R_y21 - 0.03f;
			if (R_x11 <= -1 || R_y11 <= -1)
			{
				D_flag1 = 1;
			}
		}

		if (D_flag2 == 1)
		{
			R_x12 = R_x12 + 0.03f;
			R_y12 = R_y12 + 0.03f;
			R_x22 = R_x22 + 0.03f;
			R_y22 = R_y22 + 0.03f;

			if (R_x22 >= 1 || R_y22 >= 1)
			{
				D_flag2 = 0;
			}
		}
		else
		{
			R_x12 = R_x12 - 0.03f;
			R_y12 = R_y12 - 0.03f;
			R_x22 = R_x22 - 0.03f;
			R_y22 = R_y22 - 0.03f;
			if (R_x12 <= -1 || R_y12 <= -1)
			{
				D_flag2 = 1;
			}
		}

		if (D_flag3 == 1)
		{
			R_x13 = R_x13 + 0.03f;
			R_y13 = R_y13 + 0.03f;
			R_x23 = R_x23 + 0.03f;
			R_y23 = R_y23 + 0.03f;

			if (R_x23 >= 1 || R_y23 >= 1)
			{
				D_flag3 = 0;
			}
		}
		else
		{
			R_x13 = R_x13 - 0.03f;
			R_y13 = R_y13 - 0.03f;
			R_x23 = R_x23 - 0.03f;
			R_y23 = R_y23 - 0.03f;
			if (R_x13 <= -1 || R_y13 <= -1)
			{
				D_flag3 = 1;
			}
		}

		if (D_flag4 == 1)
		{
			R_x14 = R_x14 + 0.03f;
			R_y14 = R_y14 + 0.03f;
			R_x24 = R_x24 + 0.03f;
			R_y24 = R_y24 + 0.03f;

			if (R_x24 >= 1 || R_y24 >= 1)
			{
				D_flag4 = 0;
			}
		}
		else
		{
			R_x14 = R_x14 - 0.03f;
			R_y14 = R_y14 - 0.03f;
			R_x24 = R_x24 - 0.03f;
			R_y24 = R_y24 - 0.03f;
			if (R_x14 <= -1 || R_y14 <= -1)
			{
				D_flag4 = 1;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(100, DG_func, 1);
	}
}
void ZIG_func(int value)
{
	if (Zig_flag == 1)
	{
		if (Z_flag == 1)
		{
			if (Z_switch == 1)
			{
			   
				R_x1 = R_x1 + 0.1f;
				R_y1 = R_y1 + 0.1f;
				R_x2 = R_x2 + 0.1f;
				R_y2 = R_y2 + 0.1f;
				Z_switch = 0;
			}
			else
			{
				R_x1 = R_x1 - 0.1f;
				R_y1 = R_y1 + 0.1f;
				R_x2 = R_x2 - 0.1f;
				R_y2 = R_y2 + 0.1f;
				Z_switch = 1;
			}
			if (R_x2 >= 1 || R_y2 >= 1)
			{
				
				Z_flag = 0;
			}

		}
		else
		{
			if (Z_switch == 1)
			{
				
				R_x1 = R_x1 + 0.1f;
				R_y1 = R_y1 - 0.1f;
				R_x2 = R_x2 + 0.1f;
				R_y2 = R_y2 - 0.1f;
			
				Z_switch = 0;
			}
			else
			{
				R_x1 = R_x1 - 0.1f;
				R_y1 = R_y1 - 0.1f;
				R_x2 = R_x2 - 0.1f;
				R_y2 = R_y2 - 0.1f;
				Z_switch = 1;
			}
			if (R_x1 <= -1 || R_y1 <= -1)
			{
				Z_flag = 1;
			}
		}

		if (Z_flag1 == 1)
		{
			if (Z_switch1 == 1)
			{
				R_x11 = R_x11 + 0.1f;
				R_y11 = R_y11 + 0.1f;
				R_x21 = R_x21 + 0.1f;
				R_y21 = R_y21 + 0.1f;
				Z_switch1 = 0;
			}
			else
			{
				R_x11 = R_x11 - 0.1f;
				R_y11 = R_y11 + 0.1f;
				R_x21 = R_x21 - 0.1f;
				R_y21 = R_y21 + 0.1f;
				Z_switch1 = 1;
			}
			if (R_x21 >= 1 || R_y21 >= 1)
			{
				Z_flag1 = 0;
			}
		}
		else
		{
			if (Z_switch1 == 1)
			{

				R_x11 = R_x11 + 0.1f;
				R_y11 = R_y11 - 0.1f;
				R_x21 = R_x21 + 0.1f;
				R_y21 = R_y21 - 0.1f;
				Z_switch1 = 0;
			}
			else
			{
				R_x11 = R_x11 - 0.1f;
				R_y11 = R_y11 - 0.1f;
				R_x21 = R_x21 - 0.1f;
				R_y21 = R_y21 - 0.1f;
				
				Z_switch1 = 1;
			}
			if (R_x11 <= -1 || R_y11 <= -1)
			{
				Z_flag1 = 1;
			}
		}

		if (Z_flag2 == 1)
		{
			if (Z_switch2 == 1)
			{
				R_x12 = R_x12 + 0.1f;
				R_y12 = R_y12 + 0.1f;
				R_x22 = R_x22 + 0.1f;
				R_y22 = R_y22 + 0.1f;
				Z_switch2 = 0;
			}
			else
			{
				R_x12 = R_x12 - 0.1f;
				R_y12 = R_y12 + 0.1f;
				R_x22 = R_x22 - 0.1f;
				R_y22 = R_y22 + 0.1f;
				Z_switch2 = 1;
			}
			if (R_x22 >= 1 || R_y22 >= 1)
			{
				Z_flag2 = 0;
			}
		}
		else
		{
			if (Z_switch2 == 1)
			{

				R_x12 = R_x12 + 0.1f;
				R_y12 = R_y12 - 0.1f;
				R_x22 = R_x22 + 0.1f;
				R_y22 = R_y22 - 0.1f;
				Z_switch2 = 0;
			}
			else
			{
				R_x12 = R_x12 - 0.1f;
				R_y12 = R_y12 - 0.1f;
				R_x22 = R_x22 - 0.1f;
				R_y22 = R_y22 - 0.1f;
				
				Z_switch2 = 1;
			}
			if (R_x12 <= -1 || R_y12 <= -1)
			{
				Z_flag2 = 1;
			}
		}

		if (Z_flag3 == 1)
		{
			if (Z_switch3 == 1)
			{
				R_x13 = R_x13 + 0.1f;
				R_y13 = R_y13 + 0.1f;
				R_x23 = R_x23 + 0.1f;
				R_y23 = R_y23 + 0.1f;
				Z_switch3 = 0;
			}
			else
			{
				R_x13 = R_x13 - 0.1f;
				R_y13 = R_y13 + 0.1f;
				R_x23 = R_x23 - 0.1f;
				R_y23 = R_y23 + 0.1f;
				Z_switch3 = 1;
			}
			if (R_x23 >= 1 || R_y23 >= 1)
			{
				Z_flag3 = 0;
			}
		}
		else
		{
			if (Z_switch3 == 1)
			{

				R_x13 = R_x13 + 0.1f;
				R_y13 = R_y13 - 0.1f;
				R_x23 = R_x23 + 0.1f;
				R_y23 = R_y23 - 0.1f;
				Z_switch3 = 0;
			}
			else
			{

				R_x13 = R_x13 - 0.1f;
				R_y13 = R_y13 - 0.1f;
				R_x23 = R_x23 - 0.1f;
				R_y23 = R_y23 - 0.1f;
				
				Z_switch3 = 1;
			}
			if (R_x13 <= -1 || R_y13 <= -1)
			{
				Z_flag3 = 1;
			}
		}

		if (Z_flag4 == 1)
		{
			if (Z_switch4 == 1)
			{
				R_x14 = R_x14 + 0.1f;
				R_y14 = R_y14 + 0.1f;
				R_x24 = R_x24 + 0.1f;
				R_y24 = R_y24 + 0.1f;
				Z_switch4 = 0;
			}
			else
			{
				R_x14 = R_x14 - 0.1f;
				R_y14 = R_y14 + 0.1f;
				R_x24 = R_x24 - 0.1f;
				R_y24 = R_y24 + 0.1f;
				Z_switch4 = 1;
			}
			if (R_x24 >= 1 || R_y24 >= 1)
			{
				Z_flag4 = 0;
			}
		}
		else
		{
			if (Z_switch4 == 1)
			{

				R_x14 = R_x14 + 0.1f;
				R_y14 = R_y14 - 0.1f;
				R_x24 = R_x24 + 0.1f;
				R_y24 = R_y24 - 0.1f;
				Z_switch4 = 0;
			}
			else
			{
				R_x14 = R_x14 - 0.1f;
				R_y14 = R_y14 - 0.1f;
				R_x24 = R_x24 - 0.1f;
				R_y24 = R_y24 - 0.1f;
				
				Z_switch4 = 1;
			}
			if (R_x14 <= -1 || R_y14 <= -1)
			{
				Z_flag4 = 1;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(100, ZIG_func, 2);
	}

}
void Form_fuc(int value)
{
	if (Form_flag == 1)
	{
		if (COUNT % 6 == 0)
		{
			R_x1 = R_x1 + 0.1f;
			R_y1 = R_y1 + 0.1f;

			R_x11 = R_x11 + 0.1f;
			R_y11 = R_y11 + 0.1f;


			R_x12 = R_x12 + 0.1f;
			R_y12 = R_y12 + 0.1f;
	

			R_x13 = R_x13 + 0.1f;
			R_y13 = R_y13 + 0.1f;
		

			R_x14 = R_x14 + 0.1f;
			R_y14 = R_y14 + 0.1f;
			

			++COUNT;
		}
		else if (COUNT % 6 == 1)
		{
			R_x1 = R_x1 - 0.1f;
			R_y1 = R_y1 - 0.1f;

			R_x11 = R_x11 - 0.1f;
			R_y11 = R_y11 - 0.1f;


			R_x12 = R_x12 - 0.1f;
			R_y12 = R_y12 - 0.1f;


			R_x13 = R_x13 - 0.1f;
			R_y13 = R_y13 - 0.1f;


			R_x14 = R_x14 - 0.1f;
			R_y14 = R_y14 - 0.1f;

			++COUNT;
		}
		else if (COUNT % 6 == 2)
		{
			R_x1 = R_x1 - 0.2f;
			R_y1 = R_y1 - 0.1f;
			R_x2 = R_x2 + 0.3f;
			R_y2 = R_y2 ;

			R_x11 = R_x11 - 0.2f;
			R_y11 = R_y11 - 0.1f;
			R_x21 = R_x21 + 0.3f;
			R_y21 = R_y21;

			R_x12 = R_x12 - 0.2f;
			R_y12 = R_y12 - 0.1f;
			R_x22 = R_x22 + 0.3f;
			R_y22 = R_y22;

			R_x13 = R_x13 - 0.2f;
			R_y13 = R_y13 - 0.1f;
			R_x23 = R_x23 + 0.3f;
			R_y23 = R_y23 ;

			R_x14 = R_x14 - 0.2f;
			R_y14 = R_y14 - 0.1f;
			R_x24 = R_x24 + 0.3f;
			R_y24 = R_y24;

			++COUNT;
		}
		else if (COUNT % 6 == 3)
		{
			R_x1 = R_x1 + 0.2f;
			R_y1 = R_y1 + 0.1f;
			R_x2 = R_x2 - 0.3f;
			R_y2 = R_y2;

			R_x11 = R_x11 + 0.2f;
			R_y11 = R_y11 + 0.1f;
			R_x21 = R_x21 - 0.3f;
			R_y21 = R_y21;

			R_x12 = R_x12 + 0.2f;
			R_y12 = R_y12 + 0.1f;
			R_x22 = R_x22 - 0.3f;
			R_y22 = R_y22;

			R_x13 = R_x13 + 0.2f;
			R_y13 = R_y13 + 0.1f;
			R_x23 = R_x23 - 0.3f;
			R_y23 = R_y23;

			R_x14 = R_x14 + 0.2f;
			R_y14 = R_y14 + 0.1f;
			R_x24 = R_x24 - 0.3f;
			R_y24 = R_y24;

			++COUNT;
		}
		else if (COUNT % 6 == 4)
		{
			R_x1 = R_x1 + 0.1f;
			R_y2 = R_y2 + 0.2f;

			R_x11 = R_x11 + 0.1f;
			R_y21 = R_y21 + 0.2f;

			R_x12 = R_x12 + 0.1f;
			R_y22 = R_y22 + 0.2f;

			R_x13 = R_x13 + 0.1f;
			R_y23 = R_y23 + 0.2f;

			R_x14 = R_x14 + 0.1f;
			R_y24 = R_y24 + 0.2f;
			++COUNT;
		}
		else if (COUNT % 6 == 5)
		{
		 R_x1 = R_x1 - 0.1f;
		 R_y2 = R_y2 - 0.2f;
		 
		 R_x11 = R_x11 - 0.1f;
		 R_y21 = R_y21 - 0.2f;

		 R_x12 = R_x12 - 0.1f;
		 R_y22 = R_y22 - 0.2f;

		 R_x13 = R_x13 - 0.1f;
		 R_y23 = R_y23 - 0.2f;

		 R_x14 = R_x14 - 0.1f;
		 R_y24 = R_y24 - 0.2f;
		++COUNT;
		}

		glutPostRedisplay();
		glutTimerFunc(600, Form_fuc, 3);

	}
}
void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON &&  state == GLUT_DOWN)
	{
		//left_button = true;
		std::cout << "x = " << x << "y = " << y << std::endl;
		++count;
		if (count == 1)
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
			X1 = R_x1;
			Y1 = R_y1;
			X2 = R_x2;
			Y2 = R_y2;
		}
		else if (count == 2)
		{
			if (x >= 250)
			{
				R_x11 = -0.15 + (x - 250.0) / 250.0;
				R_x21 = 0.15 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y11 = -0.15 - (y - 250.0) / 250.0;
					R_y21 = 0.15 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y11 = -0.15 + 1 - y / 250.0;
					R_y21 = 0.15 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x11 = -0.15 - 1.0 + x / 250.0;
				R_x21 = 0.15 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y11 = -0.15 - (y - 250.0) / 250.0;
					R_y21 = 0.15 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y11 = -0.15 + 1 - y / 250.0;
					R_y21 = 0.15 + 1 - y / 250.0;

				}
			}

			X11 = R_x11;
			Y11 = R_y11;
			X21 = R_x21;
			Y21 = R_y21;
		}
		else if (count == 3)
		{
			if (x >= 250)
			{
				R_x12 = -0.15 + (x - 250.0) / 250.0;
				R_x22 = 0.15 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y12 = -0.15 - (y - 250.0) / 250.0;
					R_y22 = 0.15 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y12 = -0.15 + 1 - y / 250.0;
					R_y22 = 0.15 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x12 = -0.15 - 1.0 + x / 250.0;
				R_x22 = 0.15 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y12 = -0.15 - (y - 250.0) / 250.0;
					R_y22 = 0.15 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y12 = -0.15 + 1 - y / 250.0;
					R_y22 = 0.15 + 1 - y / 250.0;

				}
			}
			X12 = R_x12;
			Y12 = R_y12;
			X22 = R_x22;
			Y22 = R_y22;
		}
		else if (count == 4)
		{
		if (x >= 250)
		{
			R_x13 = -0.15 + (x - 250.0) / 250.0;
			R_x23 = 0.15 + (x - 250.0) / 250.0;
			if (y >= 250)
			{

				R_y13 = -0.15 - (y - 250.0) / 250.0;
				R_y23 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y13 = -0.15 + 1 - y / 250.0;
				R_y23 = 0.15 + 1 - y / 250.0;

			}
		}
		 else if (0 < x && x < 250)
		 {
			R_x13 = -0.15 - 1.0 + x / 250.0;
			R_x23 = 0.15 - 1.0 + x / 250.0;
			if (y >= 250)
			{

				R_y13 = -0.15 - (y - 250.0) / 250.0;
				R_y23 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y13 = -0.15 + 1 - y / 250.0;
				R_y23 = 0.15 + 1 - y / 250.0;

			}
		 }
		 X13 = R_x13;
		 Y13 = R_y13;
		 X23 = R_x23;
		 Y23 = R_y23;
		}
		else if (count == 5)
		{
		 R5 = rand() % 2;
		 G5 = rand() % 2;
		 B5 = rand() % 2;
		if (x >= 250)
		{
			R_x14 = -0.15 + (x - 250.0) / 250.0;
			R_x24 = 0.15 + (x - 250.0) / 250.0;
			if (y >= 250)
			{

				R_y14 = -0.15 - (y - 250.0) / 250.0;
				R_y24 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y14 = -0.15 + 1 - y / 250.0;
				R_y24 = 0.15 + 1 - y / 250.0;

			}
		}
		 else if (0 < x && x < 250)
		 {
			R_x14 = -0.15 - 1.0 + x / 250.0;
			R_x24 = 0.15 - 1.0 + x / 250.0;
			if (y >= 250)
			{

				R_y14 = -0.15 - (y - 250.0) / 250.0;
				R_y24 = 0.15 - (y - 250.0) / 250.0;
			}
			else
			{
				R_y14 = -0.15 + 1 - y / 250.0;
				R_y24 = 0.15 + 1 - y / 250.0;

			}
		 }
		 X14 = R_x14;
		 Y14 = R_y14;
		 X24 = R_x24;
		 Y24 = R_y24;
		}
	}
	else
	{
		//left_button = false;
	}

}
//void Motion(int x, int y)
//{
//	if (left_button == true)
//	{
//		
//	}
//
//
//	glutPostRedisplay();
//}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (DG_key == 1)
		{
			Dg_flag = 1;
			glutTimerFunc(100, DG_func, 1);
			DG_key = 0;
			
		}
		else
		{
			Dg_flag = 0;
			DG_key = 1;
		}
		break;
	case'i':
		if (ZIG_key == 1)
		{
			Zig_flag = 1;
			glutTimerFunc(100, ZIG_func, 2);
			ZIG_key = 0;

		}
		else
		{
			Zig_flag = 0;
			ZIG_key = 1;
		}
		break;

	case'c':
		if (FORM_key == 1)
		{
				Form_flag = 1;
				glutTimerFunc(100, Form_fuc, 3);
				FORM_key = 0;

		}
		else
		{
				Form_flag = 0;
				FORM_key = 1;
				
		}
		break;

	case's':
		Dg_flag = 0;
		DG_key = 1;
		Zig_flag = 0;
		ZIG_key = 1;
		Form_flag = 0;
		FORM_key = 1;
		break;
	case'm':
		R_x1 = X1;
		R_y1 = Y1;
		R_x2 = X2;
		R_y2 = Y2;

		R_x11 = X11;
		R_y11 = Y11;
		R_x21 = X21;
		R_y21 = Y21;

		R_x12 = X12;
		R_y12 = Y12;
		R_x22 = X22;
		R_y22 = Y22;

		R_x13 = X13;
		R_y13 = Y13;
		R_x23 = X23;
		R_y23 = Y23;

		R_x14 = X14;
		R_y14 = Y14;
		R_x24 = X24;
		R_y24 = Y24;
		break;

	case'r':
		count = 0;
		COUNT = 0;
		Dg_flag = 0;
		DG_key = 1;
		Zig_flag = 0;
		ZIG_key = 1;
		Form_flag = 0;
		FORM_key = 1;

		R_x1 =0;
		R_y1 = 0;
		R_x2 = 0;
		R_y2 = 0;

		R_x11 = 0;
		R_y11 = 0;
		R_x21 = 0;
		R_y21 = 0;

		R_x12 = 0;
		R_y12 = 0;
		R_x22 = 0;
		R_y22 = 0;

		R_x13 = 0;
		R_y13 = 0;
		R_x23 = 0;
		R_y23 = 0;

		R_x14 = 0;
		R_y14 = 0;
		R_x24 = 0;
		R_y24 = 0;
		break;
	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}



	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}