/*
 * @Author: leechain
 * @Date: 2022-04-10 19:02:14
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-11 11:46:45
 * @FilePath: /Cpp_Server/src/Acceptor.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;

class Acceptor
{
private:
    EventLoop *loop;
    Socket *sock;
    Channel *acceptChannel;
    function<void(Socket*)> newConnectionCallback;
public:
    Acceptor(EventLoop *_loop);
    ~Acceptor();
    
    void acceptConnection();
    void setNewConnectionCallback(function<void(Socket*)>);
};