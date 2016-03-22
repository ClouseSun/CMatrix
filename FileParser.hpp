//
//  FileParser.hpp
//  CMatrix
//
//  Created by 孙云霄 on 16/3/20.
//  Copyright © 2016年 ClouseSun. All rights reserved.
//

#ifndef FileParser_hpp
#define FileParser_hpp

#include "DisplayManager.hpp"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE 100

class FileParser
{
    DisplayManager _displaymanager;
    std::string buffer[MAX_LINE];
    
public:
    void Run(int argc, char* argv[], std::string filename);
    bool ParserMatrix(std::string *buf);
    std::string* ReadFile(std::string filename);
    static std::vector<std::string> Split(std::string str, std::string pattern);
    
};

#endif /* FileParser_hpp */
