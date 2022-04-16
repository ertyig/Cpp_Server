/*
 * @Author: leechain
 * @Date: 2022-04-14 11:06:10
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-16 08:37:33
 * @FilePath: /Cpp_Server/src/Buffer.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "Buffer.h"
#include <cstring>
#include <iostream>


Buffer::Buffer()
{

}

Buffer::~Buffer()
{
    
}

void Buffer::append(const char* _str,int _size)
{
    for(int i=0;i<_size;++i)
    {
        if(_str[i]=='\0') break;
        buf.push_back(_str[i]);
    }
}

ssize_t Buffer::size()
{
    return buf.size();
}

const char* Buffer::c_str()
{
    return buf.c_str();
}

void Buffer::clear()
{
    buf.clear();
}

void Buffer::getline()
{
    buf.clear();
    std::getline(cin,buf);
}