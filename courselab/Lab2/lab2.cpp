// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "GL/glut.h"

float fTranslate;
float fRotate;
float fChangesize=1.0f;

void Draw_Desk() // ��������������һ�����ӡ�
{
	glColor3f(1.0f,1.0f,1.0f);			//��ʼ��������ɫΪ��ɫ	
	glTranslatef(0,0,0);			//����ԭ��λ�ã���������
	glScalef(1.5,1.2,0.3);			//��������ĳ��Ŵ�Ϊ1.5������Ŵ�Ϊ1.2��������СΪ0.3��������ߵı���Ϊ5��4��1��
	glutWireCube(1.0);				//���������壬��Ϊ����

	glTranslatef(-0.3,-0.25,-2);		//��ԭ����x�Ḻ�����ƶ�0.3�������泤�ȵľ��룬y�Ḻ�����ƶ�0.25���������ȵľ��룬z�Ḻ�����ƶ�2������ߵľ��룬�õ�����������Ϊһ�����š�
	glScalef(0.15,0.15,3);			//�������峤��������������Ϊԭ����0.15��0.15��0.3��
	glutWireCube(1.0);				//������������Ϊһ������

	glTranslatef(4,0,0);			//����ǰһ�������ƶ�ԭ��λ��
	glutWireCube(1.0);				//���Ƶڶ�������

	glTranslatef(0,3,0);
	glutWireCube(1.0);

	glTranslatef(-4,0,0);
	glutWireCube(1.0);

	glFlush();				//����ͼ��
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
// If want display in wireframe mode
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glPushMatrix();
		glTranslatef(-2.0f, 0.0f,-6.0f);		// �������������Ļ���
		glTranslatef(0.0f, fTranslate, 0.0f);	// �ı�ԭ����Y���λ�ã�ʵ�����ӵ��ƶ�
		Draw_Desk();						// ������					
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-6.0f);			// �������������Ļ�м�
		glRotatef(fRotate, 0, 1.0f, 0);			// �����ӵķ�����x����ת��ʵ�����ӵ���ת
		Draw_Desk();						// ������
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f,0.0f,-6.0f);			//�����ӷ�������Ļ�ұ�
		glScalef(fChangesize,fChangesize,fChangesize);	//����������Ϊԭ����fChangesize���Ĵ�С
		Draw_Desk();					//������
	glPopMatrix();

	fTranslate += 0.005f;
	fRotate    += 0.5f;
	fChangesize-=0.05f;


	if(fTranslate > 0.5f) fTranslate = 0.0f;
	if(fChangesize<=0.6f) fChangesize=1.0f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);                                                  
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);		
	glutIdleFunc(idle);					

	glutMainLoop();

	return 0;
}


