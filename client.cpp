/*
 * @Author: leechain
 * @Date: 2022-04-02 15:41:08
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-15 16:36:27
 * @FilePath: /Cpp_Server/client.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */
#include <iostream>
#include <unistd.h>
#include "src/Socket.h"
#include "src/Buffer.h"
#include "src/InetAddress.h"
#include <cstring>
#include "src/util.h"


int main()
{
    Socket *sock=new Socket();
    InetAddress *addr=new InetAddress("127.0.0.1",8888);
    
    sock->connect(addr);
    int sockfd=sock->getFd();
    Buffer *sendBuffer=new Buffer();
    Buffer *readBuffer=new Buffer();


    while(true)
    {
        sendBuffer->getline();
        ssize_t write_bytes=write(sockfd,sendBuffer->c_str(),sendBuffer->size());//向服务器写数据
        if(write_bytes==-1)//write返回-1，表示写数据发生错误
        {
            printf("socket disconnected,can't write!");
            break;
        }

        int already_read=0;
        char buf[1024];//buf大小无所谓
        while(true)
        {
            bzero(&buf,sizeof(buf));
            ssize_t read_bytes=read(sockfd,buf,sizeof(buf));//从服务器读取数据
            if(read_bytes>0)
            {
                readBuffer->append(buf,read_bytes);
                already_read+=read_bytes;
            }
            else if(read_bytes==0)//read返回0，表示EOF，通常是服务器断开连接，等会儿进行测试
            {
                printf("server socket disconnected!\n");
                exit(EXIT_SUCCESS);
            }

            if(already_read>=sendBuffer->size())//read 返回-1，表示发生错误，进行错误处理
            {
                printf("Message from server: %s\n",readBuffer->c_str());
                break;
            }
        }
        readBuffer->clear();
    }

    delete addr;
    delete sock;
    return 0;
}
