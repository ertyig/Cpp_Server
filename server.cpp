/*
 * @Author: leechain
 * @Date: 2022-04-02 15:41:28
 * @LastEditors: leechain
 * @LastEditTime: 2022-04-09 11:12:44
 * @FilePath: /Cpp_Server/server.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by leechain, All Rights Reserved. 
 */

#include "src/EventLoop.h"
#include "src/Server.h"


int main()
{
    //启动服务器
    EventLoop *loop = new EventLoop();
    Server *server = new Server(loop);
    loop->loop();

    return 0;
}


