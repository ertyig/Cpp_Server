/*
 * @Author: leechain
 * @Date: 2022-04-06 09:48:06
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-13 09:56:31
 * @FilePath: /Cpp_Server/src/Channel.h
 * @Description: Channel管理socket fd
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <sys/epoll.h>
#include <functional>
using namespace std;


class EventLoop;

class Channel
{
private:
    EventLoop *loop;
    int fd;
    uint32_t events; //表示希望监听这个文件描述符的哪些事件
    uint32_t revents; //表示在epoll返回该Channel时，文件描述符 正在发生 的事件
    bool inEpoll;
    function<void()> callback;

public:
    Channel(EventLoop *_loop,int _fd);
    ~Channel();

    void handleEvent();
    void enableReading();

    int getFd();
    u_int32_t getEvents();
    u_int32_t getRevents();
    bool getInpoll();
    void setInpoll();

    void setRevents(uint32_t);
    void setCallback(function<void()>);
};
