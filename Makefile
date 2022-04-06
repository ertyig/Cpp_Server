server:
	g++ util.cpp client.cpp -o client && \
	g++ util.cpp server.cpp InetAddress.cpp Epoll.cpp Socket.cpp Channel.cpp -o server
clean:
	rm server && rm client