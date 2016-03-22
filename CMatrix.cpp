//
//  CMatrix.cpp
//  CMatrix
//
//  Created by 孙云霄 on 16/3/15.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//
//  m00 m01 m02 m03
//  m10 m11 m12 m13
//  m20 m21 m22 m23
//  m30 m31 m32 m33

//  m0 m1 m2 m3
//  m4 m5 m6 m7
//  m8 m9 m10 m11
//  m12 m13 m14 m15

#include "CMatrix.hpp"

CMatrix::CMatrix()
{
    m00 = m11 = m22 = m33 = 1;
    m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m23 = m30 = m31 = m32 = 0;
}

CMatrix::CMatrix(const CMatrix &assign)
{
    m00 = assign.m00;
    m01 = assign.m01;
    m02 = assign.m02;
    m03 = assign.m03;
    m10 = assign.m10;
    m11 = assign.m11;
    m12 = assign.m12;
    m13 = assign.m13;
    m20 = assign.m20;
    m21 = assign.m21;
    m22 = assign.m22;
    m23 = assign.m23;
    m30 = assign.m30;
    m31 = assign.m31;
    m32 = assign.m32;
    m33 = assign.m33;
}

void CMatrix::SetMatrix(float *val)
{
    m00 = *(val + 0);
    m01 = *(val + 1);
    m02 = *(val + 2);
    m03 = *(val + 3);
    m10 = *(val + 4);
    m11 = *(val + 5);
    m12 = *(val + 6);
    m13 = *(val + 7);
    m20 = *(val + 8);
    m21 = *(val + 9);
    m22 = *(val + 10);
    m23 = *(val + 11);
    m30 = *(val + 12);
    m31 = *(val + 13);
    m32 = *(val + 14);
    m33 = *(val + 15);
}

void CMatrix::SetRow(int i, CVector3 p)
{
    (*this)[4 * i] = p.GetX();
    (*this)[4 * i + 1] = p.GetY();
    (*this)[4 * i + 2] = p.GetZ();
    (*this)[4 * i + 3] = 0;
}

void CMatrix::SetCol(int i,CVector3 p)
{
    (*this)[i + 0] = p.GetX();
    (*this)[i + 4] = p.GetY();
    (*this)[i + 8] = p.GetZ();
    (*this)[i + 12] = 0;
}

CVector3 CMatrix::GetRow(int i)
{
    return CVector3((*this)[4 * i], (*this)[4 * i + 1], (*this)[4 * i + 2]);
}

CVector3 CMatrix::GetCol(int i)
{
    return CVector3((*this)[i], (*this)[i + 4], (*this)[i + 8]);
}

void CMatrix::operator = (CMatrix &src)
{
    for(int i = 0; i < 16; i++)
    {
        (*this)[i] = src[i];
    }
}

CMatrix CMatrix::operator * (float factor)
{
    CMatrix res = (*this);
    for(int i = 0; i < 16; i++)
    {
        res[i] = (*this)[i] * factor;
    }
    return res;
}


CMatrix CMatrix::operator * (CMatrix &src)
{
    CMatrix res;
    float _resArray[16];
    _resArray[0] = (*this)[0] * src[0] + (*this)[1] * src[4] + (*this)[2] * src[8] + (*this)[3] * src[12];
    _resArray[1] = (*this)[0] * src[1] + (*this)[1] * src[5] + (*this)[2] * src[9] + (*this)[3] * src[13];
    _resArray[2] = (*this)[0] * src[2] + (*this)[1] * src[6] + (*this)[2] * src[10] + (*this)[3] * src[14];
    _resArray[3] = (*this)[0] * src[3] + (*this)[1] * src[7] + (*this)[2] * src[11] + (*this)[3] * src[15];
    
    _resArray[4] = (*this)[4] * src[0] + (*this)[5] * src[4] + (*this)[6] * src[8] + (*this)[7] * src[12];
    _resArray[5] = (*this)[4] * src[1] + (*this)[5] * src[5] + (*this)[6] * src[9] + (*this)[7] * src[13];
    _resArray[6] = (*this)[4] * src[2] + (*this)[5] * src[6] + (*this)[6] * src[10] + (*this)[7] * src[14];
    _resArray[7] = (*this)[4] * src[3] + (*this)[5] * src[7] + (*this)[6] * src[11] + (*this)[7] * src[15];
    
    _resArray[8] = (*this)[8] * src[0] + (*this)[9] * src[4] + (*this)[10] * src[8] + (*this)[11] * src[12];
    _resArray[9] = (*this)[8] * src[1] + (*this)[9] * src[5] + (*this)[10] * src[9] + (*this)[11] * src[13];
    _resArray[10] = (*this)[8] * src[2] + (*this)[9] * src[6] + (*this)[10] * src[10] + (*this)[11] * src[14];
    _resArray[11] = (*this)[8] * src[3] + (*this)[9] * src[7] + (*this)[10] * src[11] + (*this)[11] * src[15];

    _resArray[12] = (*this)[12] * src[0] + (*this)[13] * src[4] + (*this)[14] * src[8] + (*this)[15] * src[12];
    _resArray[13] = (*this)[12] * src[1] + (*this)[13] * src[5] + (*this)[14] * src[9] + (*this)[15] * src[13];
    _resArray[14] = (*this)[12] * src[2] + (*this)[13] * src[6] + (*this)[14] * src[10] + (*this)[15] * src[14];
    _resArray[15] = (*this)[12] * src[3] + (*this)[13] * src[7] + (*this)[14] * src[11] + (*this)[15] * src[15];
    
    res.SetMatrix(_resArray);
    return res;
}



CVector3 CMatrix::operator * (CVector3 &src)
{
    float x = src.GetX();
    float y = src.GetY();
    float z = src.GetZ();
    float w = 0;
    float rx,ry,rz,rw;
    
    rx = (*this)[0] * x + (*this)[1] * y + (*this)[2] * z + (*this)[3] * w;
    ry = (*this)[4] * x + (*this)[5] * y + (*this)[6] * z + (*this)[7] * w;
    rz = (*this)[8] * x + (*this)[9] * y + (*this)[10] * z + (*this)[11] * w;
    rw = (*this)[12] * x + (*this)[13] * y + (*this)[14] * z + (*this)[15] * w;
    
    return CVector3(rx, ry, rz);
}

CVector3 CMatrix::Mulpoint(CVector3 &src)
{
    float x = src.GetX();
    float y = src.GetY();
    float z = src.GetZ();
    float w = 1;
    float rx,ry,rz,rw;
    
    rx = (*this)[0] * x + (*this)[1] * y + (*this)[2] * z + (*this)[3] * w;
    ry = (*this)[4] * x + (*this)[5] * y + (*this)[6] * z + (*this)[7] * w;
    rz = (*this)[8] * x + (*this)[9] * y + (*this)[10] * z + (*this)[11] * w;
    rw = (*this)[12] * x + (*this)[13] * y + (*this)[14] * z + (*this)[15] * w;
    
    return CVector3(rx, ry, rz);

}

void CMatrix::Identity()
{
    m00 = m11 = m22 = m33 = 1;
    m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m23 = m30 = m31 = m32 = 0;
    return;
}

//  m0  m1  m2  m3      m0  m4  m8  m12
//  m4  m5  m6  m7      m1  m5  m9  m13
//  m8  m9  m10 m11     m2  m6  m10 m14
//  m12 m13 m14 m15     m3  m7  m11 m15

CMatrix CMatrix::Transpose()
{
    float res[16];
    CMatrix des;
    
    res[0] = (*this)[0];
    res[5] = (*this)[5];
    res[10] = (*this)[10];
    res[15] = (*this)[15];
    
    res[1] = (*this)[4];
    res[2] = (*this)[8];
    res[3] = (*this)[12];
    
    res[4] = (*this)[1];
    res[6] = (*this)[9];
    res[7] = (*this)[13];
    
    res[8] = (*this)[2];
    res[9] = (*this)[6];
    res[11] = (*this)[14];
    
    res[12] = (*this)[3];
    res[13] = (*this)[7];
    res[14] = (*this)[11];
    
    des.SetMatrix(res);
    return des;
}

CMatrix CMatrix::SetTrans(CVector3 trans)
{
    CMatrix des;
    des.m00 = des.m11 = des.m22 = des.m33 = 1;
    des.m01 = des.m02 = 0;
    des.m10 = des.m12 = 0;
    des.m20 = des.m21 = 0;
    des.m30 = des.m31 = des.m32 = 0;
    des.m03 = trans.GetX();
    des.m13 = trans.GetY();
    des.m23 = trans.GetZ();
    return des;
}

CMatrix CMatrix::SetRotate(double seta,CVector3 axis)
{
    float nx = axis.GetX();
    float ny = axis.GetY();
    float nz = axis.GetZ();
    float radian = seta / 180.0 * 3.1415;
    CMatrix des;
    
    des.m00 = nx * nx * (1-cos(radian)) + cos(radian);
    des.m01 = nx * ny * (1-cos(radian)) + nz * sin(radian);
    des.m02 = nx * nz * (1-cos(radian)) - ny * sin(radian);
    des.m03 = 0;
    
    des.m10 = nx * ny * (1-cos(radian)) - nz * sin(radian);
    des.m11 = ny * ny * (1-cos(radian)) + cos(radian);
    des.m12 = ny * nz * (1-cos(radian)) + nx * sin(radian);
    des.m13 = 0;
    
    des.m20 = nx * nz * (1-cos(radian)) + ny * sin(radian);
    des.m21 = ny * nz * (1-cos(radian)) - nz * sin(radian);
    des.m22 = nz * nz * (1-cos(radian)) + cos(radian);
    
    des.m30 = m31 = m32 = 0;
    des.m33 = 1;
    
    return des;
}

CMatrix CMatrix::SetScale(CVector3 src)
{
    CMatrix des;
    des.m00 = src.GetX();
    des.m11 = src.GetY();
    des.m22 = src.GetZ();
    des.m33 = 1;
    des.m01 = des.m02 = des.m03 = 0;
    des.m10 = des.m12 = des.m13 = 0;
    des.m20 = des.m21 = des.m23 = 0;
    des.m30 = des.m31 = des.m32 = 0;
    
    return des;
}

float CMatrix::Determinant33(float a1,float a2,float a3,float b1,float b2,float b3,float c1,float c2,float c3)
{
    return a1*(b2*c3-b3*c2)-a2*(b1*c3-b3*c1)+a3*(b1*c2-b2*c1);
}

float CMatrix::Determinant44()
{
    float a00 = m00 * Determinant33(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    float a01 = m01 * Determinant33(m10, m12, m13, m20, m22, m23, m30, m32, m33);
    float a02 = m02 * Determinant33(m10, m11, m13, m20, m21, m23, m30, m31, m33);
    float a03 = m03 * Determinant33(m10, m11, m12, m20, m21, m22, m30, m31, m32);
    
    return a00 - a01 + a02 -a03;
}

float CMatrix::Inverse()
{
    if(this->Determinant44() == 0)
    {
        std::cerr << "The matrix is not invertible!"<<std::endl;
        return 0;
    }
    else
    {
        float det = Determinant44();
        float res[16];
        res[0] = Determinant33(m11, m12, m13, m21, m22, m23, m31, m32, m33) / det;
        res[1] = -Determinant33(m10, m12, m13, m20, m22, m23, m30, m32, m33) / det;
        res[2] = Determinant33(m10, m11, m13, m20, m21, m23, m30, m31, m33) / det;
        res[3] = -Determinant33(m10, m11, m12, m20, m21, m22, m30, m31, m32) / det;
        res[4] = -Determinant33(m01, m02, m03, m21, m22, m23, m31, m32, m33) / det;
        res[5] = Determinant33(m00, m02, m03, m20, m22, m23, m30, m32, m33) / det;
        res[6] = -Determinant33(m00, m01, m03, m20, m21, m23, m30, m31, m33) / det;
        res[7] = Determinant33(m00, m01, m02, m20, m21, m22, m30, m31, m32) / det;
        res[8] = Determinant33(m01, m02, m03, m11, m12, m13, m31, m32, m33) / det;
        res[9] = -Determinant33(m00, m02, m03, m10, m12, m13, m30, m32, m33) / det;
        res[10] = Determinant33(m00, m01, m03, m10, m11, m13, m30, m31, m33) / det;
        res[11] = -Determinant33(m00, m01, m02, m10, m11, m12, m30, m31, m32) / det;
        res[12] = -Determinant33(m01, m02, m03, m11, m12, m13, m21, m22, m23) / det;
        res[13] = Determinant33(m00, m02, m03, m10, m12, m13, m20, m22, m23) / det;
        res[14] = -Determinant33(m00, m01, m03, m10, m11, m13, m20, m21, m23) / det;
        res[15] = Determinant33(m00, m01, m02, m10, m11, m12, m20, m21, m22) / det;
        
        this->SetMatrix(res);
        return det;
    }
}

CMatrix CMatrix::GetInverse()
{
    CMatrix resMatrix;
    
    if(this->Determinant44() == 0)
    {
        std::cerr << "The matrix is not invertible!"<<std::endl;
        return resMatrix;
    }
    else
    {
        float det = Determinant44();
        float res[16];
        res[0] = Determinant33(m11, m12, m13, m21, m22, m23, m31, m32, m33) / det;
        res[1] = -Determinant33(m10, m12, m13, m20, m22, m23, m30, m32, m33) / det;
        res[2] = Determinant33(m10, m11, m13, m20, m21, m23, m30, m31, m33) / det;
        res[3] = -Determinant33(m10, m11, m12, m20, m21, m22, m30, m31, m32) / det;
        res[4] = -Determinant33(m01, m02, m03, m21, m22, m23, m31, m32, m33) / det;
        res[5] = Determinant33(m00, m02, m03, m20, m22, m23, m30, m32, m33) / det;
        res[6] = -Determinant33(m00, m01, m03, m20, m21, m23, m30, m31, m33) / det;
        res[7] = Determinant33(m00, m01, m02, m20, m21, m22, m30, m31, m32) / det;
        res[8] = Determinant33(m01, m02, m03, m11, m12, m13, m31, m32, m33) / det;
        res[9] = -Determinant33(m00, m02, m03, m10, m12, m13, m30, m32, m33) / det;
        res[10] = Determinant33(m00, m01, m03, m10, m11, m13, m30, m31, m33) / det;
        res[11] = -Determinant33(m00, m01, m02, m10, m11, m12, m30, m31, m32) / det;
        res[12] = -Determinant33(m01, m02, m03, m11, m12, m13, m21, m22, m23) / det;
        res[13] = Determinant33(m00, m02, m03, m10, m12, m13, m20, m22, m23) / det;
        res[14] = -Determinant33(m00, m01, m03, m10, m11, m13, m20, m21, m23) / det;
        res[15] = Determinant33(m00, m01, m02, m10, m11, m12, m20, m21, m22) / det;

        resMatrix.SetMatrix(res);
        return resMatrix.Transpose();
    }
}

void CMatrix::Output()
{
    for(int i = 0;i < 4 ;i++)
    {
        for(int j = 0; j < 4;j++)
        {
            std::cout << (*this)[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}

