// Author: Kotori
// Date: 5 Oct 2011

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
