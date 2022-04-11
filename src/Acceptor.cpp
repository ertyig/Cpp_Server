/*
 * @Author: leechain
 * @Date: 2022-04-10 19:02:23
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-11 09:56:40
 * @FilePath: /Cpp_Server/src/Acceptor.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"
#include "Acceptor.h" //这个头文件要放在最后面，奇特

Acceptor::Acceptor(EventLoop *_loop) : loop(_loop)
{
    sock=new Socket();
    addr=new InetAddress("127.0.0.1",8888);
    sock->bind(addr);
    sock->listen();
    sock->setnonblocking();
    //新建一个Channel时，必须说明该Channel与哪个 EventLoop 和 fd 绑定
    acceptChannel=new Channel(loop,sock->getFd());
    function<void()> cb=bind(&Acceptor::acceptConnection,this);
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor()
{
    delete sock;
    delete addr;
    delete acceptChannel;
}

void Acceptor::acceptConnection()
{
    newConnectionCallback(sock);
}

void Acceptor::setNewConnectionCallback(function<void(Socket*)> _cb)
{
    newConnectionCallback=_cb;
}