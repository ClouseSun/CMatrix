//
//  DisplayManager.hpp
//  Vector
//
//  Created by ClouseSun on 16/3/7.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#ifndef DisplayManager_hpp
#define DisplayManager_hpp


#include "CVector3.hpp"
#include "CMatrix.hpp"
#include <vector>
#include <time.h>
#include <algorithm>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

/* DisplayManager -- display vector user input from cmdline in various perspective */

class DisplayManager
{
    static std::vector <CVector3> vecV; /* store input and result vectors, maybe 2 or 3. */
    static std::vector <CMatrix> vecM;
    static float mspeed; /* move step each key press */
    static float rspeed; /* rotate angle each key press */
    static float mx,my,mz; /* x/y/z component of the vector offset from origion */
    static float rx,ry,rz; /* rotation angle from X/Y/Z axis , */
    static float sx,sy,sz; /* x/y/z scale component */
    
public:
    static std::vector <int> vecO;
    
    DisplayManager();
    
    /*
     *  Reset viewport when window size changed
     */
    
    static void ChangeSize(int w, int h);
    
    /*
     *  Initialize the rendering context
     */
    
    void SetupRC();
    
    /*
     *  Receive keyboard input to change view
     */
    
    static void KeyboardFunc(unsigned char key,int x, int y);
    
    /*
     *  Called to draw axis and vectors
     */
    
    static void RenderScene(void);
    
    /*
     *  Called to draw axis and vectors
     */
    
    static void TimeFunc(int val);
    
    /*
     *  Main depicting func
     */
    
    void Show(int argc, char* argv[]);
    
    /*
     *  Push vector
     */
    
    void PushCVector3(CVector3 cv3);
    
    /*
     *  Get no.i vector
     */
    
    CVector3 GetVector(int i);
    
    /*
     *  clear all vector
     */
    
    void ClearVector();
    
    /*
     *  Push matrix
     */
    
    void PushCMatrix(CMatrix cm);
    
    /*
     *  Get no.i matrix
     */
    
    CMatrix GetMatrix(int i);
    
    /*
     *  Draw 3 dimensional axis
     *  Parameters:
     *      len : length of the axis
     *      width : weight of the axis
     *      coloring : true if axis colored (X red, Y green, Z blue), white if false
     *      label : true if X/Y/Z labeled on each axis , false if not
     *      scale : length for each scale (1.0f width 0.1f length), 0 for no scale
     */
    
    static void DrawAxis(GLfloat len, GLfloat width, bool coloring, bool label, GLfloat scale);
    
    /*
     *  Draw all vectors in the stack
     *  Parameters:
     *      width : weight of the vector
     *      coloring : true if vector colored , white if false
     */
    
    static void DrawVector3(CVector3 cv3, GLfloat width, float* palette);
    
    /*
     *  Show the input text on (x, y, z)
     */
    
    static void show_text(char *text_toshow, double x, double y, double z, float R, float G, float B);
    
    static void DrawMatrix(CMatrix cm, GLfloat width, float *palette);
    
};

#endif /* DisplayManager_hpp */
