/*! \file manager.h
    \brief Game Server Management Header

    Game Server Management Header. Brings together all of the functions that are in a game server.
*/

#ifndef MANAGER_H
#define MANAGER_H

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{

/*! \class Manager
    \brief Manager class

    Manager class brings together all of the functions that are in a game server.
*/
class Manager
{
public:
    /*! \fn Manager()
        \brief Database class constructor

        Manager class constructor. Takes no arguments.
    */
    Manager(int port);

    int Start();

    int Stop();

private:

    int port_;
    int conn_limit_;
    int current_conn_;
};

}


#endif // MANAGER_H
