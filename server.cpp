//
// Created by leechain on 2022/4/2.
//
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "util.h"

#define MAX_EVENTS 1024
#define READ_BUFFER 1024


void setnonblocking(int fd)
{
    fcntl(fd,F_SETFL,fcntl(fd,F_GETFL) | O_NONBLOCK);
}



int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    errif(sockfd==-1,"socket create error!");

    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(8888);

    errif(bind(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1,"socket bind error!");

    errif(listen(sockfd,SOMAXCONN)==-1,"socket listen error!");

    int epfd=epoll_create1(0);
    errif(epfd==-1,"epoll create error");

    struct epoll_event events[MAX_EVENTS];
    struct epoll_event ev;
    bzero(&events,sizeof(events));

    bzero(&ev,sizeof(ev));
    ev.data.fd=sockfd; //该IO口为服务器socket fd
    ev.events=EPOLLIN | EPOLLET;
    setnonblocking(sockfd);
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev); //将服务器socket fd添加到epoll

    
    while (true) // 不断监听epoll上的事件并处理
    {
        int nfds=epoll_wait(epfd,events,MAX_EVENTS,-1); //有nfds个fd发生事件
        errif(nfds==-1,"epoll wait error"); 

        for(int i=0;i<nfds;++i) //处理这nfds个事件
        {
            if(events[i].data.fd==sockfd) //发生事件的fd是服务器socket fd，表示有新客户端连接
            {
                struct sockaddr_in clnt_addr;
                socklen_t clnt_addr_len=sizeof(clnt_addr);
                bzero(&clnt_addr,sizeof(clnt_addr));

                int clnt_sockfd=accept(sockfd,(sockaddr*)&clnt_addr,&clnt_addr_len);
                errif(clnt_sockfd==-1,"socket create error!");
                printf("New client fd %d! IP: %s Port: %d\n",clnt_sockfd,inet_ntoa(clnt_addr.sin_addr),ntohs(clnt_addr.sin_port));

                bzero(&ev,sizeof(ev));
                ev.data.fd=clnt_sockfd;
                ev.events=EPOLLIN | EPOLLET; //对于客户端连接，使用ET模式，可以让epoll更加高效，支持更多并发
                setnonblocking(clnt_sockfd); //ET需要搭配非阻塞式socket使用
                epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sockfd,&ev); //将该客户端的socket fd添加到epoll
            }
            else if(events[i].events & EPOLLIN) //发生事件的是客户端，并且是可读事件（EPOLLIN）
            {
                char buf[READ_BUFFER]; //定义缓冲区
                while(true)  //由于使用非阻塞IO，需要不断读取，直到全部读取完毕
                {
                    bzero(&buf,sizeof(buf)); //清空缓冲区
                    ssize_t read_bytes=read(events->data.fd,buf,sizeof(buf));//从客户端socket读到缓冲区，返回已读数据大小

                    if(read_bytes>0)
                    {
                        printf("Message from client fd %d: %s\n",events[i].data.fd,buf);
                        write(events[i].data.fd,buf,sizeof(buf));//将相同的数据写回客户端
                    }
                    else if(read_bytes==-1&&errno==EINTR) //客户端正常中断、继续读取
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
                        printf("client fd %d disconnected\n",events[i].data.fd);
                        close(events[i].data.fd); //关闭socket会自动将文件描述符从epoll树上移除
                        break;
                    }
                    
                }
            }
            else{
                printf("Something else happend\n");
            }
        }   
    }

    close(sockfd);

    return 0;
}