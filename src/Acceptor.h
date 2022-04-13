/*
 * @Author: leechain
 * @Date: 2022-04-10 19:02:14
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-13 09:55:51
 * @FilePath: /Cpp_Server/src/Acceptor.h
 * @Description: 新建TCP连接
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
    Acceptor(EventLoop *_loop); //该构造函数 新建服务器的socket
    ~Acceptor();
    
    void acceptConnection();  //允许客户端的TCP连接
    void setNewConnectionCallback(function<void(Socket*)>);
};