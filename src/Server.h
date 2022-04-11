/*
 * @Author: leechain
 * @Date: 2022-04-07 21:22:39
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-11 15:21:13
 * @FilePath: /Cpp_Server/src/Server.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <map>
using namespace std;

class EventLoop;
class Socket;
class Acceptor;
class Connection;

class Server
{
private:
    EventLoop *loop; //事件循环
    Acceptor *acceptor; //用于接受TCP连接
    map<int,Connection*> connections; //所有TCP连接
public:
    Server(EventLoop*);
    ~Server();

    void newConnection(Socket *sock); //新建TCP连接
    void deleteConnection(Socket *sock);
};