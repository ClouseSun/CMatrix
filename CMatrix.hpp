//
//  CMatrix.hpp
//  CMatrix
//
//  Created by ClouseSun on 16/3/15.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//
//  m00 m01 m02 m03
//  m10 m11 m12 m13
//  m20 m21 m22 m23
//  m30 m31 m32 m33

#ifndef CMatrix_hpp
#define CMatrix_hpp

#include <stdio.h>
#include "CVector3.hpp"

class CMatrix
{
    float m00,m01,m02,m03,
          m10,m11,m12,m13,
          m20,m21,m22,m23,
          m30,m31,m32,m33;
public:
    CMatrix();
    CMatrix (const CMatrix &assign);
    void SetMatrix(float *val);
    void SetRow(int i,CVector3 p);
    void SetCol(int i,CVector3 p);
    
    CVector3 GetRow(int i);
    CVector3 GetCol(int i);
    
    operator float* () {return &m00;};
    
    void operator = (CMatrix &src);
    CMatrix operator * (float factor);
    CMatrix operator * (CMatrix &src);
    CVector3 operator * (CVector3 &src);
    CVector3 Mulpoint(CVector3 &src);
    
    void Identity();
    CMatrix Transpose();
    CMatrix SetTrans(CVector3 trans);
    CMatrix SetRotate(double seta,CVector3 axis);
    CMatrix SetScale(CVector3 src);
    float Inverse();
    CMatrix GetInverse();
    float Determinant33(float a1,float a2,float a3,float b1,float b2,float b3,float c1,float c2,float c3);
    float Determinant44();
    
    void Output();
};

#endif /* CMatrix_hpp */
