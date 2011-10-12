/*! \file manager.cpp
    \brief SQLite3 C++ Wrapper

    Game Server Management Class. Brings together all of the functions that are in a game server.
*/

// Common Includes.
#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "server.h"

// Load the Management class header.
#include "manager.h"

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{

Manager::Manager(int port)
{
    port_ = port;
}

int Manager::Start()
{
    //

    bool exit_main_loop = false;

    while(!exit_main_loop)
    {
        try
        {
            // Create a boost::asio io_service object.
            boost::asio::io_service io_service;
            KotoriApp::Server s(io_service, port_);
            io_service.run();
        }
        catch(std::exception& excp)
        {
            // If an exception has been caught, display it then exit.
            std::cerr << "Exception: " << excp.what() << "\n";
            return 1;
        }
    }

    return 0;
}

int Manager::Stop()
{
    //
    
    return 0;
}

}

