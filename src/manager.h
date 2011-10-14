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
