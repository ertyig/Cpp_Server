/*
 * @Author: leechain
 * @Date: 2022-04-11 10:09:05
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-11 11:52:40
 * @FilePath: /Cpp_Server/src/Connection.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;

class Connection
{
private:
    EventLoop *loop;
    Socket *sock;
    Channel *channel;
    function<void(Socket*)> deleteConnectionCallback;
public:
    Connection(EventLoop *_loop,Socket *_sock);
    ~Connection();

    void echo(int sockfd);
    void setDeleteConnectionCallback(function<void(Socket*)> _cb);
};