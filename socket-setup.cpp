#include "socket-setup.hpp"


std::string Recieved (1024,'\0');
int ClientSocket=0;
int ServerSocket=0;

int Socket_Init()
{
    int ServerSocket = socket(AF_INET, SOCK_STREAM, 0 );
    sockaddr_in ServerAdress;
    ServerAdress.sin_family = AF_INET;
    ServerAdress.sin_port = htons(SOCKET_NO);
    ServerAdress.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    bind(ServerSocket, (struct sockaddr*)&ServerAdress, sizeof(ServerAdress) );
    listen(ServerSocket,10);
    std::cout << "Listening..." << "\n";    
    return ServerSocket;
}

std::string Receive_message()
{
    std::string buffer(1024,'\0');
    int recieved_bytes = recv(ClientSocket, &buffer[0], sizeof(buffer), 0);

    if(recieved_bytes)
    {
        buffer.resize(recieved_bytes);
    }
    else
    {
        std::cout << "There is a problem recieving the message\n";
    }

    return buffer;
}

void Send_Response(std::string message)
{
    message = "\033[34m" + message + "\033[0m"; // "\033[34m" makes the color blue and "\033[0m" resets the color
    send(ClientSocket, message.c_str(), message.size(), 0);
}


void Close_Connection_With(int connection)
{
    close(connection);
}


void Run(const std::string& process)
{
    std::string command = "pgrep -x "+process+" > /dev/null";
    if(system(command.c_str())) // equals one if the process isnt running
        {
            system((process+" &").c_str());
            Send_Response("The Process is now running\n");  
        }
    else
        {
            Send_Response("The Process is already running\n");  
        }
}

void Kill(const std::string& process)
{
    std::string command = "pkill "+process;
    if(system(command.c_str())==0) // equals 0 if the process was terminated
        {
            Send_Response("The Process was terminated successfully\n");  
        }
    else
        {
            Send_Response("The Process is already closed\n");  
        }
}