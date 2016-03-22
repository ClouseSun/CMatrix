//
//  FileParser.cpp
//  CMatrix
//
//  Created by 孙云霄 on 16/3/20.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#include "FileParser.hpp"

void FileParser::Run(int argc, char **argv, std::string filename)
{
    ReadFile(filename);
    ParserMatrix(buffer);
    _displaymanager.Show(argc, argv);
}

std::vector<std::string> FileParser::Split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
    int size = (int)str.size();
    
    for(int i = 0; i < size; i++)
    {
        pos = str.find(pattern,i);
        if(pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = (int)(pos + pattern.size() - 1);
        }
    }
    return result;
}

bool FileParser::ParserMatrix(std::string *buf)
{
    int row = 0;
    int mark = -1;
    
    while(row < sizeof(buffer) / sizeof(std::string))
    {
        while (strcmp(buf[row].c_str(),"\n") == 0)
        {
            row++;
        }
        
        if(strcmp(buf[row].c_str(), "matrix multiply matrix\n") == 0)
        {
            mark = 1;
            _displaymanager.vecO.push_back(1);
        }
        else if(strcmp(buf[row].c_str(), "matrix multiply number\n") == 0)
        {
            mark = 2;
            _displaymanager.vecO.push_back(2);
        }
        else if(strcmp(buf[row].c_str(), "matrix multiply vector\n") == 0)
        {
            mark = 3;
            _displaymanager.vecO.push_back(3);
        }
        else if(strcmp(buf[row].c_str(), "matrix multiply point\n") == 0)
        {
            mark = 4;
            _displaymanager.vecO.push_back(4);
        }
        else if(strcmp(buf[row].c_str(), "identity\n") == 0)
        {
            mark = 5;
            _displaymanager.vecO.push_back(5);
        }
        else if(strcmp(buf[row].c_str(), "transcope\n") == 0)
        {
            mark = 6;
            _displaymanager.vecO.push_back(6);
        }
        else if(strcmp(buf[row].c_str(), "rotate\n") == 0)
        {
            mark = 7;
            _displaymanager.vecO.push_back(7);
        }
        else if(strcmp(buf[row].c_str(), "scale\n") == 0)
        {
            mark = 8;
            _displaymanager.vecO.push_back(8);
        }
        else if(strcmp(buf[row].c_str(), "translation\n") == 0)
        {
            mark = 9;
            _displaymanager.vecO.push_back(9);
        }
        else if(strcmp(buf[row].c_str(), "inverse\n") == 0)
        {
            mark = 10;
            _displaymanager.vecO.push_back(10);
        }
        else
            return false;
        
        row++;
        
        float src[16];
        while (strcmp(buf[row].c_str(),"\n") == 0)
        {
            row++;
        }
        
        for (int i = 0; i < 4; i++)
        {
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            src[4 * i] = atof(vector[0].c_str());
            src[4 * i + 1] = atof(vector[1].c_str());
            src[4 * i + 2] = atof(vector[2].c_str());
            src[4 * i + 3] = atof(vector[3].c_str());
        }
        CMatrix srcmat;
        srcmat.SetMatrix(src);
        _displaymanager.PushCMatrix(srcmat);
        
        if(mark == 1)
        {
            float des[16];
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            for (int i = 0; i < 4; i++)
            {
                std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
                des[4 * i] = atof(vector[0].c_str());
                des[4 * i + 1] = atof(vector[1].c_str());
                des[4 * i + 2] = atof(vector[2].c_str());
                des[4 * i + 3] = atof(vector[3].c_str());
            }
            CMatrix desmat;
            desmat.SetMatrix(des);
            _displaymanager.PushCMatrix(desmat);
            
            _displaymanager.PushCMatrix(srcmat * desmat);
            (srcmat * desmat).Output();
        }
        
        else if(mark == 2)
        {
            float des;
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            des = atof(buf[row].c_str());
            _displaymanager.PushCMatrix(srcmat * des);
            (srcmat * des).Output();
        }
        
        else if(mark == 3)
        {
            float dx, dy, dz;
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            dx = atof(vector[0].c_str());
            dy = atof(vector[1].c_str());
            dz = atof(vector[2].c_str());
            CVector3 des(dx, dy, dz);
            _displaymanager.PushCVector3(des);
            _displaymanager.PushCVector3(srcmat * des);
            (srcmat * des).Output();
        }
        
        else if(mark == 4)
        {
            float dx, dy, dz;
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            dx = atof(vector[0].c_str());
            dy = atof(vector[1].c_str());
            dz = atof(vector[2].c_str());
            CVector3 des(dx, dy, dz);
            _displaymanager.PushCVector3(des);
            _displaymanager.PushCVector3(srcmat.Mulpoint(des));
            srcmat.Mulpoint(des).Output();
        }
        
        else if(mark == 5)
        {
            CMatrix des;
            _displaymanager.PushCMatrix(des);
            des.Output();
        }
        
        else if(mark == 6)
        {
            CMatrix des = srcmat.Transpose();
            _displaymanager.PushCMatrix(des);
            des.Output();
        }
        
        else if(mark == 7)
        {
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            float deseta = atof(buf[row++].c_str());
            
            float dx, dy, dz;
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            dx = atof(vector[0].c_str());
            dy = atof(vector[1].c_str());
            dz = atof(vector[2].c_str());
            CVector3 des(dx, dy, dz);
            
            _displaymanager.PushCVector3(des);
            _displaymanager.PushCMatrix(srcmat.SetRotate(deseta, des));
            (srcmat.SetRotate(deseta, des)).Output();
        }
        else if (mark == 8)
        {
            float dx, dy, dz;
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            dx = atof(vector[0].c_str());
            dy = atof(vector[1].c_str());
            dz = atof(vector[2].c_str());
            CVector3 des(dx, dy, dz);
            _displaymanager.PushCMatrix(srcmat.SetScale(des));
            (srcmat.SetScale(des)).Output();
        }
        else if(mark == 9)
        {
            float dx, dy, dz;
            while (strcmp(buf[row].c_str(),"\n") == 0)
            {
                row++;
            }
            std::vector<std::string> vector = FileParser::Split(buf[row++] , " ");
            dx = atof(vector[0].c_str());
            dy = atof(vector[1].c_str());
            dz = atof(vector[2].c_str());
            CVector3 des(dx, dy, dz);
            _displaymanager.PushCMatrix(srcmat.SetTrans(des));
            (srcmat.SetTrans(des)).Output();
        }
        else if(mark == 10)
        {
            CMatrix des;
            _displaymanager.PushCMatrix(srcmat.GetInverse());
            (srcmat.GetInverse()).Output();
        }
    }
    return true;
}

std::string* FileParser::ReadFile(std::string filename)
{
    FILE* fp;
    int row = 0;
    char bufchar[MAX_LINE];
    if((fp = fopen(filename.c_str(),"r")) == NULL)
    {
        perror("fail to read");
        exit (1) ;
    }
    
    while(fgets(bufchar,MAX_LINE,fp) != NULL)
    {
        buffer[row++] = bufchar;
    }
    
    return buffer;
}
