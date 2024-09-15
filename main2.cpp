#include "socket-setup.hpp"
#include "message-handling.hpp"
#include "database.hpp"

#include <cstdlib>      // for the system


int main()
{

    Database_TABLE_CREATION();
    ServerSocket = Socket_Init();
    ClientSocket = accept(ServerSocket, nullptr, nullptr );

    while(Continue_Flag)
    {
        Recieved = Receive_message();
        //Received = trim(Received) ;
        Database_INSERT(Recieved);
        Message_Handle(Recieved);
    }
    
    std::cout << "/******** History *********/\n";
    //Database_SELECT();
    Close_Connection_With(ServerSocket);
    Database_DELETE();
    Database_Close();

    return 0;
}




