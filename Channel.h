/*
 * @Author: leechain
 * @Date: 2022-04-06 09:48:06
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-06 09:51:20
 * @FilePath: /Cpp_Server/Channel.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <sys/epoll.h>

class Epoll;

class Channel
{
private:
    Epoll *ep;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;

public:
    Channel(Epoll *_ep,int _fd);
    ~Channel();

    void enableReading();

    int getFd();
    u_int32_t getEvents();
    u_int32_t getRevents();
    bool getInpoll();
    void setInpoll();

    void setRevents(uint32_t);
};
