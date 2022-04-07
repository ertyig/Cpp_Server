/*
 * @Author: leechain
 * @Date: 2022-04-04 09:52:10
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-06 10:10:13
 * @FilePath: /Cpp_Server/Epoll.h
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#pragma once
#include <sys/epoll.h>
#include <vector>

using namespace std;

class Channel;

class Epoll {
private:
    int epfd;
    struct epoll_event *events;

public:
    Epoll();
    ~Epoll();

    void addFd(int fd, uint32_t op);
    //vector<epoll_event> poll(int timeout = -1);
    vector<Channel*> poll(int timeout=-1);
    void updateChannel(Channel*);
};