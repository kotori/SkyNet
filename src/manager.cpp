/*
* Copyright (C) 2011 Kotori <https://github.com/kotori>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/


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

