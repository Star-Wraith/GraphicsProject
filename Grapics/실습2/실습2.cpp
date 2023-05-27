#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <ctime>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);

GLfloat red = 1;
GLfloat green = 1;
GLfloat blue = 1;
GLfloat R_r = 1;
GLfloat R_g = 1;
GLfloat R_b = 0;
GLfloat xy1 = -0.5;
GLfloat xy2 = 0.5;
void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(500, 500); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����

		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutMouseFunc(Mouse);

	glutMainLoop();

}
GLvoid drawScene()
{
	glClearColor(red, green, blue, 1.0f);  // ������ ������ ��ü�� ĥ�ϱ�
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R_r, R_g, R_b);
	glRectf(xy1, xy1, xy2, xy2);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y)
{
	int tall= 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x >= 125 && y  < 375 && x  <= 375 && y  >125)
		{
			
			R_r = rand() % 2;
			R_g = rand() % 2;
			R_b = rand() % 2;
		}
		else
		{
			red = rand() % 2;
			green = rand() % 2;
			blue = rand() % 2;
		}
	
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (x >= 125 - tall && y + tall < 375 && x + tall <= 375 && y - tall>125)
		{
		
			tall = tall + 500/20.0;
			xy1 = xy1 - 0.1;
			xy2 = xy2 + 0.1;
	
		}
		else
		{
			tall = tall - 500/20.0;
			xy1 = xy1 + 0.1;
			xy2 = xy2 - 0.1;
			
		}


	}

	glutPostRedisplay();

}

