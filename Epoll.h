#pragma once
#include <sys/epoll.h>
#include <vector>

using namespace std;

class Epoll {
private:
    int epfd;
    struct epoll_event *events;

public:
    Epoll();
    ~Epoll();

    void addFd(int fd, uint32_t op);
    vector<epoll_event> poll(int timeout = -1);
};