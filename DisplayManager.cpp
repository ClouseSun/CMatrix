//
//  DisplayManager.cpp
//  Vector
//
//  Created by ClouseSun on 16/3/7.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#include "DisplayManager.hpp"

std::vector <CVector3> DisplayManager::vecV;
std::vector <CMatrix> DisplayManager::vecM;
std::vector <int> DisplayManager::vecO;
float DisplayManager::mspeed;
float DisplayManager::rspeed;
float DisplayManager::mx;
float DisplayManager::my;
float DisplayManager::mz;
float DisplayManager::rx;
float DisplayManager::ry;
float DisplayManager::rz;
float DisplayManager::sx;
float DisplayManager::sy;
float DisplayManager::sz;
extern const float eps;

DisplayManager::DisplayManager()
{
    std::vector <CVector3> sv;
    vecV = sv;
    mspeed = 1.0f;
    rspeed = 1.0f;
    mx = my = -1.2f;
    mz = -8.6f;
    rx = ry = rz = 0;
    sx = sy = sz = 1.0f;
}

void DisplayManager::TimeFunc(int val)
{
    DisplayManager::RenderScene();
    glutTimerFunc(1, TimeFunc, 0);
}

void DisplayManager::ChangeSize(int w, int h)
{
    GLfloat nRange = 5.0f;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,GLfloat(w)/h,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();}

void DisplayManager::SetupRC()
{
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_BACK,GL_LINE);
}

void DisplayManager::RenderScene(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glTranslatef(mx, my, mz);
    glRotatef(rz, 0, 0, 1);
    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);
    glScalef(sx, sy, sz);
    
    DrawAxis(5.0f, 3.0f, true, true, 1.0f);
    
    float palette_vec[3][3];
    palette_vec[0][0] = 1.0f;
    palette_vec[0][1] = 1.0f;
    palette_vec[0][2] = 0.0f;
    
    palette_vec[1][0] = 1.0f;
    palette_vec[1][1] = 0.0f;
    palette_vec[1][2] = 1.0f;
    
    palette_vec[2][0] = 0.0f;
    palette_vec[2][1] = 1.0f;
    palette_vec[2][2] = 1.0f;
    
    float palette_mat[3][3];
    palette_mat[0][0] = 1.0f;
    palette_mat[0][1] = 0.0f;
    palette_mat[0][2] = 0.0f;
    
    palette_mat[1][0] = 0.0f;
    palette_mat[1][1] = 1.0f;
    palette_mat[1][2] = 0.0f;
    
    palette_mat[2][0] = 0.0f;
    palette_mat[2][1] = 0.0f;
    palette_mat[2][2] = 1.0f;
    
    if(vecO.size() != 0)
    {
        int num_V;
        
        switch (vecO[vecO.size()-1])
        {
            case 1:
                show_text("Matrix Mutiply Matrix", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 2:
                show_text("matrix multiply number", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 3:
                show_text("matrix multiply vector", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 4:
                show_text("matrix multiply point", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 5:
                show_text("identity", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 6:
                show_text("transcope", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 7:
                show_text("rotate", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 8:
                show_text("scale", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 9:
                show_text("translation", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
            case 10:
                show_text("inverse", 4.0f, 5.0f, 0.0f, 254, 254, 254);
                break;
                
            default:
                break;
        }
        
        if( vecO[vecO.size()-1] == 3 || vecO[vecO.size()-1] == 4)
        {
            num_V = 2;
        }
        else
            num_V = 0;

        
        for(int i = 0 ; i < num_V ; i++)
        {
            DrawVector3(vecV[vecV.size()-1-i], 2.0f, palette_vec[i]);
        }
        
        int num_M;
        if( vecO[vecO.size()-1] == 1)
        {
            num_M = 3;
        }
        else if(vecO[vecO.size()-1] == 3 || vecO[vecO.size()-1] == 4)
        {
            num_M = 1;
        }
        else
            num_M = 2;
        
        for(int i = 0; i < num_M ; i++)
        {
            DrawMatrix(vecM[vecM.size()-1-i], 2.0f, palette_mat[i % 3]);
        }
    }
    glPopMatrix();
    glutSwapBuffers();
}

void DisplayManager::ClearVector()
{
    vecM.clear();
    vecV.clear();
    vecO.clear();
}

void DisplayManager::KeyboardFunc(unsigned char key,int x, int y)
{
    switch(key)
    {
        case 'w':
            my -= mspeed;
            break;
        case 's':
            my += mspeed;
            break;
        case 'a':
            mx += mspeed;
            break;
        case 'd':
            mx -= mspeed;
            break;
        case 'q':
            mz += mspeed;
            break;
        case 'e':
            mz -= mspeed;
            break;
        case 'i':
            rx += rspeed;
            break;
        case 'k':
            rx -= rspeed;
            break;
        case 'j':
            ry -= rspeed;
            break;
        case 'l':
            ry += rspeed;
            break;
        case 'u':
            rz += rspeed;
            break;
        case 'o':
            rz -= rspeed;
            break;
        case '1':
            sx += 0.1;
            break;
        case '2':
            sx -= 0.1;
            break;
        case '3':
            sy += 0.1;
            break;
        case '4':
            sy -= 0.1;
            break;
        case '5':
            sz += 0.1;
            break;
        case '6':
            sz -= 0.1;
            break;
        case 'z':
            mz = -10.0f;
            mx = my = 0.0f;
            ry = -90;
            rx = rz = 0;
            break;
        case 'x':
            mz = -10.0f;
            mx = my = 0.0f;
            rx = 90;
            ry = rz = 0;
            break;
        case 'c':
            mz = -10.0f;
            mx = my = 0.0f;
            rx = ry = 0;
            rz = 0;
            break;
        case 'r':
            mx = my = -1.2f;
            mz = -8.6f;
            rx = ry = rz = 0;
            break;
        case 'p':
            if(vecO.size() != 0)
            {
                if (vecO[vecO.size()-1] == 1)
                {
                    vecO.pop_back();
                    vecM.pop_back();
                    vecM.pop_back();
                    vecM.pop_back();
                }
                else if(vecO[vecO.size()-1] == 3 || vecO[vecO.size()-1] == 4)
                {
                    vecO.pop_back();
                    vecM.pop_back();
                    vecV.pop_back();
                    vecV.pop_back();
                }
                else
                {
                    vecO.pop_back();
                    vecM.pop_back();
                    vecM.pop_back();
                }
            }
    }
}

void DisplayManager::Show(int argc, char* argv[])
{
    for(int i = 0; i< vecM.size()/2;i++)
    {
        CMatrix temp;
        temp = vecM[i];
        vecM[i] = vecM[vecM.size()- i - 1];
        vecM[vecM.size() - i - 1] = temp;
    }
    
    //std::reverse(vecM.begin(), vecM.end());
    std::reverse(vecO.begin(), vecO.end());
    std::reverse(vecV.begin(), vecV.end());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Display");
    glutDisplayFunc(DisplayManager::RenderScene);
    glutTimerFunc(1, TimeFunc, 0);
    glutReshapeFunc(DisplayManager::ChangeSize);
    glutKeyboardFunc(DisplayManager::KeyboardFunc);
    SetupRC();
    glutMainLoop();
}

void DisplayManager::PushCVector3(CVector3 cv3)
{
    this->vecV.push_back(cv3);
}

CVector3 DisplayManager::GetVector(int i)
{
    return vecV[i];
}

void DisplayManager::PushCMatrix(CMatrix cm)
{
    this->vecM.push_back(cm);
}

CMatrix DisplayManager::GetMatrix(int i)
{
    return vecM[i];
}

void DisplayManager::DrawAxis(GLfloat len, GLfloat width, bool coloring, bool label, GLfloat scale)
{
    glLineWidth(width);
    
    if(label)
    {
        char Xlabel[2] = "X";
        show_text(Xlabel, len, 0.2f, 0.0f, 254, 0, 0);
        char Ylabel[2] = "Y";
        show_text(Ylabel, 0.0f, len+0.2, 0.3f, 0, 254, 0);
        char Zlabel[2] = "Z";
        show_text(Zlabel, 0.0f, 0.2f, len, 0, 0, 254);
    }
    
    if(coloring)
        glColor3f(1.0f, 0.0f, 0.0f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(len, 0.0f, 0.0f);
    glEnd();
    
    
    if(scale >= 0)
    {
        int num = len / scale;
        for(int i = 1;i <= num;i++)
        {
            glBegin(GL_LINES);
            glVertex3f(i * scale, 0.0f, 0.0f);
            glVertex3f(i * scale, 0.1f, 0.0f);
            glVertex3f(i * scale, 0.0f, 0.0f);
            glVertex3f(i * scale, 0.0f, 0.1f);
            glEnd();
        }
    }
    
    glPushMatrix();
    glTranslatef(len, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
    
    if(coloring)
        glColor3f(0.0f, 1.0f, 0.0f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, len, 0.0f);
    glEnd();
    
    if(scale >= 0)
    {
        int num = len / scale;
        for(int i = 1;i <= num;i++)
        {
            glBegin(GL_LINES);
            glVertex3f(0.0f, i * scale, 0.0f);
            glVertex3f(0.1f, i * scale, 0.0f);
            glVertex3f(0.0f, i * scale, 0.0f);
            glVertex3f(0.0f, i * scale, 0.1f);
            glEnd();
        }
    }
    
    glPushMatrix();
    glTranslatef(0.0f, len, 0.0f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
    
    if(coloring)
        glColor3f(0.0f, 0.0f, 1.0f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, len);
    glEnd();
    
    if(scale >= 0)
    {
        int num = len / scale;
        for(int i = 1;i <= num;i++)
        {
            glBegin(GL_LINES);
            glVertex3f(0.0f, 0.0f, i * scale);
            glVertex3f(0.1f, 0.0f, i * scale);
            glVertex3f(0.0f, 0.0f, i * scale);
            glVertex3f(0.0f, 0.1f, i * scale);
            glEnd();
        }
    }
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, len);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
    
}

void DisplayManager::show_text(char *text_toshow, double x, double y, double z, float R, float G, float B)
{
    /* There are 7 bitmap fonts available in GLUT.
     GLUT_BITMAP_8_BY_13
     GLUT_BITMAP_9_BY_15
     GLUT_BITMAP_TIMES_ROMAN_10
     GLUT_BITMAP_TIMES_ROMAN_24
     GLUT_BITMAP_HELVETICA_10
     GLUT_BITMAP_HELVETICA_12
     GLUT_BITMAP_HELVETICA_18 */
    
    void* font = GLUT_BITMAP_HELVETICA_18;
    glColor3f(R, G, B);
    glRasterPos3f(x, y, z);
    
    for(int i = 0; i<=strlen(text_toshow); i++)
    {
        char c = text_toshow[i];
        glutBitmapCharacter(font, c);
    }
}

void DisplayManager::DrawVector3(CVector3 cv3, GLfloat width, float *palette)
{
    glLineWidth(width);
    glColor3f(palette[0], palette[1], palette[2]);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(cv3.GetX(),cv3.GetY(),cv3.GetZ());
    glEnd();
    
//    glPushMatrix();
//    glTranslatef(cv3.GetX(), cv3.GetY(), cv3.GetZ());
//    glutWireCone(0.09, 0.3, 10, 10);
//    glPopMatrix();
    
}

void DisplayManager::DrawMatrix(CMatrix cm, GLfloat width, float *palette)
{
    DrawVector3(cm.GetCol(0), 2.0f, palette);
    DrawVector3(cm.GetCol(1), 2.0f, palette);
    DrawVector3(cm.GetCol(2), 2.0f, palette);
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple (1, 0x0F0F);
    glColor3f(palette[0], palette[1], palette[2]);
    glLineWidth(0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(cm.GetCol(0).GetX(), cm.GetCol(0).GetY(), cm.GetCol(0).GetZ());
    glVertex3f(cm.GetCol(1).GetX(), cm.GetCol(1).GetY(), cm.GetCol(1).GetZ());
    glVertex3f(cm.GetCol(2).GetX(), cm.GetCol(2).GetY(), cm.GetCol(2).GetZ());
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}
