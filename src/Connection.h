/*
 * @Author: leechain
 * @Date: 2022-04-11 10:09:05
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-14 11:26:37
 * @FilePath: /Cpp_Server/src/Connection.h
 * @Description: 管理TCP连接
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection
{
private:
    EventLoop *loop;
    Socket *sock;
    Channel *channel;
    function<void(Socket*)> deleteConnectionCallback;
    string *inBuffer;
    Buffer *readBuffer;
public:
    Connection(EventLoop *_loop,Socket *_sock);
    ~Connection();

    void echo(int sockfd);//处理客户端读写事件
    void setDeleteConnectionCallback(function<void(Socket*)> _cb);
};