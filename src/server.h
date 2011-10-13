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


#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{
	using boost::asio::ip::tcp;
	using namespace std;

	extern int CONNECTION_COUNTER;

	class Session
	{
	public:

		Session(boost::asio::io_service& io_service);

		tcp::socket& socket();

		void start();

		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

		void handle_write(const boost::system::error_code& error);

	private:

		unsigned short uiClientPort_;

		std::string sClientIp_;

  		tcp::socket socket_;

		enum { max_length = 1024 };

		char data_[max_length];

	}; // END class session

	class Server
	{
	public:

		Server(boost::asio::io_service& io_service, short port);

		void handle_accept(Session* new_session, const boost::system::error_code& error);

	private:

		boost::asio::io_service& io_service_;

		tcp::acceptor acceptor_;

	}; // END class server

}

#endif // NETWORK_SERVER_H
