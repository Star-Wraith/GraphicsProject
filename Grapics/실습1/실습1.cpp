#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
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

	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(250, 250); // 윈도우의 크기 지정
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

	glutMainLoop();

}
GLvoid drawScene()
{
	glClearColor(red,green,blue,1.0f);  // 설정된 색으로 전체를 칠하기
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
	case 'R':     //--- 배경색을 빨강색으로 설정
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		
		break;
	case 'G':     //--- 배경색을 초록색으로 설정
		red = 0.0;
		green = 1.0;
		blue = 0.0;

		break;
	case 'B':     //--- 배경색을 파랑색으로 설정
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
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}