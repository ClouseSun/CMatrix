//
//  CVector3.cpp
//  Vector
//
//  Created by ClouseSun on 16/3/7.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#include "CVector3.hpp"

extern const float eps;

CVector3::CVector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

CVector3::CVector3(float sx,float sy,float sz)
{
    this->x = sx;
    this->y = sy;
    this->z = sz;
}

CVector3::CVector3(const CVector3 &src)
{
    this->x = src.x;
    this->y = src.y;
    this->z = src.z;
}

float CVector3::GetX()
{
    return this->x;
}

float CVector3::GetY()
{
    return this->y;
}

float CVector3::GetZ()
{
    return this->z;
}

void CVector3::Set(float sx, float sy, float sz)
{
    this->x = sx;
    this->y = sy;
    this->z = sz;
}

float CVector3::GetLength()
{
    return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void CVector3::operator = (const CVector3 &src)
{
    this->x = src.x;
    this->y = src.y;
    this->z = src.z;
}

CVector3 CVector3::operator + (const CVector3 &src)
{
    return CVector3(this->x + src.x, this->y + src.y, this->z + src.z);
}

CVector3 CVector3::operator - (const CVector3 &src)
{
    return CVector3(this->x - src.x, this->y - src.y, this->z - src.z);
}

CVector3 CVector3::operator * (float scale)
{
    return CVector3(this->x * scale, this->y * scale, this->z * scale);
}

CVector3 CVector3::operator / (float scale)
{
    if(fabs(scale) < eps)
    {
        std::cerr << "Divided by zero!"<<std::endl;
    }
    return CVector3(this->x / scale, this->y / scale, this->z / scale);
}

float CVector3::DotProduct(CVector3 src)
{
    return this->x * src.x + this->y * src.y + this->z * src.z;
}

CVector3 CVector3::CrossProduct(CVector3 src)
{
    return CVector3(this->y * src.z - this->z * src.y, this->z * src.x - this->x * src.z, this->x * src.y - this->y * src.x);
}

void CVector3::Inverse()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

void CVector3::Normalize()
{
    this->x /= x/this->GetLength();
    this->y /= y/this->GetLength();
    this->z /= z/this->GetLength();
}

void CVector3::Output()
{
    std::cout << '('<<this->x<<','<<this->y<<','<<this->z<<')' << std::endl;
}

CVector3 CVector3::Project(CVector3 des)
{
    return des / des.GetLength() * this->DotProduct(des) / des.GetLength();
}

