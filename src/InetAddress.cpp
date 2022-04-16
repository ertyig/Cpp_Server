/*
 * @Author: leechain
 * @Date: 2022-04-04 09:51:54
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-15 11:22:34
 * @FilePath: /Cpp_Server/src/InetAddress.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#include "InetAddress.h"
#include <cstring>

InetAddress::InetAddress() : addr_len(sizeof(addr))
{
    bzero(&addr,sizeof(addr));
}

InetAddress::InetAddress(const char* ip,uint16_t port) : addr_len(sizeof(addr))
{
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);
    addr_len=sizeof(addr);
}

InetAddress::~InetAddress()
{
    
}

void InetAddress::setInetAddr(sockaddr_in _addr,socklen_t _addr_len)
{
    addr=_addr;
    addr_len=_addr_len;
}

sockaddr_in InetAddress::getAddr()
{
    return addr;
}

socklen_t InetAddress::getAddr_len()
{
    return addr_len;
}
