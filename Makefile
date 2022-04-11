server:
	g++ src/util.cpp client.cpp -o client && \
	g++ src/util.cpp server.cpp src/InetAddress.cpp src/Epoll.cpp src/Socket.cpp src/Channel.cpp src/Server.cpp src/EventLoop.cpp src/Acceptor.cpp -o server
clean:
	rm server && rm client