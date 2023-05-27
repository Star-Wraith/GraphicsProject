#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <ctime>
int count = 0;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
GLfloat red = 1;
GLfloat green = 1;
GLfloat blue = 1;
int flag = 1;
void main(int argc, char** argv)
{

	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(250, 250); // �������� ũ�� ����
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
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����

	glutMainLoop();

}
GLvoid drawScene()
{
	glClearColor(red,green,blue,1.0f);  // ������ ������ ��ü�� ĥ�ϱ�
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
void TimerFunction(int value)
{
	if (flag == 1)
	{
		red = rand() % 2;
		green = rand() % 2;
		blue = rand() % 2;
		glutPostRedisplay();
		glutTimerFunc(100, TimerFunction, 1);
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	srand((unsigned int)time(NULL));
	x = 0;
	y = 0;
	switch (key) {
	case 'R':     //--- ������ ���������� ����
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		
		break;
	case 'G':     //--- ������ �ʷϻ����� ����
		red = 0.0;
		green = 1.0;
		blue = 0.0;

		break;
	case 'B':     //--- ������ �Ķ������� ����
		red = 0.0;
		green = 0.0;
		blue = 1.0;
	
		break;
	case 'A':
		red = rand() % 2;
		green = rand() % 2;
		blue = rand() % 2;
		break;
	case 'W':
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		break;
	case 'K':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		break;
	case 'T':
		flag = 1;
		glutTimerFunc(1000, TimerFunction, 1000);;
		break;
	case 'S':
		flag = 0;
		break;
	case 'Q':
		glutLeaveMainLoop();
		break;

		
	}
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}