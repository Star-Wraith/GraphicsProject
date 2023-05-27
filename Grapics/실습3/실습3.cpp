#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
int count = 0;
GLvoid drawScene(GLvoid);
GLvoid drawRect();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Mouse(int button, int state, int x, int y);

bool left_button = false;
GLfloat R_x1 = - 0.2f;
GLfloat R_y1 = - 0.2f;
GLfloat R_x2 = 0.2f;
GLfloat R_y2 = 0.2f;
GLfloat R_x11 = -0.2f;
GLfloat R_y11 = -0.2f;
GLfloat R_x21 = 0.2f;
GLfloat R_y21 = 0.2f;
GLfloat R_x12 = -0.2f;
GLfloat R_y12 = -0.2f;
GLfloat R_x22 = 0.2f;
GLfloat R_y22 = 0.2f;
GLfloat R_x13 = -0.2f;
GLfloat R_y13 = -0.2f;
GLfloat R_x23 = 0.2f;
GLfloat R_y23 = 0.2f;
GLfloat R_x14 = -0.2f;
GLfloat R_y14 = -0.2f;
GLfloat R_x24 = 0.2f;
GLfloat R_y24 = 0.2f;
void main(int argc, char** argv)
{

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
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop();

}

GLvoid drawScene()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // ������ ������ ��ü�� ĥ�ϱ�
	glClear(GL_COLOR_BUFFER_BIT);
	drawRect();
	glutSwapBuffers();
}
GLvoid drawRect()
{
	if (count == 0)
	{
		glColor3f(0, 1, 0);
		glRectf(R_x1, R_y1, R_x2, R_y2);
	}
	else if(count==1)
	{
		glColor3f(0, 1, 0);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(1, 0, 0);
		glRectf(R_x11, R_y11, R_x21, R_y21);

	}
	else if (count == 2)
	{
		glColor3f(0, 1, 0);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(1, 0, 0);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		glColor3f(0, 0, 1);
		glRectf(R_x12, R_y12, R_x22, R_y22);
	}
	else if (count == 3)
	{
		glColor3f(0, 1, 0);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(1, 0, 0);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		glColor3f(0, 0, 1);
		glRectf(R_x12, R_y12, R_x22, R_y22);
		glColor3f(0, 0, 0);
		glRectf(R_x13, R_y13, R_x23, R_y23);
	}
	else if (count == 4)
	{
		glColor3f(0, 1, 0);
		glRectf(R_x1, R_y1, R_x2, R_y2);
		glColor3f(1, 0, 0);
		glRectf(R_x11, R_y11, R_x21, R_y21);
		glColor3f(0, 0, 1);
		glRectf(R_x12, R_y12, R_x22, R_y22);
		glColor3f(0, 0, 0);
		glRectf(R_x13, R_y13, R_x23, R_y23);
		glColor3f(1, 1, 1);
		glRectf(R_x14, R_y14, R_x24, R_y24);
	}
	else if (count == 5)
	{
	     glutLeaveMainLoop();
	}
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && x >= 200 && y <= 300 && x <= 300 && y >= 200)
	{
		left_button = true;
		std::cout << "x = " << x << "y = " << y << std::endl;
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
		if (count == 0)
		{
			if (x >= 250)
			{
				R_x1 = -0.2 + (x - 250.0) / 250.0;
				R_x2 = 0.2 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y1 = -0.2 - (y - 250.0) / 250.0;
					R_y2 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y1 = -0.2 + 1 - y / 250.0;
					R_y2 = 0.2 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x1 = -0.2 - 1.0 + x / 250.0;
				R_x2 = 0.2 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y1 = -0.2 - (y - 250.0) / 250.0;
					R_y2 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y1 = -0.2 + 1 - y / 250.0;
					R_y2 = 0.2 + 1 - y / 250.0;

				}
			}
		}
		else if (count == 1)
		{
			if (x >= 250)
			{
				R_x11 = -0.2 + (x - 250.0) / 250.0;
				R_x21 = 0.2 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y11 = -0.2 - (y - 250.0) / 250.0;
					R_y21 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y11 = -0.2 + 1 - y / 250.0;
					R_y21 = 0.2 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x11 = -0.2 - 1.0 + x / 250.0;
				R_x21 = 0.2 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y11 = -0.2 - (y - 250.0) / 250.0;
					R_y21 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y11 = -0.2 + 1 - y / 250.0;
					R_y21 = 0.2 + 1 - y / 250.0;

				}
			}
		}
		else if (count == 2)
		{
			if (x >= 250)
			{
				R_x12 = -0.2 + (x - 250.0) / 250.0;
				R_x22 = 0.2 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y12 = -0.2 - (y - 250.0) / 250.0;
					R_y22 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y12 = -0.2 + 1 - y / 250.0;
					R_y22 = 0.2 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x12 = -0.2 - 1.0 + x / 250.0;
				R_x22 = 0.2 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y12 = -0.2 - (y - 250.0) / 250.0;
					R_y22 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y12 = -0.2 + 1 - y / 250.0;
					R_y22 = 0.2 + 1 - y / 250.0;

				}
			}
		}
		else if (count == 3)
		{
			if (x >= 250)
			{
				R_x13 = -0.2 + (x - 250.0) / 250.0;
				R_x23 = 0.2 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y13 = -0.2 - (y - 250.0) / 250.0;
					R_y23 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y13 = -0.2 + 1 - y / 250.0;
					R_y23 = 0.2 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x13 = -0.2 - 1.0 + x / 250.0;
				R_x23 = 0.2 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y13 = -0.2 - (y - 250.0) / 250.0;
					R_y23 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y13 = -0.2 + 1 - y / 250.0;
					R_y23 = 0.2 + 1 - y / 250.0;

				}
			}
		}
		else if (count == 4)
		{
			if (x >= 250)
			{
				R_x14 = -0.2 + (x - 250.0) / 250.0;
				R_x24 = 0.2 + (x - 250.0) / 250.0;
				if (y >= 250)
				{

					R_y14 = -0.2 - (y - 250.0) / 250.0;
					R_y24 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y14 = -0.2 + 1 - y / 250.0;
					R_y24 = 0.2 + 1 - y / 250.0;

				}
			}
			else if (0 < x && x < 250)
			{
				R_x14 = -0.2 - 1.0 + x / 250.0;
				R_x24 = 0.2 - 1.0 + x / 250.0;
				if (y >= 250)
				{

					R_y14 = -0.2 - (y - 250.0) / 250.0;
					R_y24 = 0.2 - (y - 250.0) / 250.0;
				}
				else
				{
					R_y14 = -0.2 + 1 - y / 250.0;
					R_y24 = 0.2 + 1 - y / 250.0;

				}
			}
		}
	}


	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		++count;
		break;
	case'q':
		glutLeaveMainLoop();
	default:
		break;
	}



	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}