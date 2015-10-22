#ifndef Socket_h
#define Socket_h

#include <stdio.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <sstream>


class Socket {
public:
    Socket();
    ~Socket();
    std::vector<double> getMotors();
    
private:
    std::string getResponse(std::string query);
    int connectionFd, rc, index = 0, limit;
    struct sockaddr_in servAddr, localAddr;

};

#endif