// Common Includes.
#include <cstdlib>
#include <iostream>

// Boost Libraries.
#include <boost/bind.hpp>
#include <boost/asio.hpp>

// Network Server Library.
#include "network_server.hpp"

// Boost ASIO Namespace.
using boost::asio::ip::tcp;

// Application's entry point.
int main(int argc, char* argv[])
{
    try
    {
        // Ensure an argument has been passed, otherwise show usage.
        if(argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <port>\n";
            return 1;
        }
        else
        {
            // Create a boost::asio io_service object.
            boost::asio::io_service io_service;
            KotoriApp::Server s(io_service, atoi(argv[1]));
            io_service.run();
        }
    }
    catch(std::exception& excp)
    {
        // If an exception has been caught, display it then exit.
        std::cerr << "Exception: " << excp.what() << "\n";
        return 1;
    }

    return 0;
}
