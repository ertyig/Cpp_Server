/*
 * @Author: leechain
 * @Date: 2022-04-07 21:23:13
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-07 21:55:36
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
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch)
{
    ep->updateChannel(ch);
}