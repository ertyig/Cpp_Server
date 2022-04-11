/*
 * @Author: leechain
 * @Date: 2022-04-10 19:02:14
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-10 20:16:05
 * @FilePath: /Cpp_Server/src/Acceptor.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <functional>

class EventLoop;
class Socket;
class InetAddress;
class Channel;

class Acceptor
{
private:
    EventLoop *loop;
    Socket *sock;
    InetAddress *addr;
    Channel *acceptChannel;
    
public:
    Acceptor(EventLoop *_loop);
    ~Acceptor();
    void acceptConnection();

    function<void(Socket*)> newConnectionCallback;

    void setNewConnectionCallback(function<void(Socket*)>);
};