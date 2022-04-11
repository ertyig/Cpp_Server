/*
 * @Author: leechain
 * @Date: 2022-04-07 21:22:50
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-10 20:17:24
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
#include <functional>
#include <cstring>
#include <unistd.h>

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop) :loop(_loop), acceptor(nullptr)
{
    acceptor=new Acceptor(loop);
    function<void(Socket*)> cb=bind(&Server::newConnection,this,placeholders::_1);
    acceptor->setNewConnectionCallback(cb);   
}   

Server::~Server()
{
    delete acceptor;
}

void Server::handleReadEvent(int sockfd)
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

void Server::newConnection(Socket *serv_sock)
{
    InetAddress *clnt_addr=new InetAddress();
    Socket *clnt_sock=new Socket(serv_sock->accept(clnt_addr));
    printf("new client fd %d IP: %s Port: %d\n",clnt_sock->getFd(),inet_ntoa(clnt_addr->addr.sin_addr),ntohs(clnt_addr->addr.sin_port));
    clnt_sock->setnonblocking();
    Channel *clntChannel=new Channel(loop,clnt_sock->getFd());
    function<void()> cb=bind(&Server::handleReadEvent,this,clnt_sock->getFd());
    clntChannel->setCallback(cb);
    clntChannel->enableReading();
}