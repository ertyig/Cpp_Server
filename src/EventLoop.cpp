/*
 * @Author: leechain
 * @Date: 2022-04-07 21:23:13
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-13 10:10:20
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
            //若服务器socket有可读事件或者客户端socket有可读事件，
            //handleEvent会通过 回调函数 处理相应事件
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch)
{
    ep->updateChannel(ch);
}