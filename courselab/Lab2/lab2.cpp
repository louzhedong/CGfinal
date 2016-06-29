// main.cpp : 定义控制台应用程序的入口点。
//

#include "GL/glut.h"

float fTranslate;
float fRotate;
float fChangesize=1.0f;

void Draw_Desk() // 这个函数将会绘制一张桌子。
{
	glColor3f(1.0f,1.0f,1.0f);			//初始化线条颜色为白色	
	glTranslatef(0,0,0);			//定义原点位置，绘制桌面
	glScalef(1.5,1.2,0.3);			//将立方体的长放大为1.5倍，宽放大为1.2倍，高缩小为0.3倍。长宽高的比例为5：4：1。
	glutWireCube(1.0);				//绘制立方体，作为桌面

	glTranslatef(-0.3,-0.25,-2);		//将原点往x轴负方向移动0.3倍的桌面长度的距离，y轴负方向移动0.25倍的桌面宽度的距离，z轴负方向移动2倍桌面高的距离，得到的立方体作为一个桌脚。
	glScalef(0.15,0.15,3);			//将立方体长、宽、高依次缩放为原来的0.15，0.15，0.3倍
	glutWireCube(1.0);				//绘制立方体作为一个桌脚

	glTranslatef(4,0,0);			//参照前一个桌脚移动原点位置
	glutWireCube(1.0);				//绘制第二个桌脚

	glTranslatef(0,3,0);
	glutWireCube(1.0);

	glTranslatef(-4,0,0);
	glutWireCube(1.0);

	glFlush();				//绘制图案
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
		glTranslatef(-2.0f, 0.0f,-6.0f);		// 将桌面放置在屏幕左边
		glTranslatef(0.0f, fTranslate, 0.0f);	// 改变原点在Y轴的位置，实现桌子的移动
		Draw_Desk();						// 画桌子					
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-6.0f);			// 将桌面放置在屏幕中间
		glRotatef(fRotate, 0, 1.0f, 0);			// 将桌子的方向沿x轴旋转，实现桌子的旋转
		Draw_Desk();						// 画桌子
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f,0.0f,-6.0f);			//将桌子放置在屏幕右边
		glScalef(fChangesize,fChangesize,fChangesize);	//将桌子缩放为原来的fChangesize倍的大小
		Draw_Desk();					//画桌子
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


