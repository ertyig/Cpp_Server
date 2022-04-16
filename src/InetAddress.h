/*
 * @Author: leechain
 * @Date: 2022-04-04 09:51:44
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-15 11:20:38
 * @FilePath: /Cpp_Server/src/InetAddress.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#pragma once
#include <arpa/inet.h>

class InetAddress
{
private:
    struct sockaddr_in addr;
    socklen_t addr_len;

public:
    InetAddress();
    InetAddress(const char* ip,uint16_t port);
    ~InetAddress();

    void setInetAddr(sockaddr_in _addr,socklen_t _addr_len);
    sockaddr_in getAddr();
    socklen_t getAddr_len();
};