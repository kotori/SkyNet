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

// Common Includes.
#include <cstdlib>
#include <iostream>

// Management Library
#include "manager.h"

// Application's entry point.
int main(int argc, char* argv[])
{

    // Ensure an argument has been passed, otherwise show usage.
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }
    // I hate pointers
    KotoriApp::Manager *myManger = new KotoriApp::Manager(atoi(argv[1]));

    myManger->Start();

    delete myManger;

    return 0;
}
