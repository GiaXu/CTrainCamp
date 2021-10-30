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

static unsigned int s_mask = 0xffffff;
static int number = 0;

void initWindow();
void display();
void reshape(int width, int height);
void onAscIIKey(unsigned char ch, int mouseX, int mouseY);
void showStrokes_Right(unsigned char mask);
void showStrokes_Left(unsigned char mask);
void showStrokes_Center(unsigned char mask);
unsigned char getRightMask();
unsigned char getLeftMask();
unsigned char getCenterMask();
void setRightMask(unsigned char mask);
void setLeftMask(unsigned char mask);
void setCenterMask(unsigned char mask); 
void drawDigital();
void drawLeftDigital();
void drawRightDigital();
void drawCenterDigital();
void setDigital(int num);

   float matScale4x4centerUP[] = { 0.5f, 0.f, 0.f, 0.f,
                            0.f, 0.5f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.5f, 0.f, 1.f };

    float matScale4x4Left[] = { 0.5f, 0.f, 0.f, 0.f,
                            0.f, 0.5f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            -0.5f, 0.f, 0.f, 1.f };

    float matScale4x4Right[] = { 0.5f, 0.f, 0.f, 0.f,
                            0.f, 0.5f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.5f, 0.f, 0.f, 1.f };

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);

    initWindow();

    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);
    glutKeyboardFunc(onAscIIKey);

    setDigital(857);

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


    glLoadMatrixf(matScale4x4centerUP);

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
    if (num < 0 || num > 999)
    {
        // error
    }
    int numLow = num % 10;
    int numMiddle = (num - numLow) / 10 % 10;
    int numHigh = (num - numLow) / 100;
    setLeftMask(calcMask(numHigh));
    setRightMask(calcMask(numLow));
    setCenterMask(calcMask(numMiddle));

}

void drawDigital()
{
    glLoadMatrixf(matScale4x4Left);
    drawLeftDigital();
    glLoadMatrixf(matScale4x4Right);
    drawRightDigital();
    glLoadMatrixf(matScale4x4centerUP);
    drawCenterDigital();
    
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

unsigned char getCenterMask()
{
    return (unsigned char)(s_mask >> 16);
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

void setCenterMask(unsigned char mask)   
{
    unsigned int centerMask = mask;
    s_mask &= 0xffff;
    s_mask |= (centerMask << 16);
}

void drawLeftDigital()
{
    showStrokes_Left(getLeftMask());
}

void drawRightDigital()
{
    showStrokes_Right(getRightMask());
}


void drawCenterDigital()
{
    showStrokes_Center(getCenterMask());
}

void onAscIIKey(unsigned char ch,int mouseX,int mouseY)
{
    if(number > 99)
    {
        number = 0;
    }
    number = (number * 10) + (ch - '0');
    
    setDigital(number);

    glutPostRedisplay();
}


void showStrokes_Right(unsigned char mask)
{
    glColor3f(1.f,0.8f,0.2f);

    if (mask & TOP)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.65f,0.625f,0.f);
        glVertex3f(0.75f,0.775f,0.f);
        glVertex3f(0.35f,0.775f,0.f);
        glVertex3f(0.45f,0.625f,0.f);
        glEnd();
    }

    if (mask & TOP_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.45f,0.575f,0.f);
        glVertex3f(0.35f,0.725f,0.f);
        glVertex3f(0.35f,0.05f,0.f);
        glVertex3f(0.45f,0.125f,0.f);
        glEnd();
    }

    if (mask & TOP_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.75f,0.725f,0.f);
        glVertex3f(0.65f,0.575f,0.f);
        glVertex3f(0.65f,0.125f,0.f);
        glVertex3f(0.75f,0.05f,0.f);
        glEnd();
    }

    if (mask & CENTER)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.75f,0.f,0.f);
        glVertex3f(0.65f,0.075f,0.f);
        glVertex3f(0.45f,0.075f,0.f);
        glVertex3f(0.35f,0.f,0.f);
        glVertex3f(0.45f,-0.075f,0.f);
        glVertex3f(0.65f,-0.075f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.45f,-0.125f,0.f);
        glVertex3f(0.35f,-0.05f,0.f);
        glVertex3f(0.35f,-0.725f,0.f);
        glVertex3f(0.45f,-0.575f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.75f,-0.05f,0.f);
        glVertex3f(0.65f,-0.125f,0.f);
        glVertex3f(0.65f,-0.575f,0.f);
        glVertex3f(0.75f,-0.725f,0.f);
        glEnd();
    }

    if(mask & BOTTOM)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.75f,-0.775f,0.f);
        glVertex3f(0.65f,-0.625f,0.f);
        glVertex3f(0.45f,-0.625f,0.f);
        glVertex3f(0.35f,-0.775f,0.f);
        glEnd();
    }
}


void showStrokes_Left(unsigned char mask)
{
    glColor3f(1.f,0.8f,0.2f);

    if (mask & TOP)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.45f,0.625f,0.f);
        glVertex3f(-0.35f,0.775f,0.f);
        glVertex3f(-0.75f,0.775f,0.f);
        glVertex3f(-0.65f,0.625f,0.f);
        glEnd();
    }

    if (mask & TOP_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.65f,0.575f,0.f);
        glVertex3f(-0.75f,0.725f,0.f);
        glVertex3f(-0.75f,0.05f,0.f);
        glVertex3f(-0.65f,0.125f,0.f);
        glEnd();
    }

    if (mask & TOP_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.35f,0.725f,0.f);
        glVertex3f(-0.45f,0.575f,0.f);
        glVertex3f(-0.45f,0.125f,0.f);
        glVertex3f(-0.35f,0.05f,0.f);
        glEnd();
    }

    if (mask & CENTER)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.35f,0.f,0.f);
        glVertex3f(-0.45f,0.075f,0.f);
        glVertex3f(-0.65f,0.075f,0.f);
        glVertex3f(-0.75f,0.f,0.f);
        glVertex3f(-0.65f,-0.075f,0.f);
        glVertex3f(-0.45f,-0.075f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.65f,-0.125f,0.f);
        glVertex3f(-0.75f,-0.05f,0.f);
        glVertex3f(-0.75f,-0.725f,0.f);
        glVertex3f(-0.65f,-0.575f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.35f,-0.05f,0.f);
        glVertex3f(-0.45f,-0.125f,0.f);
        glVertex3f(-0.45f,-0.575f,0.f);
        glVertex3f(-0.35f,-0.725f,0.f);
        glEnd();
    }

    if(mask & BOTTOM)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.35f,-0.775f,0.f);
        glVertex3f(-0.45f,-0.625f,0.f);
        glVertex3f(-0.65f,-0.625f,0.f);
        glVertex3f(-0.75f,-0.775f,0.f);
        glEnd();
    }
}

void showStrokes_Center(unsigned char mask)
{
    glColor3f(1.f,0.8f,0.2f);

    if (mask & TOP)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.1f,0.625f,0.f);
        glVertex3f(0.2f,0.775f,0.f);
        glVertex3f(-0.2f,0.775f,0.f);
        glVertex3f(-0.1f,0.625f,0.f);
        glEnd();
    }

    if (mask & TOP_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.1f,0.575f,0.f);
        glVertex3f(-0.2f,0.725f,0.f);
        glVertex3f(-0.2f,0.05f,0.f);
        glVertex3f(-0.1f,0.125f,0.f);
        glEnd();
    }

    if (mask & TOP_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.2f,0.725f,0.f);
        glVertex3f(0.1f,0.575f,0.f);
        glVertex3f(0.1f,0.125f,0.f);
        glVertex3f(0.2f,0.05f,0.f);
        glEnd();
    }

    if (mask & CENTER)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.2f,0.f,0.f);
        glVertex3f(0.1f,0.075f,0.f);
        glVertex3f(-0.1f,0.075f,0.f);
        glVertex3f(-0.2f,0.f,0.f);
        glVertex3f(-0.1f,-0.075f,0.f);
        glVertex3f(0.1f,-0.075f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_LEFT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(-0.1f,-0.125f,0.f);
        glVertex3f(-0.2f,-0.05f,0.f);
        glVertex3f(-0.2f,-0.725f,0.f);
        glVertex3f(-0.1f,-0.625f,0.f);
        glEnd();
    }

    if(mask & BOTTOM_RIGHT)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.2f,-0.05f,0.f);
        glVertex3f(0.1f,-0.125f,0.f);
        glVertex3f(0.1f,-0.575f,0.f);
        glVertex3f(0.2f,-0.725f,0.f);
        glEnd();
    }

    if(mask & BOTTOM)
    {
        glBegin(GL_POLYGON);
        glVertex3f(0.2f,-0.775f,0.f);
        glVertex3f(0.1f,-0.625f,0.f);
        glVertex3f(-0.1f,-0.625f,0.f);
        glVertex3f(-0.2f,-0.775f,0.f);
        glEnd();
    }
}



