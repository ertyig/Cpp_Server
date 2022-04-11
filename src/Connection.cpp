/*
 * @Author: leechain
 * @Date: 2022-04-11 10:09:19
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-11 15:19:41
 * @FilePath: /Cpp_Server/src/Connection.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "Socket.h"
#include "Channel.h"
#include "Connection.h"
#include <unistd.h>
#include <cstring>

#define READ_BUFFER 1024


Connection::Connection(EventLoop *_loop,Socket *_sock):loop(_loop),sock(_sock),channel(nullptr)
{
    channel=new Channel(loop,sock->getFd()); //该连接的Channel
    function<void()> cb=bind(&Connection::echo,this,sock->getFd());
    channel->setCallback(cb); //绑定回调函数
    channel->enableReading(); //打开读事件监听
}

Connection::~Connection()
{
    delete channel;
    delete sock;
}

void Connection::echo(int sockfd)
{
    char buf[READ_BUFFER];
    while(true)//由于使用非阻塞IO，读取客户端buffer,一次读取buf大小数据，直到全部读取完毕
    {
        bzero(&buf,sizeof(buf)); //清空缓冲区
        ssize_t read_bytes=read(sockfd,buf,sizeof(buf));//从客户端socket读到缓冲区，返回已读数据大小

        if(read_bytes>0)
        {
            printf("Message from client fd %d: %s\n",sockfd,buf);
            write(sockfd,buf,sizeof(buf));//将相同的数据写回客户端
        }
        else if(read_bytes==-1 && errno==EINTR) //客户端正常中断、继续读取
        {
            printf("Continue reading");
            continue;
        }
        else if(read_bytes==-1 && ((errno==EAGAIN || errno==EWOULDBLOCK)))//非阻塞IO，这个条件表示数据全部读取完毕
        {
            printf("Finish reading once,errno:%d\n",errno);
            break;
        }
        else if(read_bytes==0)//read 返回0，表示客户端断开连接
        {
            printf("client fd %d disconnected\n",sockfd);
            close(sockfd); //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(function<void(Socket*)> _cb)
{
    deleteConnectionCallback=_cb;
}