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


// Common Includes
#include <iostream>
#include <string>

// BOOST Library headers
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

// Include headers for Session and Server classes
#include "server.h"

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{
	using boost::asio::ip::tcp;
	using namespace std;

	int CONNECTION_COUNTER;

	Session::Session(boost::asio::io_service& io_service) : socket_(io_service) { }

	tcp::socket& Session::socket()
	{
		return socket_;
	}

	void Session::start()
	{
		sClientIp_ = socket_.remote_endpoint().address().to_string();
		uiClientPort_ = socket_.remote_endpoint().port();
		cout << "Starting Session For " << sClientIp_ << ":" << uiClientPort_ << "\n";
		CONNECTION_COUNTER++;
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&Session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void Session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if(!error)
		{
			cout << "[" << sClientIp_ << "] Incoming Message\n";
			boost::asio::async_write(socket_, boost::asio::buffer(data_, bytes_transferred),
				boost::bind(&Session::handle_write, this, boost::asio::placeholders::error));
		}
		else
		{
			cout << "Closing Connection for " << sClientIp_ << "\n";
			CONNECTION_COUNTER--;
			delete this;
		}
	}

	void Session::handle_write(const boost::system::error_code& error)
	{
		cout << "Responding With Echo...\n";
		if(!error)
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length), boost::bind(&Session::handle_read,
				this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			delete this;
    		}
  	}



	Server::Server(boost::asio::io_service& io_service, short port) : io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		CONNECTION_COUNTER=0;
		cout << "Starting SkyNet Server on port " << port << "\n";
		Session *new_session = new Session(io_service_);
		acceptor_.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session,
			boost::asio::placeholders::error));
	}

	void Server::handle_accept(Session* new_session, const boost::system::error_code& error)
	{
		if(!error)
		{
			cout << "Incoming Connection Being Handled.\n";
			new_session->start();
			new_session = new Session(io_service_);
			acceptor_.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
		}
		else
		{
			delete new_session;
		}
	}
}
