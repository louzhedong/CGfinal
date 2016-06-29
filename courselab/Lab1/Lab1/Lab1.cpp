// Lab1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "GL/glut.h"  
#include "math.h"  


void inner(float i,float j,int r)
{     float PI = 3.1415;
	  float ax,ay,bx,by,cx,cy,dx,dy,ex,ey;
	  ax=0;
	  ay=r;
	  bx=r*cos(18*PI/180);
      by=r*sin(18*PI/180);
	  cx=r*sin(36*PI/180);
      cy=-r*cos(36*PI/180);
	  dx=-cx;
	  dy=cy;
	  ex=-bx;
	  ey=by;

 glColor3f(1.0,1.0,0.0);      //设置五角星颜色为黄色
    glBegin(GL_TRIANGLES);
	        glVertex2i(i,j);
            glVertex2i(i+ax,j+ay);
			glVertex2i(i+dx,j+dy);
    glEnd();

	glBegin(GL_TRIANGLES);
	        glVertex2i(i,j);
            glVertex2i(i+ax,j+ay);
			glVertex2i(i+cx,j+cy);
    glEnd();

	glBegin(GL_TRIANGLES);
			glVertex2i(i,j);
			glVertex2i(i+bx,j+by);
            glVertex2i(i+ex,j+ey);
	 glEnd();	

    glBegin(GL_TRIANGLES);
			glVertex2i(i,j);
			glVertex2i(i+bx,j+by);
            glVertex2i(i+dx,j+dy);
	 glEnd();

	 glBegin(GL_TRIANGLES);
			glVertex2i(i,j);
			glVertex2i(i+cx,j+cy);
            glVertex2i(i+ex,j+ey);
	 glEnd();
	
	
}

void display(void)
{ glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 

   glColor3f(1.0,0.0,0.0);        //颜色为红色
    glBegin(GL_QUADS);
            glVertex2i(0,140);
			glVertex2i(100,140);
	        glVertex2i(100,80);    
            glVertex2i(0,80);
    glEnd();
	
    inner(15,123,9);
	
    glTranslatef(28.0f,135.0f,0.0f);
	glPushMatrix();
    glRotatef(-30.0f,0.0f,0.0f,1.0f);
    inner(0,0,4);
	glPopMatrix();
    
	glTranslatef(7.0f,-7.0f,0.0f);
	glPushMatrix();
    glRotatef(30.0f,0.0f,0.0f,1.0f);
    inner(0,0,4);
	glPopMatrix();

	glTranslatef(0.0f,-10.0f,0.0f);
	inner(0,0,4);
	glTranslatef(-7.0f,-6.0f,0.0f);
	glPushMatrix();
    glRotatef(-30.0f,0.0f,0.0f,1.0f);
    inner(0,0,4);
	glPopMatrix();
	glFlush();                     //渲染
}

void main (int argc,char** argv)
{
    glutInit(&argc,argv);                         //初始化GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //设置显示模式
    glutInitWindowPosition(100,100);               //设置显示窗口的左上角位置
    glutInitWindowSize(800,600);                  //设置窗口的长和高
    glutCreateWindow("五星红旗" );     //创造显示窗口

	glMatrixMode(GL_PROJECTION);    //设置投影参数
	gluOrtho2D(0.0,200.0,0.0,150.0);

    glutDisplayFunc(display); //发送图形到显示窗口

    glutMainLoop();              //显示所有并等候
}

