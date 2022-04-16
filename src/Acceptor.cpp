/*
 * @Author: leechain
 * @Date: 2022-04-10 19:02:23
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-16 08:41:15
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

Acceptor::Acceptor(EventLoop *_loop) : loop(_loop),sock(nullptr),acceptChannel(nullptr)
{
    sock=new Socket();
    InetAddress *addr=new InetAddress("127.0.0.1",8888);
    sock->bind(addr);
    sock->listen();
    sock->setnonblocking();
    //新建一个Channel时，必须说明该Channel与哪个 EventLoop 和 fd 绑定
    acceptChannel=new Channel(loop,sock->getFd());
    function<void()> cb=bind(&Acceptor::acceptConnection,this);
    acceptChannel->setCallback(cb);  //(acceptChannel里 callback=cb)
    acceptChannel->enableReading();
    delete addr;
}

Acceptor::~Acceptor()
{
    delete sock;
    delete acceptChannel;
}

void Acceptor::acceptConnection()
{
    InetAddress *clnt_addr=new InetAddress();
    Socket *clnt_sock=new Socket(sock->accept(clnt_addr));
    printf("new client fd %d IP: %s Port: %d\n",clnt_sock->getFd(),inet_ntoa(clnt_addr->getAddr().sin_addr),ntohs(clnt_addr->getAddr().sin_port));
    clnt_sock->setnonblocking();
    //回调函数传入参数
    newConnectionCallback(clnt_sock);
    
    delete clnt_addr;
}

void Acceptor::setNewConnectionCallback(function<void(Socket*)> _cb)
{
    newConnectionCallback=_cb;
}