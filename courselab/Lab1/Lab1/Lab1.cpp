// Lab1.cpp : �������̨Ӧ�ó������ڵ㡣
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

 glColor3f(1.0,1.0,0.0);      //�����������ɫΪ��ɫ
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
 

   glColor3f(1.0,0.0,0.0);        //��ɫΪ��ɫ
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
	glFlush();                     //��Ⱦ
}

void main (int argc,char** argv)
{
    glutInit(&argc,argv);                         //��ʼ��GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //������ʾģʽ
    glutInitWindowPosition(100,100);               //������ʾ���ڵ����Ͻ�λ��
    glutInitWindowSize(800,600);                  //���ô��ڵĳ��͸�
    glutCreateWindow("���Ǻ���" );     //������ʾ����

	glMatrixMode(GL_PROJECTION);    //����ͶӰ����
	gluOrtho2D(0.0,200.0,0.0,150.0);

    glutDisplayFunc(display); //����ͼ�ε���ʾ����

    glutMainLoop();              //��ʾ���в��Ⱥ�
}

