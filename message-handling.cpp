#include "message-handling.hpp"


int Continue_Flag=1;
void Message_Handle(std::string message)
{
    // converting all string to lower case characters
    std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c){ return std::tolower(c); });

   int found = Recieved.find("end") ;
        if(found != std::string::npos)
        {
            std::cout << "ana dkhalt f end\n";
            Send_Response("the prgram will end now\n");
            Close_Connection_With(ClientSocket);
            Continue_Flag=0;
            return;
        }
    
    found = Recieved.find("open terminal");
    
    if(found != std::string::npos)
        {
            Run("xterm");
            return;
        }

    found = Recieved.find("close terminal");
    
    if(found != std::string::npos)
        {
            Kill("xterm");
            std::system("pkill xterm"); 
            return;
        }

    found = Recieved.find("open firefox");
    
    if(found != std::string::npos)
        {
            Run("firefox");
            return;
        }

    found = Recieved.find("close firefox");
    
    if( found != std::string::npos)
        {
            Kill("firefox");
            return;
        }

    found = Recieved.find("open notes");
    if( found != std::string::npos)
        {
            Run("obsidian");
            return;
        }

    found = Recieved.find("close notes");
    if( found != std::string::npos)
        {
            Kill("obsidian");
            return;
        }


    found = Recieved.find("show history");
    if( found != std::string::npos)
        {
            Database_SELECT();
            Send_Response(History);
            //std::cout << "History printing" << History << "\n";
            History.clear();
            return;
        }

    found = Recieved.find("clear history");
    if( found != std::string::npos)
        {
            Send_Response("History is cleared\n");
            Database_DELETE();
            History.clear();
            return;
        }
    


    found = Recieved.find("open calculator");
    if( found != std::string::npos)
        {
            Run("gnome-calculator");
            return;
        }

    found = Recieved.find("close calculator");
    if( found != std::string::npos)
        {
            Kill("gnome-calculator");
            return;
        }
    
    found = Recieved.find("open ubuntu software");
    if( found != std::string::npos)
        {
            Run("gnome-software");
            return;
        }

    found = Recieved.find("close ubuntu software");
    if( found != std::string::npos)
        {
            Kill("gnome-software");
            return;
        }
    
    
//found != std::string::npos

    std::cout << "ana dkhalt f akher end\n";
    Send_Response("Server:\n"\
                  "Unknown Command...\n" \
                  "Please choose one of the following\n" \
                  "1- Open terminal\n" \
                  "2- Close terminal\n" \
                  "3- Open firefox\n" \
                  "4- Close firefox\n" \
                  "5- Show history\n" \
                  "6- Clear history\n");

}






