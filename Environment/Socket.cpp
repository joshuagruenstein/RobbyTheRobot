#include "Socket.h"

#define MAX_BUFFER 128
#define HOST "127.0.0.1"
#define PORT 50007

Socket::Socket(void) {
    limit = MAX_BUFFER;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = inet_addr(HOST);
    
    connectionFd = socket(AF_INET, SOCK_STREAM, 0);
    
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);
    rc = bind(connectionFd,(struct sockaddr *) &localAddr, sizeof(localAddr));
    
    connect(connectionFd,(struct sockaddr *)&servAddr, sizeof(servAddr));
}

Socket::~Socket(void) {
    close(connectionFd);
}

std::vector<double> Socket::getOutputs(std::vector<double> sensors) {
    std::string mString = getResponse(senseString(sensors));
    std::vector<double> mVect;
    std::string::size_type pos = mString.find('|');
    if (pos != std::string::npos) mString = mString.substr(0, pos);
    std::stringstream ss(mString);
    double i; while (ss >> i) {
        mVect.push_back(i);
        if (ss.peek()==',') ss.ignore();
    } return mVect;
}

std::string Socket::senseString(std::vector<double> sensors) {
    std::ostringstream oss;
    if (!sensors.empty()) {
        std::copy(sensors.begin(), sensors.end()-1,
                  std::ostream_iterator<double>(oss, ","));
        oss << sensors.back();
    } return oss.str();
}

std::string Socket::getResponse(std::string query) {
    char buffer[MAX_BUFFER+1];
    sprintf(buffer, "%s", query.c_str());
    send(connectionFd, buffer, strlen(buffer), 0);
    sprintf(buffer, "%s", "");
    recv(connectionFd, buffer, MAX_BUFFER, 0);
    std::string mString(buffer);
    return mString;
}