/*
 * @Author: leechain
 * @Date: 2022-04-07 21:22:50
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-13 09:30:34
 * @FilePath: /Cpp_Server/src/Server.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include <functional>
#include <cstring>
#include <unistd.h>

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) :loop(_loop), acceptor(nullptr)
{
    acceptor=new Acceptor(loop);
    function<void(Socket*)> cb=bind(&Server::newConnection,this,placeholders::_1);
    acceptor->setNewConnectionCallback(cb);  //绑定 新建连接的回调函数 
}   

Server::~Server()
{
    delete acceptor;
}


void Server::newConnection(Socket *sock)
{
    Connection *conn=new Connection(loop,sock);
    function<void(Socket*)> cb=bind(&Server::deleteConnection,this,placeholders::_1);
    conn->setDeleteConnectionCallback(cb); // 绑定 删除连接的回调函数
    connections[sock->getFd()]=conn; //存储新连接 (socket fd : *conn)
}


void Server::deleteConnection(Socket *sock)
{
    Connection *conn=connections[sock->getFd()];
    
    connections.erase(sock->getFd());
    delete conn;
}