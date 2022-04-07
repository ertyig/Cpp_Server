/*
 * @Author: leechain
 * @Date: 2022-04-06 09:48:20
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-07 21:34:46
 * @FilePath: /Cpp_Server/src/Channel.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "Channel.h"
#include "EventLoop.h"
//#include "Epoll.h"

Channel::Channel(EventLoop *_loop,int _fd):ep(_ep),fd(_fd),events(0),revents(0),inEpoll(false)
{
    
}

Channel::~Channel()
{

}

void Channel::handleEvent()
{
    callback();
}

void Channel::enableReading()
{
    events=EPOLLIN | EPOLLET;
    loop->updateChannel(this);
}

int Channel::getFd()
{
    return fd;
}

uint32_t Channel::getEvents()
{
    return events;
}

uint32_t Channel::getRevents()
{
    return revents;
}

bool Channel::getInpoll()
{
    return inEpoll;
}

void Channel::setInpoll()
{
    inEpoll=true;
}

void Channel::setRevents(uint32_t _ev)
{
    revents=_ev;
}

void Channel::setCallback(function<void()> _cb)
{
    callback=_cb;
}