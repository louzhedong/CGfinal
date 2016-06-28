// cg2016_TeamWork3.cpp : 定义控制台应用程序的入口点。
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
加了三个控制变量，分别改变桌面和茶壶纹理和漫反射颜色
**********************************
***********************************/
bool bChange = false;
bool bChangeTeapot = false;
bool bColor = false;//改变茶壶漫反射颜色

int wHeight = 0;
int wWidth = 0;

//b['1'] = true;  //纹理切换，texture[0]和texture[2]

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
	float table_diffuse[] = { 0.06f,0.31f,0.55f, 1.0f };//镜面的散射颜色——金黄色
	float table_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float table_shininess[] = { 20.0 };  //镜面反射系数
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

void glutSolidCube2(float size)//长方体六个面并指定纹理坐标
{
	//glPushMatrix();
	glScalef(size, size, size);
	glColor3f(1.0, 1.0, 1.0f);
	glBegin(GL_QUADS); //下表面
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_QUADS); //上表面
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);  //前
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_QUADS);  //后
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
	FILE *filePtr;	// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
	unsigned char	*bitmapImage;		// bitmap图像数据
	int	imageIdx = 0;		// 图像位置索引
	unsigned char	tempRGB;	// 交换变量

	// 以“二进制+读”模式打开文件filename 
	filePtr = fopen(filename, "rb"); 
	if (filePtr == NULL) return NULL;
	// 读入bitmap文件图
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr); 
	// 验证是否为bitmap文件
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}

	// 读入bitmap信息头
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr); 
	// 将文件指针移至bitmap数据
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// 为装载图像数据创建足够的内存
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage]; 
	// 验证内存是否创建成功
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr); 
	// 确认读入成功
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式
	for (imageIdx = 0; 
	 imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3) { 
		tempRGB = bitmapImage[imageIdx]; 
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2]; 
		bitmapImage[imageIdx + 2] = tempRGB; 
	}
	// 关闭bitmap图像文件
	fclose(filePtr); 
	return bitmapImage; 
}

unsigned char *CreateCustomBmp(BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr;	// 文件指针
    BITMAPFILEHEADER bitmapFileHeader;	// bitmap文件头
    unsigned char	*bitmapImage;		// bitmap图像数据
    int	imageIdx = 0;		// 图像位置索引
    unsigned char	tempRGB;	// 交换变量
    
    
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
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			// 设置s方向的纹理自动生成
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);						// 自动生成s方向纹理坐标
	glEnable(GL_TEXTURE_GEN_T);

	BITMAPINFOHEADER bitmapInfoHeader1; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader2; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader3; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader4; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader5; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader6; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader7; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader8; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader9; // bitmap信息头
	BITMAPINFOHEADER bitmapInfoHeader10; // bitmap信息头

	unsigned char*   bitmapData1;         // 纹理数据
	unsigned char*   bitmapData2;         // 纹理数据	
	unsigned char*   bitmapData3;         // 纹理数据
	unsigned char*   bitmapData4;         // 纹理数据
	unsigned char*   bitmapData5;         // 纹理数据	
	unsigned char*   bitmapData6;         // 纹理数据
	unsigned char*   bitmapData7;         // 纹理数据
	unsigned char*   bitmapData8;         // 纹理数据
	unsigned char*   bitmapData9;         // 纹理数据
	unsigned char*   bitmapData10;         // 纹理数据

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

	//读取图片数据
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

	//将图片数据给纹理
	// 第一参数是需要生成标示符的个数
	// 第二参数是返回标示符的数组
	glGenTextures(10, texture);  

	//绑定第一个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[0]);  
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //放大
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//缩小
	glTexImage2D(GL_TEXTURE_2D, 
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader1.biWidth,	//纹理宽度，必须是2n，若有边框+2 
		bitmapInfoHeader1.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData1);			//bitmap数据指针

	//绑定第二个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader2.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader2.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData2);			//bitmap数据指针

	//绑定第三个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader3.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader3.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData3);			//bitmap数据指针

	//绑定第四个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader4.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader4.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData4);			//bitmap数据指针

	//绑定第五个纹理 进行过滤 给球体
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader5.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader5.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData5);			//bitmap数据指针

	//绑定第六个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader6.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader6.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData6);			//bitmap数据指针

	//绑定第七个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader7.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader7.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData7);			//bitmap数据指针

	//绑定自定义纹理进行设置
	glBindTexture(GL_TEXTURE_1D, texture[7]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	bitmapData8 = CreateCustomBmp(&bitmapInfoHeader8);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		640,	//纹理宽带，必须是2n，若有边框+2 
		480,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData8);				//bitmap数据指针	

	//绑定第九个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader9.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader9.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData9);			//bitmap数据指针

	//绑定第七个纹理 进行过滤
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0, 		//mipmap层次 (通常为0，表示最上层) 
		GL_RGB,		//我们希望该纹理有红、绿、蓝数据
		bitmapInfoHeader10.biWidth,	//纹理宽带，必须是2n，若有边框+2 
		bitmapInfoHeader10.biHeight,	//纹理高度，必须是2n，若有边框+2 
		0,				//边框 (0=无边框, 1=有边框) 
		GL_RGB,				//bitmap数据的格式
		GL_UNSIGNED_BYTE,		//每个颜色数据的类型
		bitmapData10);			//bitmap数据指针
}

void Draw_Scene()
{
	GLUquadricObj *pObj;
	if (bmix) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	Apple.draw();

	glColor3f(0.8f,0.7f,0.6f);
	float ground_diffuse[] = { 0.8f, 0.7f, 0.6f, 1.0f };//镜面的散射颜色——金黄色
	float ground_specular[] = { 0.4f, 0.4f, 0.4f, 1.0f };//反射颜色
	float ground_shininess[] = { 30.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ground_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, ground_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();							//地面
	glTranslatef(0, 0, -15);
	glScalef(100, 100, 0.1);
	glutSolidCube2(1.0);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();							//桌子 s四条腿+一个桌面
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
	float desktop_diffuse[] = { 0.93f, 0.77f, 0.57f, 1.0f };//镜面的散射颜色——金黄色
	float desktop_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float desktop_shininess[] = { 20.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, desktop_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, desktop_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, desktop_shininess);
	/*********************
	两种贴图
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
	float soccer_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };//镜面的散射颜色——金黄色
	float soccer_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float soccer_shininess[] = { 20.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, soccer_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, soccer_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, soccer_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glPushMatrix();							//地面上球体
	glTranslatef(-2, -2, -13.6);
	glScalef(1.5, 1.5, 1.5);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	
	//glColor3f(0.8f, 0.58f, 0.05f);
	/*********************************
	改变茶壶散射颜色，不过只有在纹理不是自定义情况下才能看见
	********************************/
	float teapot_diffuse[] = { 0.8f, 0.58f, 0.05f, 1.0f };//镜面的散射颜色——金黄色
	if(!bColor){
		teapot_diffuse[1] = 0.08f;
		teapot_diffuse[2] = 0.35f;
	}
	float teapot_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float teapot_shininess[] = { 40.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teapot_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, teapot_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, teapot_shininess); 
	/*********************
	两种贴图
	**********************/
	if(bChangeTeapot){
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	}else{
		glBindTexture(GL_TEXTURE_2D, texture[6]);
	}
	glPushMatrix();							//茶壶
	glTranslatef(-7, 2, -6.4);
	glRotatef(90, 1, 0, 0);
	glScalef(1.5, 1.5, 1.5);
	glutSolidTeapot(1);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();							//棱台
	glTranslatef(0, 4, -7.5);
	glScalef(0.5, 0.5, 0.7);
	Draw_Table();
	glPopMatrix();
	
	glColor3f(1.0f,0.96f,0.56f);
	float egg_diffuse[] = { 1.0f,0.96f,0.56f, 1.0f };//镜面的散射颜色——金黄色
	float egg_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float egg_shininess[] = { 10.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, egg_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, egg_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, egg_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();							//鸡蛋
	glTranslatef(0, 4, -6);
	glScalef(0.5, 0.5, 0.75);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
	
	glColor3f(0.6f,0.2f,0.8f);
	float cone_diffuse[] = { 0.6f,0.2f,0.8f, 1.0f };//镜面的散射颜色
	float cone_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float cone_shininess[] = { 80.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cone_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cone_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, cone_shininess);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glPushMatrix();							//圆锥体；
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);
	glTranslatef(-10, -2, -6);
	glRotatef(180, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	gluCylinder(pObj, 0.0f, 2.0f, 5.0f, 26, 13);
	glPopMatrix();
	
	glColor3f(0.97f,0.93f,0.84f);
	float sofa1_diffuse[] = { 0.97f,0.7f,0.15f, 1.0f };//镜面的散射颜色——金黄色
	float sofa1_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float sofa1_shininess[] = { 10.0 };  //镜面反射系数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sofa1_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sofa1_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, sofa1_shininess); 
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();							//沙发
	glTranslatef(8, 0, -13);
	glScalef(10, 30, 4);
	glutSolidCube2(1.0);
	glPopMatrix();
	
	float sofa2_diffuse[] = { 0.93f,0.91f,0.81f, 1.0f };//镜面的散射颜色——金黄色
	float sofa2_specular[] = { 1.0f, 1.0f, 0.1f, 1.0f };//反射颜色
	float sofa2_shininess[] = { 40.0 };  //镜面反射系数
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

//屏幕截图
bool SnapScreen(int width,int height,const char *file)
{
	 byte *image;          //接受图像数据
	 FILE *fp;            //文件指针
	 BITMAPFILEHEADER FileHeader;    //接受位图文件头
	 BITMAPINFOHEADER InfoHeader;    //接受位图信息头

	 FileHeader.bfType=BITMAP_ID;                                                  //ID设置为位图的id号
	 FileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);      
	 FileHeader.bfReserved1=0;                                                    
	 FileHeader.bfReserved2=0;                                                    
	 FileHeader.bfSize=height*width*24+FileHeader.bfOffBits;                      //BMP图像文件大小

	 InfoHeader.biXPelsPerMeter = 0;                                              //水平分辨率
	 InfoHeader.biYPelsPerMeter = 0;                                              //垂直分辨率
	 InfoHeader.biClrUsed = 0;                                                    //图像使用的颜色
	 InfoHeader.biClrImportant = 0;                                                //重要的颜色数                     
	 InfoHeader.biPlanes=1;                //必须设置为1
	 InfoHeader.biCompression=BI_RGB;                                              //设置为BI_RGB时,表示图像并没有彩色表
	 InfoHeader.biBitCount=24;                                                    //图像的位数
	 InfoHeader.biSize=sizeof(BITMAPINFOHEADER);                                  //结构体的大小
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
	 //像素格式设置4字节对齐
	 glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	 //接收出像素的数据
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

void Mouse(int button, int state, int x, int y)        /*当鼠标按下或拿起时会回调该函数*/
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //        l_button_down = TRUE;                /*当l_button_down为true时才可改变相机位置*/
        oldpt.x=x;                      /*记录旧坐标，以便移动发生时计算鼠标移动方向*/
        oldpt.y=y;
        printf("鼠标左键按下\n");
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        //        l_button_down = FALSE;        /*拿起时不能改变摄像机位置*/
        printf("鼠标左键松开\n");
    }
}

void onMouseMove(int x, int y)          /*当鼠标移动时会回调该函数*/
{
    angle-=(x-oldpt.x)/100.0;
    center[1]-=(y-oldpt.y)/50.0;
    oldpt.x=x;
    oldpt.y=y;
    center[0]=-5.0f*sin(angle)+eye[0];
    center[2]=-5.0f*cos(angle)+eye[2];
    printf("%lf %lf\n",center[0],center[2]);
    printf("鼠标移动\n");
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
				  printf("保存图片成功");
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
	键盘上用1,2，3控制贴图切换
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
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
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
