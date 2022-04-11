/*
 * @Author: leechain
 * @Date: 2022-04-07 21:22:39
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-10 19:43:53
 * @FilePath: /Cpp_Server/src/Server.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once

class EventLoop;
class Socket;
class Acceptor;

class Server
{
private:
    EventLoop *loop;
    Acceptor *acceptor;
public:
    Server(EventLoop*);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *serv_sock);
};