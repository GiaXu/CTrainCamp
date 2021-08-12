#include <stdio.h>
#include <GLUT/glut.h>

enum EmStrokes
{
    TOP = 0x01,
    TOP_LEFT = 0x02,
    TOP_RIGHT = 0x04,
    CENTER = 0x08,
    BOTTOM_LEFT = 0x10,
    BOTTOM_RIGHT = 0x20,
    BOTTOM = 0x40

};

static unsigned int s_mask = 0xffff;
static int number = 0;

void initWindow();
void display();
void reshape(int width, int height);
void onAscIIKey(unsigned char ch, int mouseX, int mouseY);
void showStrokes_Right(unsigned char mask);
void showStrokes_Left(unsigned char mask);
unsigned char getRightMask();
unsigned char getLeftMask();
void setRightMask(unsigned char mask);
void setLeftMask(unsigned char mask);
void drawDigital();
void drawLeftDigital();
void drawRightDigital();
void setDigital(int num);

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);

    initWindow();

    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);
    glutKeyboardFunc(onAscIIKey);

    setDigital(56);

    glutMainLoop();

    return 0;
}


void initWindow()
{
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,400);
    glutCreateWindow("Hello OpenGL");
}

void display()
{
    glClearColor(0.4f,0.6f,0.8f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glEnable(GL_CULL_FACE);

    drawDigital();
   
    glutSwapBuffers();
}

unsigned char calcMask(int num)
{
    num %= 10;
    switch (num)
    {
        case 0:
         return (unsigned char)(TOP | TOP_LEFT | BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT | TOP_RIGHT);

        case 1:
         return (unsigned char)(TOP_RIGHT | BOTTOM_RIGHT );

        case 2:
         return (unsigned char)(TOP | TOP_RIGHT | CENTER | BOTTOM_LEFT | BOTTOM);

        case 3: 
         return (unsigned char)(TOP | TOP_RIGHT | CENTER | BOTTOM_RIGHT | BOTTOM);

        case 4:
         return (unsigned char)(TOP_LEFT | TOP_RIGHT | CENTER | BOTTOM_RIGHT);
          
        case 5:
         return (unsigned char)(TOP | TOP_LEFT | CENTER | BOTTOM_RIGHT | BOTTOM);

        case 6:
         return (unsigned char)(TOP | TOP_LEFT | CENTER | BOTTOM_LEFT | BOTTOM | BOTTOM_RIGHT);

        case 7:
         return (unsigned char)(TOP | TOP_RIGHT | BOTTOM_RIGHT);

        case 8:
         return (unsigned char)(TOP | TOP_LEFT | TOP_RIGHT | CENTER | BOTTOM | BOTTOM_LEFT | BOTTOM_RIGHT);

        case 9:
         return (unsigned char)(TOP | TOP_LEFT | TOP_RIGHT | CENTER | BOTTOM_RIGHT | BOTTOM);

        default :
        return 0;
    }
    
}

void setDigital(int num)
{
    if (num < 0 || num > 99)
    {
        // error
    }
    int numLow = num % 10;
    int numHigh = num / 10;
    setLeftMask(calcMask(numHigh));
    setRightMask(calcMask(numLow));
}

void drawDigital()
{
    drawLeftDigital();
    drawRightDigital();
}

void reshape(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);
}

unsigned char getRightMask()
{
    return (unsigned char) s_mask;
}

unsigned char getLeftMask()
{
    return (unsigned char)(s_mask >> 8);
}

void setRightMask(unsigned char mask)
{
    s_mask &= 0xff00;
    s_mask |= mask;
}

void setLeftMask(unsigned char mask)
{
    unsigned int leftMask = mask;
    s_mask &= 0xff;
    s_mask |= (leftMask << 8);
}

void drawLeftDigital()
{
    showStrokes_Left(getLeftMask());
}

void drawRightDigital()
{
    showStrokes_Right(getRightMask());
}

void onAscIIKey(unsigned char ch,int mouseX,int mouseY)
{
    if(number > 9)
    {
        number = 0;
    }
    number = (number * 10) + (ch - '0');
    /*
   if(number >= 10)
   {
       number = 0;
   }
   if(number >= 0 || number < 10)
   {
       number = number * 10;
   }
    number += (ch - '0');
    */
    setDigital(number);

    glutPostRedisplay();
}


void showStrokes_Right(unsigned char mask)
{
    glColor3f(1.f,0.8f,0.2f);

    if (mask & TOP)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.375f,0.625f,0.f);
        glVertex3f(0.475f,0.775f,0.f);
        glVertex3f(0.075f,0.775f,0.f);
        glVertex3f(0.175f,0.625f,0.f);
        glEnd();
    }

    if (mask & TOP_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.175f,0.575f,0.f);
        glVertex3f(0.075f,0.725f,0.f);
        glVertex3f(0.075f,0.05f,0.f);
        glVertex3f(0.175f,0.125f,0.f);
        glEnd();
    }

    if (mask & TOP_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.475f,0.725f,0.f);
        glVertex3f(0.375f,0.575f,0.f);
        glVertex3f(0.375f,0.125f,0.f);
        glVertex3f(0.475f,0.05f,0.f);
        glEnd();
    }

    if (mask & CENTER)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.475f,0.f,0.f);
        glVertex3f(0.375f,0.075f,0.f);
        glVertex3f(0.175f,0.075f,0.f);
        glVertex3f(0.075f,0.f,0.f);
        glVertex3f(0.175f,-0.075f,0.f);
        glVertex3f(0.375f,-0.075f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.175f,-0.125f,0.f);
        glVertex3f(0.075f,-0.05f,0.f);
        glVertex3f(0.075f,-0.725f,0.f);
        glVertex3f(0.175f,-0.575f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.475f,-0.05f,0.f);
        glVertex3f(0.375f,-0.125f,0.f);
        glVertex3f(0.375f,-0.575f,0.f);
        glVertex3f(0.475f,-0.725f,0.f);
        glEnd();
    }

    if(mask & BOTTOM)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.475f,-0.775f,0.f);
        glVertex3f(0.375f,-0.625f,0.f);
        glVertex3f(0.175f,-0.625f,0.f);
        glVertex3f(0.075f,-0.775f,0.f);
        glEnd();
    }
}


void showStrokes_Left(unsigned char mask)
{
    glColor3f(1.f,0.8f,0.2f);

    if (mask & TOP)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.175f,0.625f,0.f);
        glVertex3f(-0.075f,0.775f,0.f);
        glVertex3f(-0.475f,0.775f,0.f);
        glVertex3f(-0.375f,0.625f,0.f);
        glEnd();
    }

    if (mask & TOP_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.375f,0.575f,0.f);
        glVertex3f(-0.475f,0.725f,0.f);
        glVertex3f(-0.475f,0.05f,0.f);
        glVertex3f(-0.375f,0.125f,0.f);
        glEnd();
    }

    if (mask & TOP_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.075f,0.725f,0.f);
        glVertex3f(-0.175f,0.575f,0.f);
        glVertex3f(-0.175f,0.125f,0.f);
        glVertex3f(-0.075f,0.05f,0.f);
        glEnd();
    }

    if (mask & CENTER)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.475f,0.f,0.f);
        glVertex3f(-0.375f,-0.075f,0.f);
        glVertex3f(-0.175f,-0.075f,0.f);
        glVertex3f(-0.075f,0.f,0.f);
        glVertex3f(-0.175f,0.075f,0.f);
        glVertex3f(-0.375f,0.075f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.375f,-0.125f,0.f);
        glVertex3f(-0.475f,-0.05f,0.f);
        glVertex3f(-0.475f,-0.725f,0.f);
        glVertex3f(-0.375f,-0.575f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.075f,-0.05f,0.f);
        glVertex3f(-0.175f,-0.125f,0.f);
        glVertex3f(-0.175f,-0.575f,0.f);
        glVertex3f(-0.075f,-0.725f,0.f);
        glEnd();
    }

    if(mask & BOTTOM)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.075f,-0.775f,0.f);
        glVertex3f(-0.175f,-0.625f,0.f);
        glVertex3f(-0.375f,-0.625f,0.f);
        glVertex3f(-0.475f,-0.775f,0.f);
        glEnd();
    }
}

