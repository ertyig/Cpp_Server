/*
 * @Author: leechain
 * @Date: 2022-04-04 09:52:05
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-06 14:08:25
 * @FilePath: /Cpp_Server/Epoll.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#include "Epoll.h"
#include "util.h"
#include <unistd.h>
#include <cstring>
#include "Channel.h"

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr)
{
    epfd=epoll_create1(0);
    errif(epfd==-1,"epoll create error");
    events=new epoll_event[MAX_EVENTS];
    bzero(events,sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll()
{
    if(epfd!=-1)
    {
        close(epfd);
        epfd=-1;
    }
    delete [] events;
}

void Epoll::addFd(int fd,uint32_t op)
{
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.fd=fd;
    ev.events=op;
    errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll add event error");
}

vector<Channel*> Epoll::poll(int timeout)
{
    vector<Channel*> activeChannels; //activeChannels是所有 有事件发生的Channel
    int nfds=epoll_wait(epfd,events,MAX_EVENTS,timeout);
    errif(nfds==-1,"epoll wait error");
    for(int i=0;i<nfds;++i)
    {
        Channel *ch=(Channel*)events[i].data.ptr;
        ch->setRevents(events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel *channel)
{
    int fd=channel->getFd(); //拿到Channel的文件描述符
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.ptr=channel;
    ev.events=channel->getEvents(); //拿到Channel希望监听的事件
    if(!channel->getInpoll()) //添加Channel中的文件描述符到epoll
    {
        errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll add error");
    }
    else //若文件描述符已存在，则修改
    {
        errif(epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev)==-1,"epoll modify error");
    }
}

// vector<epoll_event> Epoll::poll(int timeout)
// {
//     vector<epoll_event> activeEvents;
//     int nfds=epoll_wait(epfd,events,MAX_EVENTS,timeout);
//     errif(nfds==-1,"epoll wait error");
//     for(int i=0;i<nfds;++i)
//     {
//         activeEvents.push_back(events[i]);
//     }
//     return activeEvents;
// }