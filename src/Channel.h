/*
 * @Author: leechain
 * @Date: 2022-04-06 09:48:06
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-07 21:30:01
 * @FilePath: /Cpp_Server/src/Channel.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <sys/epoll.h>
#include <functional>
using namespace std;

//class Epoll;
class EventLoop;

class Channel
{
private:
    //Epoll *ep;
    EventLoop *loop;
    int fd;
    uint32_t events; //表示希望监听这个文件描述符的哪些事件
    uint32_t revents; //表示在epoll返回该Channel时文件描述符 正在发生 的事件
    bool inEpoll;
    function<void()> callback;

public:
    //Channel(Epoll *_ep,int _fd);
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
