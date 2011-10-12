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

    KotoriApp::Manager *myManger = new KotoriApp::Manager(atoi(argv[1]));

    myManger->Start();

    delete myManger;

    return 0;
}
