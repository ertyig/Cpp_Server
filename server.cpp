/*
 * @Author: leechain
 * @Date: 2022-04-02 15:41:28
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-05 16:23:55
 * @FilePath: /Cpp_Server/server.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "util.h"
#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"

using namespace std;
#define MAX_EVENTS 1024
#define READ_BUFFER 1024

void handleReadEvent(int);

int main()
{
    Socket *serv_sock=new Socket();
    InetAddress *serv_addr=new InetAddress("127.0.0.1",8888);
    
    serv_sock->bind(serv_addr);
    serv_sock->listen();
    Epoll *ep=new Epoll();
    serv_sock->setnonblocking();
    ep->addFd(serv_sock->getFd(),EPOLLIN | EPOLLET);

    
    while (true) // 不断监听epoll上的事件并处理
    {
        vector<epoll_event> events=ep->poll();
        int nfds=events.size();

        for(int i=0;i<nfds;++i) //处理这nfds个事件
        {
            if(events[i].data.fd==serv_sock->getFd()) //发生事件的fd是服务器socket fd，表示有新客户端连接
            {
                InetAddress *clnt_addr=new InetAddress(); //会发生内存泄漏，没有delete
                Socket *clnt_sock=new Socket(serv_sock->accept(clnt_addr));//会发生内存泄漏，没有delete

                printf("new client fd %d IP: %s Port: %d\n",clnt_sock->getFd(),inet_ntoa(clnt_addr->addr.sin_addr),ntohs(clnt_addr->addr.sin_port));
                clnt_sock->setnonblocking();
                ep->addFd(clnt_sock->getFd(), EPOLLIN | EPOLLET);
            }
            else if(events[i].events & EPOLLIN) //发生事件的是客户端，并且是可读事件（EPOLLIN）
            {
                handleReadEvent(events[i].data.fd);
            }
            else
            {
                printf("Something else happend\n");
            }
        }   
    }

    delete serv_sock;
    delete serv_addr;

    return 0;
}


void handleReadEvent(int sockfd)
{
    char buf[READ_BUFFER];
    while(true)
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