//
//  CVector3.hpp
//  Vector
//
//  Created by ClouseSun on 16/3/7.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#ifndef CVector3_h
#define CVector3_h

#include <iostream>
#include <math.h>

/* CVector3 -- 3 dimensional vector class */

const float eps = 1e-6; /* set desired precision */

class CVector3
{
    float x; /* X-coordinate of the vector */
    float y; /* Y-coordinate of the vector */
    float z; /* Z-coordinate of the vector */
    
public:
    
    /*
     *  Default constructor
     */
    
    CVector3();
    
    /*
     *  Constructor with 3 coordinates
     *  Parameters:
     *      sx : X-coordinate of the vector
     *      sy : Y-coordinate of the vector
     *      sz : Z-coordinate of the vector
     */
    
    CVector3(float sx,float sy,float sz);
    
    /*
     *  Copy constructor
     */
    
    CVector3(const CVector3 &src);
    
    /*
     *  Return x,y,z coordinate of the vector
     */
    
    float GetX();
    float GetY();
    float GetZ();
    
    /*
     *  Reset vector
     */
    
    void Set(float sx, float sy, float sz);
    
    /*
     *  Return length of the vector
     */
    
    float GetLength();
    
    /*
     *  +，-，=, *, / operator overloading of the vector
     */
    
    void operator = (const CVector3 &src);
    CVector3 operator + (const CVector3 &src);
    CVector3 operator - (const CVector3 &src);
    CVector3 operator * (float scale);
    CVector3 operator / (float scale);
    
    /*
     *  Return the result of dotproduct with source vector
     */
    
    float DotProduct(CVector3 src);
    
    /*
     *  Return the result vector of crossproduct with source vector
     */
    
    CVector3 CrossProduct(CVector3 src);
    
    /*
     *  Inverse the vector
     */
    
    void Inverse();
    
    /*
     *  Normalize the vector
     */
    
    void Normalize();
    
    /*
     *  Output the vector in the form of (x,y,z)
     */
    
    void Output();
    
    /*
     *  Project vector on dest vector
     *  Return:
     *      projection vector
     */
    
    CVector3 Project(CVector3 des);
};

#endif /* CVector3_h */
