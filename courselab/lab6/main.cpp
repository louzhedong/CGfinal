// glutEx1.cpp : �������̨Ӧ�ó������ڵ㡣  
//  
#include <stdlib.h>  
#include <windows.h>  
#include <stdio.h>  
#include <gl/glut.h>  
  
#define BITMAP_ID 0x4D42  
  
GLubyte image[16][16][3];  // �Լ����Ƶ��������� 
GLuint texture[3]; 

float fTranslate;  
float fRotate;  
float fScale     = 1.0f;    // set inital scale value to 1.0f  
  
int teapottex = 0;   

bool bPersp = false;  
bool bAnim = false;  
bool bWire = false;  
  
int wHeight = 0;  
int wWidth = 0;  
  

void Draw_Leg();  
  
// �����ʾ�����飬������������ı�ʾ��  
// ����: ͨ��ָ�룬����filename ָ����bitmap�ļ������ݡ�  
// ͬʱҲ����bitmap��Ϣͷ.����֧��-bitλͼ��  
  
  
//������ͼƬ  
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)  
{  
    FILE *filePtr;    // �ļ�ָ��  
    BITMAPFILEHEADER bitmapFileHeader;    // bitmap�ļ�ͷ  
    unsigned char    *bitmapImage;        // bitmapͼ������  
    int    imageIdx = 0;        // ͼ��λ������  
    unsigned char    tempRGB;    // ��������  
  
                                // �ԡ�������+����ģʽ���ļ�filename   
    filePtr = fopen(filename, "rb");  
    if (filePtr == NULL) {  
        printf("file not open\n");  
        return NULL;  
    }  
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
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {  
        tempRGB = bitmapImage[imageIdx];  
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];  
        bitmapImage[imageIdx + 2] = tempRGB;  
    }  
    // �ر�bitmapͼ���ļ�  
    fclose(filePtr);  
    return bitmapImage;  
}  
  
//��������ĺ���  
void texload(int i, char *filename)  
{  
    BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap��Ϣͷ  
    unsigned char*   bitmapData;                                       // ��������  
  
    bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);  
    glBindTexture(GL_TEXTURE_2D, texture[i]);  
    // ָ����ǰ����ķŴ�/��С���˷�ʽ  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
  
    glTexImage2D(GL_TEXTURE_2D,  
        0,         //mipmap���(ͨ��Ϊ����ʾ���ϲ�)   
        GL_RGB,    //����ϣ���������к졢�̡�������  
        bitmapInfoHeader.biWidth, //��������������n�����б߿�+2   
        bitmapInfoHeader.biHeight, //����߶ȣ�������n�����б߿�+2   
        0, //�߿�(0=�ޱ߿�, 1=�б߿�)   
        GL_RGB,    //bitmap���ݵĸ�ʽ  
        GL_UNSIGNED_BYTE, //ÿ����ɫ���ݵ�����  
        bitmapData);    //bitmap����ָ��    
}  
  
void drawMyTex()  
{  
    //����ͼ��  
    for (int i = 0; i < 16; i++) {  
        for (int j = 0; j < 16; j++) {  
			int x = 0;
			if((i&4)^(j&4)==0)
				x=255;
            image[i][j][0] = (GLubyte)x;    //R
            image[i][j][1] = (GLubyte)0;	//G
            image[i][j][2] = (GLubyte)0;	//B
        }  
    }  
}  
  
//��������ĺ���  
void init()  
{  
    glGenTextures(3, texture); // ��һ��������Ҫ���ɱ�ʾ���ĸ���, �ڶ������Ƿ��ر�ʾ��������  
    texload(0, "Monet.bmp");  
    texload(1, "Crack.bmp");  
    //���������Զ�������  
    drawMyTex();  
    glBindTexture(GL_TEXTURE_2D, texture[2]);  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ.  
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, image);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//�Ŵ���ˣ����Թ���  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//��С���ˣ����Թ���  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//S�����ظ�  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//T�����ظ�  
}  
  
void drawCube()  
{  
    int i, j;  
    const GLfloat x1 = -0.5, x2 = 0.5;  
    const GLfloat y1 = -0.5, y2 = 0.5;  
    const GLfloat z1 = -0.5, z2 = 0.5;  
  
    //ָ����������ĸ����㣬ÿ��������3������ֵ��ʾ    
    GLfloat point[6][4][3] = {  
        { { x1,y1,z1 },{ x2,y1,z1 },{ x2,y2,z1 },{ x1,y2,z1 } },  
        { { x1,y1,z1 },{ x2,y1,z1 },{ x2,y1,z2 },{ x1,y1,z2 } },  
        { { x2,y1,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x2,y1,z2 } },  
        { { x1,y1,z1 },{ x1,y2,z1 },{ x1,y2,z2 },{ x1,y1,z2 } },  
        { { x1,y2,z1 },{ x2,y2,z1 },{ x2,y2,z2 },{ x1,y2,z2 } },  
        { { x1,y1,z2 },{ x2,y1,z2 },{ x2,y2,z2 },{ x1,y2,z2 } }  
    };  
    int dir[4][2] = { {1,1},{1,0},{0,0},{0,1} };  
    //���������λ���ģʽ    
  
    glBegin(GL_QUADS);  
    for (i = 0; i < 6; i++) {  
        for (j = 0; j < 4; j++) {  
            glTexCoord2iv(dir[j]);  
            glVertex3fv(point[i][j]);  
        }  
    }  
    glEnd();  
      
}  
  
void Draw_Triangle() // This function draws a triangle with RGB colors  
{  
    glEnable(GL_TEXTURE_2D);  
    glBindTexture(GL_TEXTURE_2D, texture[teapottex]);  //ѡ������texture[teapottex]  
    glPushMatrix();  
    glTranslatef(0, 0, 4+1);  
    glRotatef(90, 1, 0, 0);  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//���������ܹ���Ӱ��  
    glutSolidTeapot(1);  
    glPopMatrix();  
    glDisable(GL_TEXTURE_2D);    //�ر�����texture[teapottex]  
  
    glEnable(GL_TEXTURE_2D);  
    glBindTexture(GL_TEXTURE_2D, texture[1]);  //ѡ������texture[1]  
  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//���������ܹ���Ӱ��  
    glPushMatrix();  
    glTranslatef(0, 0, 3.5);  
    glScalef(5, 4, 1);  
    drawCube();  
    glPopMatrix();  
  
    glPushMatrix();  
    glTranslatef(1.5, 1, 1.5);  
    Draw_Leg();  
    glPopMatrix();  
  
    glPushMatrix();  
    glTranslatef(-1.5, 1, 1.5);  
    Draw_Leg();  
    glPopMatrix();  
  
    glPushMatrix();  
    glTranslatef(1.5, -1, 1.5);  
    Draw_Leg();  
    glPopMatrix();  
  
    glPushMatrix();  
    glTranslatef(-1.5, -1, 1.5);  
    Draw_Leg();  
    glPopMatrix();  
    glDisable(GL_TEXTURE_2D); //�ر�����texture[1]  
}  
  
void Draw_Leg()  
{  
    glScalef(1, 1, 3);  
    drawCube();  
}  
  
void updateView(int width, int height)  
{  
    glViewport(0, 0, width, height);//�����Ӵ���С    
  
    glMatrixMode(GL_PROJECTION);//���þ���ģʽΪͶӰ     
    glLoadIdentity();   //��ʼ������Ϊ��λ����        
  
    float whRatio = (GLfloat)width / (GLfloat)height;  //������ʾ����      
    if (bPersp) {  
        gluPerspective(45.0f, whRatio, 0.1f, 100.0f); //͸��ͶӰ      
                                                      //glFrustum(-3, 3, -3, 3, 3,100);    
    }  
    else {  
        glOrtho(-3, 3, -3, 3, -100, 100);  //��ͶӰ    
    }  
  
    glMatrixMode(GL_MODELVIEW);  //���þ���ģʽΪģ��    
}  
  
void reshape(int width, int height)  
{  
    if (height == 0)      //����߶�Ϊ0    
    {  
        height = 1;   //�ø߶�Ϊ1��������ַ�ĸΪ0������    
    }  
  
    wHeight = height;  
    wWidth = width;  
  
    updateView(wHeight, wWidth); //�����ӽ�    
}  
  
void idle()  
{  
    glutPostRedisplay();  
}  
  
float eye[] = {0, 0, 8};  
float center[] = {0, 0, 0};  
  
void key(unsigned char k, int x, int y)  
{  
    switch (k)  
    {  
    case 27:  
    case 'q': {exit(0); break; }   
    case 'p': {bPersp = !bPersp; break; }  
  
    case ' ': {bAnim = !bAnim; break; }  
    case 'o': {bWire = !bWire; break; }  
  
    case 'a': {  
        eye[0] -= 0.2f;  
        center[0] -= 0.2f;  
        break;  
    }  
    case 'd': {  
        eye[0] += 0.2f;  
        center[0] += 0.2f;  
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
    case 'v': { //�л��������  
        if (teapottex == 0)teapottex = 2;  
        else if (teapottex == 2)teapottex = 0;  
        break;  
    }  
    }  
  
    updateView(wHeight, wWidth);//�����ӽ�  
}  
  
  
void redraw()  
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ�������Ȼ���     
    glLoadIdentity();    //��ʼ������Ϊ��λ����      
  
    gluLookAt(eye[0], eye[1], eye[2],  
        center[0], center[1], center[2],  
        0, 1, 0);                // ������0��0��0�����ӵ����� (0,5,50)��Y������  
  
    if (bWire) {  
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
        //���ö���λ���ģʽ�������棬����    
    }  
    else {  
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
        //���ö���λ���ģʽ�������棬���        
    }  
      
    glEnable(GL_DEPTH_TEST);//������Ȳ���      
    glEnable(GL_LIGHTING);  //��������ģʽ     
  
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };  
    GLfloat light_pos[] = { 5,5,5,1 };  
  
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);//��Դλ��  
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);//�����ɫ   
    glEnable(GL_LIGHT0);//������0�Ź�Դ     
  
    glRotatef(fRotate, 0, 1.0f, 0);    //��ת  
    glRotatef(-90, 1, 0, 0);  
    glScalef(0.2, 0.2, 0.2);//����  
    Draw_Triangle();//���Ƴ���  
  
    if (bAnim) fRotate    += 0.5f;//��ת���Ӹı�  
    glutSwapBuffers(); //����������  
}  
  
int main(int argc, char *argv[])  
{  
    glutInit(&argc, argv);//��glut�ĳ�ʼ��       
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);  
    //��ʼ����ʾģʽ:RGB��ɫģ�ͣ���Ȳ��ԣ�˫����         
    glutInitWindowSize(480, 480);//���ô��ڴ�С       
    int windowHandle = glutCreateWindow("Simple GLUT App");//���ô��ڱ���     
  
    glutDisplayFunc(redraw); //ע����ƻص�����       
    glutReshapeFunc(reshape);   //ע���ػ�ص�����       
    glutKeyboardFunc(key); //ע�ᰴ���ص�����     
    glutIdleFunc(idle);//ע��ȫ�ֻص�����������ʱ����     
    init(); //��ʼ������  
    glutMainLoop();  // glut�¼�����ѭ��     
    return 0;  
}  