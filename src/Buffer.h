/*
 * @Author: leechain
 * @Date: 2022-04-14 11:06:02
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-14 11:27:46
 * @FilePath: /Cpp_Server/src/Buffer.h
 * @Description: 缓冲区
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <string>
using namespace std;

class Buffer
{
private:
    string buf;
public:
    Buffer();
    ~Buffer();
    void append(const char* _str,int _size);
    ssize_t size();
    const char* c_str();
    void clear();
    void getline();
};