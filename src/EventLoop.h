/*
 * @Author: leechain
 * @Date: 2022-04-07 21:23:04
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-08 11:16:53
 * @FilePath: /Cpp_Server/src/EventLoop.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
class Epoll;
class Channel;

class EventLoop
{
private:
    Epoll *ep;
    bool quit;
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel*);
};