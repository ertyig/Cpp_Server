/*
 * @Author: leechain
 * @Date: 2022-04-04 09:51:22
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-15 11:10:40
 * @FilePath: /Cpp_Server/src/Socket.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#pragma once

class InetAddress;

class Socket
{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void bind(InetAddress*);
    void listen();
    void setnonblocking();
    int accept(InetAddress*);
    void connect(InetAddress*);
    int getFd();
};