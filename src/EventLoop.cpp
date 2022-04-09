/*
 * @Author: leechain
 * @Date: 2022-04-07 21:23:13
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-09 11:19:32
 * @FilePath: /Cpp_Server/src/EventLoop.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop() :ep(nullptr),quit(false)
{
    ep=new Epoll();
}

EventLoop::~EventLoop()
{
    delete ep;
}

void EventLoop::loop()
{
    while(!quit)
    {
        vector<Channel*> chs;
        chs=ep->poll();
        for(auto it=chs.begin();it!=chs.end();++it)
        {
//若服务器socket有可读事件，Channel类的handleEvent()实际上会调用Server类的newConnection()新建连接。
//若客户端socket有可读事件，Channel类的handleEvent()实际上会调用Server类的handlrReadEvent()响应客户端请求。
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch)
{
    ep->updateChannel(ch);
}