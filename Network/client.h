#pragma once
#include "connectionHandler.h"
#include "asio.h"

using boost::asio::steady_timer;
using boost::asio::ip::tcp;

class Client : public ConnectionHandler
{
private:
	//Private vars
	bool running_;
	tcp::resolver::results_type endpoints_;
	tcp::socket socket_;
	std::string input_buffer_;
	steady_timer deadline_;
	steady_timer heartbeat_timer_;
public:
	//Public methods
	Client(boost::asio::io_context& io_context);
	void connect(tcp::resolver::results_type endpoints);
	void disconnect();

private:
	//Private methods
	void startConnect(tcp::resolver::results_type::iterator endpoint_iter);
	void handleConnect(const boost::system::error_code& ec, tcp::resolver::results_type::iterator endpoint_iter);

	void startRead();
	void handleRead(const boost::system::error_code& ec, std::size_t n);

	void startWrite();
	void handleWrite(const boost::system::error_code& ec);

	void checkDeadline();
};
