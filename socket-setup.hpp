#ifndef SOCKETSETUP_HPP
#define SOCKETSETUP_HPP


#include <iostream>
#include <string>
#include <utility>

#include <sys/socket.h> // for socket(), bind() function
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h>     // for close()
#include <arpa/inet.h>  // for inet_addr()

#define ZERO 0
#define XTERM 1
#define FIREFOX 2

#define IP_ADDRESS "192.168.1.36"
#define SOCKET_NO 9099

extern std::string Recieved ;
extern int ClientSocket;
extern int ServerSocket;

int Socket_Init();
std::string Receive_message();
void Send_Response(std::string message);
void Close_Connection_With(int connection);
void Run(const std::string& process);
void Kill(const std::string& process);

#endif