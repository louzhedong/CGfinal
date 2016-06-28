// cg2016_TeamWork3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include "ObjModel.hpp"
#define BITMAP_ID 0x4D42

using namespace std;

const GLfloat Pi = 3.1415926536f;

float fRotate;
ObjModel Apple;
bool bPersp = false;
bool bWire = false;
bool bAnim = false;
bool bLight = false;
bool bTexture = false;
bool bcolor = false;
bool bmix = false;

/***********************************
***********************************
�����������Ʊ������ֱ�ı�����Ͳ���������������ɫ
**********************************
***********************************/
bool bChange = false;
bool bChangeTeapot = false;
bool bColor = false;//�ı�����������ɫ

int wHeight = 0;
int wWidth = 0;

//b['1'] = true;  //�����л���texture[0]��texture[2]

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };
float mat[16];
float angle = 0;
float light_int = 0;
GLfloat light_pos[] = { 5, 5, 5, 1 };

unsigned int texture[10];

//typedef struct tagBITMAPFILEHEADER {
//    unsigned short    bfType;
//    unsigned int   bfSize;
//    unsigned short    bfReserved1;
//    unsigned short    bfReserved2;
//    unsigned int   bfOffBits;
//} BITMAPFILEHEADER;
//typedef struct tagBITMAPINFOHEADER {
//    unsigned int      biSize;
//    int        biWidth;
//    int        biHeight;
//    unsigned short       biPlanes;
//    unsigned short       biBitCount;
//    unsigned int      biCompression;
//    unsigned int      biSizeImage;
//    int        biXPelsPerMeter;
//    int        biYPelsPerMeter;
//    unsigned int      biClrUsed;
//    unsigned int      biClrImportant;
//} BITMAPINFOHEADER;

void initModels(){
	Apple.loadOBJ("Models/Apple", "Apple.obj");
    Apple.unitize(1.3);
    Apple.setPosition(0,6,-15);
}

void Draw_Table()
{	
	//glPushMatrix();
	glColor3f(0.06f,0.81f,0.25f);
	float table_diffuse[] = { 0.06f,0.31f,0.55f, 1.0f };//�����ɢ����ɫ�������ɫ
	float table_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float table_shininess[] = { 20.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, table_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, table_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, table_shininess);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(2.0f, 2.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-2.0f, 2.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(2.0f, 2.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f, 2.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f, 2.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f, 2.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	//glPopMatrix();
}

void Draw_Leg()
{
	glColor3f(0.55f,0.25f,0.15f);
	float leg_specular[] = { 1, 1, 1, 1 };
	float leg_diffuse[] = { 0.55, 0.25, 0.15, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, leg_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, leg_diffuse);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

void glutSolidCube2(float size)//�����������沢ָ����������
{
	//glPushMatrix();
	glScalef(size, size, size);
	glColor3f(1.0, 1.0, 1.0f);
	glBegin(GL_QUADS); //�±���
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS); //�ϱ���
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);  //ǰ
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);  //��
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);    //left
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS);    //right
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	//glPopMatrix();
} 


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader) 
{
	FILE *filePtr;	// �ļ�ָ��
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap�ļ�ͷ
	unsigned char	*bitmapImage;		// bitmapͼ������
	int	imageIdx = 0;		// ͼ��λ������
	unsigned char	tempRGB;	// ��������

	// �ԡ�������+����ģʽ���ļ�filename 
	filePtr = fopen(filename, "rb"); 
	if (filePtr == NULL) return NULL;
	// ����bitmap�ļ�ͼ
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	// ��֤�Ƿ�Ϊbitmap�ļ�
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// ����bitmap��Ϣͷ
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	// ���ļ�ָ������bitmap����
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// Ϊװ��ͼ�����ݴ����㹻���ڴ�
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage]; 
	// ��֤�ڴ��Ƿ񴴽��ɹ�
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// ����bitmapͼ������
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr); 
	// ȷ�϶���ɹ�
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//����bitmap�б���ĸ�ʽ��BGR�����潻��R��B��ֵ���õ�RGB��ʽ
	for (imageIdx = 0; 
	 imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3) { 
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	// �ر�bitmapͼ���ļ�
	fclose(filePtr); 
	return bitmapImage; 
}

unsigned char *CreateCustomBmp(BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;	// �ļ�ָ��
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap�ļ�ͷ
    unsigned char	*bitmapImage;		// bitmapͼ������
    int	imageIdx = 0;		// ͼ��λ������
    unsigned char	tempRGB;	// ��������
    
    
    bitmapInfoHeader->biWidth = 640;
    bitmapInfoHeader->biHeight = 480;
    bitmapInfoHeader->biSizeImage = 640 * 480 * 3;
    bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
    
    
    //unsigned char a[480][640];
    
    int x = 0;
    int y = 0;
    
    for (int i = 0; i < 480; i++){
        if (i % 50 == 0)
            x = 1 - x;
        
        if (x)
            y = 0;
        else
            y = 1;
        
        for (int j = 0; j < 640; j++){
            if (j % 50 == 0)
                y = 1 - y;
            
            if (y){
                bitmapImage[i * 640 * 3 + 3 * j] = 255;
                bitmapImage[i * 640 * 3 + 3 * j + 1] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 2] = 0;
            }
            else{
                bitmapImage[i * 640 * 3 + 3 * j] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 1] = 0;
                bitmapImage[i * 640 * 3 + 3 * j + 2] = 0;
            }
        }
    }
    
    
    return bitmapImage;
}

void initOpengl()
{
	initModels();
	glClearColor(0.0, 0.0, 0.0, 1.0);	
	GLfloat black[] =  {0.0, 0.0, 0.0, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// ����s����������Զ�����
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);						// �Զ�����s������������
	glEnable(GL_TEXTURE_GEN_T);

	BITMAPINFOHEADER bitmapInfoHeader1; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader2; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader3; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader4; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader5; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader6; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader7; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader8; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader9; // bitmap��Ϣͷ
	BITMAPINFOHEADER bitmapInfoHeader10; // bitmap��Ϣͷ

	unsigned char*   bitmapData1;         // ��������
	unsigned char*   bitmapData2;         // ��������	
	unsigned char*   bitmapData3;         // ��������
	unsigned char*   bitmapData4;         // ��������
	unsigned char*   bitmapData5;         // ��������	
	unsigned char*   bitmapData6;         // ��������
	unsigned char*   bitmapData7;         // ��������
	unsigned char*   bitmapData8;         // ��������
	unsigned char*   bitmapData9;         // ��������
	unsigned char*   bitmapData10;         // ��������

	bitmapData1= NULL; 
	bitmapData2 = NULL;
	bitmapData3 = NULL;
	bitmapData4=NULL; 
	bitmapData5 = NULL;
	bitmapData6 = NULL;
	bitmapData7=NULL; 
	bitmapData8=NULL;
	bitmapData9=NULL; 
	bitmapData10=NULL;

	//��ȡͼƬ����
	bitmapData1 = LoadBitmapFile("crystal.bmp", &bitmapInfoHeader1);
	cout<<bitmapInfoHeader1.biWidth<<endl;
	bitmapData2 = LoadBitmapFile("egg.bmp", &bitmapInfoHeader2);
	bitmapData3 = LoadBitmapFile("floor3.bmp", &bitmapInfoHeader3);
	bitmapData4 = LoadBitmapFile("sofa.bmp", &bitmapInfoHeader4);
	bitmapData5 = LoadBitmapFile("soccer.bmp", &bitmapInfoHeader5);
	bitmapData6 = LoadBitmapFile("teapot.bmp", &bitmapInfoHeader6);
	cout<<bitmapInfoHeader6.biWidth<<endl;
	bitmapData7 = LoadBitmapFile("woodForTable.bmp", &bitmapInfoHeader7);
	cout<<bitmapInfoHeader7.biWidth<<endl;
	bitmapData9 = LoadBitmapFile("backrest2.bmp", &bitmapInfoHeader9);
	bitmapData10 = LoadBitmapFile("cone.bmp", &bitmapInfoHeader10);

	//��ͼƬ���ݸ�����
	// ��һ��������Ҫ���ɱ�ʾ���ĸ���
	// �ڶ������Ƿ��ر�ʾ��������
	glGenTextures(10, texture);  

	//�󶨵�һ������ ���й���
	glBindTexture(GL_TEXTURE_2D, texture[0]);  
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //�Ŵ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//��С
	glTexImage2D(GL_TEXTURE_2D, 
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader1.biWidth,	//�����ȣ�������2n�����б߿�+2 
		bitmapInfoHeader1.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData1);			//bitmap����ָ��

	//�󶨵ڶ������� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader2.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader2.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData2);			//bitmap����ָ��

	//�󶨵��������� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader3.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader3.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData3);			//bitmap����ָ��

	//�󶨵��ĸ����� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader4.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader4.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData4);			//bitmap����ָ��

	//�󶨵�������� ���й��� ������
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader5.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader5.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData5);			//bitmap����ָ��

	//�󶨵��������� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader6.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader6.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData6);			//bitmap����ָ��

	//�󶨵��߸����� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader7.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader7.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData7);			//bitmap����ָ��

	//���Զ��������������
	glBindTexture(GL_TEXTURE_1D, texture[7]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	bitmapData8 = CreateCustomBmp(&bitmapInfoHeader8);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		640,	//��������������2n�����б߿�+2 
		480,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData8);				//bitmap����ָ��	

	//�󶨵ھŸ����� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader9.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader9.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData9);			//bitmap����ָ��

	//�󶨵��߸����� ���й���
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap��� (ͨ��Ϊ0����ʾ���ϲ�) 
		GL_RGB,		//����ϣ���������к졢�̡�������
		bitmapInfoHeader10.biWidth,	//��������������2n�����б߿�+2 
		bitmapInfoHeader10.biHeight,	//����߶ȣ�������2n�����б߿�+2 
		0,				//�߿� (0=�ޱ߿�, 1=�б߿�) 
		GL_RGB,				//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,		//ÿ����ɫ���ݵ�����
		bitmapData10);			//bitmap����ָ��
}

void Draw_Scene()
{
	GLUquadricObj *pObj;
	if (bmix) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	Apple.draw();

	glColor3f(0.8f,0.7f,0.6f);
	float ground_diffuse[] = { 0.8f, 0.7f, 0.6f, 1.0f };//�����ɢ����ɫ�������ɫ
	float ground_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };//������ɫ
	float ground_shininess[] = { 30.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ground_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, ground_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();							//����
	glTranslatef(0, 0, -15);
	glScalef(100, 100, 0.1);
	glutSolidCube2(1.0);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();							//���� s������+һ������
	glTranslatef(0, 5, -15);
	glScalef(1, 1, 7);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -5, -15);
	glScalef(1, 1, 7);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10, 5, -15);
	glScalef(1, 1, 7);
	Draw_Leg();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-10, -5, -15);
	glScalef(1, 1, 7);
	Draw_Leg();
	glPopMatrix();
	
	glColor3f(0.8f,0.7f,0.2f);
	float desktop_diffuse[] = { 0.93f, 0.77f, 0.57f, 1.0f };//�����ɢ����ɫ�������ɫ
	float desktop_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float desktop_shininess[] = { 20.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desktop_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, desktop_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desktop_shininess);
	/*********************
	������ͼ
	**********************/
	if(bChange){
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	}else{
		glBindTexture(GL_TEXTURE_2D, texture[2]);
	}
	glPushMatrix();
	glTranslatef(-5, 0, -8);
	glScalef(15, 15, 1.0);
	glutSolidCube2(1.0);
	glPopMatrix();
	
	//glColor3f(1.0f,1.0f,1.0f);
	float soccer_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };//�����ɢ����ɫ�������ɫ
	float soccer_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float soccer_shininess[] = { 20.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, soccer_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, soccer_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, soccer_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glPushMatrix();							//����������
	glTranslatef(-2, -2, -13.6);
	glScalef(1.5, 1.5, 1.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	
	//glColor3f(0.8f, 0.58f, 0.05f);
	/*********************************
	�ı���ɢ����ɫ������ֻ�����������Զ�������²��ܿ���
	********************************/
	float teapot_diffuse[] = { 0.8f, 0.58f, 0.05f, 1.0f };//�����ɢ����ɫ�������ɫ
	if(!bColor){
		teapot_diffuse[1] = 0.08f;
		teapot_diffuse[2] = 0.35f;
	}
	float teapot_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float teapot_shininess[] = { 40.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, teapot_shininess); 
	/*********************
	������ͼ
	**********************/
	if(bChangeTeapot){
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	}else{
		glBindTexture(GL_TEXTURE_2D, texture[6]);
	}
	glPushMatrix();							//���
	glTranslatef(-7, 2, -6.4);
	glRotatef(90, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glutSolidTeapot(1);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();							//��̨
	glTranslatef(0, 4, -7.5);
	glScalef(0.5, 0.5, 0.7);
	Draw_Table();
	glPopMatrix();
	
	glColor3f(1.0f,0.96f,0.56f);
	float egg_diffuse[] = { 1.0f,0.96f,0.56f, 1.0f };//�����ɢ����ɫ�������ɫ
	float egg_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float egg_shininess[] = { 10.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, egg_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, egg_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, egg_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();							//����
	glTranslatef(0, 4, -6);
	glScalef(0.5, 0.5, 0.75);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	
	glColor3f(0.6f,0.2f,0.8f);
	float cone_diffuse[] = { 0.6f,0.2f,0.8f, 1.0f };//�����ɢ����ɫ
	float cone_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float cone_shininess[] = { 80.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cone_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cone_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, cone_shininess);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glPushMatrix();							//Բ׶�壻
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);
	glTranslatef(-10, -2, -6);
	glRotatef(180, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	gluCylinder(pObj, 0.0f, 2.0f, 5.0f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.97f,0.93f,0.84f);
	float sofa1_diffuse[] = { 0.97f,0.7f,0.15f, 1.0f };//�����ɢ����ɫ�������ɫ
	float sofa1_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float sofa1_shininess[] = { 10.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sofa1_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sofa1_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, sofa1_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();							//ɳ��
	glTranslatef(8, 0, -13);
	glScalef(10, 30, 4);
	glutSolidCube2(1.0);
	glPopMatrix();
	
	float sofa2_diffuse[] = { 0.93f,0.91f,0.81f, 1.0f };//�����ɢ����ɫ�������ɫ
	float sofa2_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//������ɫ
	float sofa2_shininess[] = { 40.0 };  //���淴��ϵ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sofa2_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sofa2_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, sofa2_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glPushMatrix();
	glTranslatef(12, 15, -9);
	glScalef(2, 30, 2);
	glRotatef(90, 1, 0, 0);
	pObj = gluNewQuadric();
	gluCylinder(pObj, 1, 1, 1, 32, 32);
	glPopMatrix();	
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i<1000; i++)
		glVertex3f(2*cos(2 * Pi / 1000*i)+12, -15,2*sin(2 * Pi / 1000*i)-9);
	glEnd();
	glBegin(GL_POLYGON);
	for (i = 0; i<1000; i++)
		glVertex3f(2 * cos(2 * Pi / 1000 * i) + 12, 15, 2 * sin(2 * Pi / 1000 * i) - 9);
	glEnd();

	glEnable(GL_TEXTURE_2D);

}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

//��Ļ��ͼ
bool SnapScreen(int width,int height,const char *file)
{
	 byte *image;          //����ͼ������
	 FILE *fp;            //�ļ�ָ��
	 BITMAPFILEHEADER FileHeader;    //����λͼ�ļ�ͷ
	 BITMAPINFOHEADER InfoHeader;    //����λͼ��Ϣͷ

	 FileHeader.bfType=BITMAP_ID;                                                  //ID����Ϊλͼ��id��
	 FileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);      
	 FileHeader.bfReserved1=0;                                                    
	 FileHeader.bfReserved2=0;                                                    
	 FileHeader.bfSize=height*width*24+FileHeader.bfOffBits;                      //BMPͼ���ļ���С

	 InfoHeader.biXPelsPerMeter = 0;                                              //ˮƽ�ֱ���
	 InfoHeader.biYPelsPerMeter = 0;                                              //��ֱ�ֱ���
	 InfoHeader.biClrUsed = 0;                                                    //ͼ��ʹ�õ���ɫ
	 InfoHeader.biClrImportant = 0;                                                //��Ҫ����ɫ��                     
	 InfoHeader.biPlanes=1;                //��������Ϊ1
	 InfoHeader.biCompression=BI_RGB;                                              //����ΪBI_RGBʱ,��ʾͼ��û�в�ɫ��
	 InfoHeader.biBitCount=24;                                                    //ͼ���λ��
	 InfoHeader.biSize=sizeof(BITMAPINFOHEADER);                                  //�ṹ��Ĵ�С
	 InfoHeader.biHeight=height;                                                
	 InfoHeader.biWidth=width;                                                    
	 InfoHeader.biSizeImage=height*width*4;                                       

	 image=(byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage);
	 if (image == NULL)
	 {
	  free(image);
	  printf("Exception: No enough space!\n");
	  return false;
	 }
	 //���ظ�ʽ����4�ֽڶ���
	 glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	 //���ճ����ص�����
	 glReadPixels(0,0,width,height,GL_BGR_EXT,GL_UNSIGNED_BYTE,image);
 
	 fp=fopen(file,"wb");
	 if (fp == NULL)
	 {
	  printf("Exception: Fail to open file!\n");
	  return false;
	 }
	 fwrite(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	 fwrite(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	 fwrite(image, InfoHeader.biSizeImage, 1, fp);
	 free(image);
	 fclose(fp); 
	 return true;
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

struct str
{
    int x,y;
}oldpt;

void Mouse(int button, int state, int x, int y)        /*����갴�»�����ʱ��ص��ú���*/
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //        l_button_down = TRUE;                /*��l_button_downΪtrueʱ�ſɸı����λ��*/
        oldpt.x=x;                      /*��¼�����꣬�Ա��ƶ�����ʱ��������ƶ�����*/
        oldpt.y=y;
        printf("����������\n");
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //        l_button_down = FALSE;        /*����ʱ���ܸı������λ��*/
        printf("�������ɿ�\n");
    }
}

void onMouseMove(int x, int y)          /*������ƶ�ʱ��ص��ú���*/
{
    angle-=(x-oldpt.x)/100.0;
    center[1]-=(y-oldpt.y)/50.0;
    oldpt.x=x;
    oldpt.y=y;
    center[0]=-5.0f*sin(angle)+eye[0];
    center[2]=-5.0f*cos(angle)+eye[2];
    printf("%lf %lf\n",center[0],center[2]);
    printf("����ƶ�\n");
}



void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }
	case 'o': {bWire = !bWire; break; }
	case ' ': {bAnim = !bAnim; break; }

	case 'a': {
				  eye[0] += 0.2f;
				  center[0] += 0.2f;
				  break;
	}
	case 'd': {
				  eye[0] -= 0.2f;
				  center[0] -= 0.2f;
				  break;
	}
	case 'w': {
				  eye[1] -= 0.2f;
				  center[1] -= 0.2f;
				  break;
	}
	case 's': {
				  eye[1] += 0.2f;
				  center[1] += 0.2f;
				  break;
	}
	case 'r': {
				  

	}
	case 'z': {
				  eye[2] -= 0.2f;
				  center[2] -= 0.2f;
				  break;
	}
	case 'c': {
				  eye[2] += 0.2f;
				  center[2] += 0.2f;
				  break;
	}
	case 'h': {
				  bLight = !bLight;
				  break;
	}
	case 't': {
				  bTexture = !bTexture;
				  break;
	}
	case '9': {
				  SnapScreen(400,400,"screen/screen.bmp");
				  printf("����ͼƬ�ɹ�");
				  break;
	}
			  case 'i': {
				  light_pos[1] += 0.2f;
				  break;
	}
	case 'k': {
				  light_pos[1] -= 0.2f;
				  break;
	}
	case 'j': {
				  light_pos[0] -= 0.2f;
				  break;
	}
	case 'l': {
				  light_pos[0] += 0.2f;
				  break;
	}
	case 'n': {
				  light_pos[2] += 0.2f;
				  break;
	}
	case 'm': {
				  light_pos[2] -= 0.2f;
				  break;
	}
	case 'u': {
				  bcolor = !bcolor;
				  break;
	}
	case 'y': {
				  bmix = !bmix;
				  break;
	}
	case 'v': {
				  light_int+=0.1;
				  break;
	}
	case 'b': {
				  light_int -= 0.1;
				  if (light_int<0) light_int += 0.1;
				  break;
	}
	/*********************
	��������1,2��3������ͼ�л�
	**********************/
	case '1': {
				  bChange = !bChange;
				  break;
	}
	case '2': {
				  bChangeTeapot = !bChangeTeapot;
				  break;
	}
	case '3': {
				  bColor = !bColor;
				  break;
	}
	}

	updateView(wHeight, wWidth);
}

void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// ������0��0��0�����ӵ����� (0,5,50)��Y������
	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}    
	if (bLight) {   
		glDisable(GL_LIGHTING);
	}
	else
		glEnable(GL_LIGHTING);
	if (bTexture) {   
		glDisable(GL_TEXTURE_2D);
	}
	else
		glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	GLfloat white[] = { 0.4, 0.4, 0.4, 0.4 };
	GLfloat red[] = { 1.0, 0, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	if (bcolor == false) glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	else glLightfv(GL_LIGHT0, GL_AMBIENT, red);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, light_int);
	//glEnable(GL_LIGHT0);
	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw triangle

	if (bAnim) fRotate += 0.05f;
	glutSwapBuffers();

}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 640);
	int windowHandle = glutCreateWindow("openGL_TeamWork");
	initOpengl();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(Mouse);  
    glutMotionFunc(onMouseMove);
	glutMainLoop();
	return 0;
}
