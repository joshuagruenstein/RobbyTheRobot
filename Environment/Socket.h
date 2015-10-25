#ifndef Socket_h
#define Socket_h

#ifdef WIN32
    #include <sys/types.h>
    #include <Winsock2.h>
    #define WINSOCKVERSION MAKEWORD(2,2)
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <time.h>
#endif

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

class Socket {
public:
    Socket();
    ~Socket();
    std::vector<double> getOutputs(std::vector<double> sensors);
private:
    std::string getResponse(std::string query);
    std::string senseString(std::vector<double> sensors);
    int connectionFd, rc, index = 0, limit;
    struct sockaddr_in servAddr, localAddr;
};

#endif
