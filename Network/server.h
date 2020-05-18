#pragma once
#include "connectionHandler.h"
#include "asio.h"

using boost::asio::steady_timer;
using boost::asio::ip::tcp;

class Participant
{
public:
	virtual ~Participant();
	virtual void deliver(const std::string& msg) = 0;
};

class Session : public ConnectionHandler, Participant, boost::enable_shared_from_this<Session>
{
private:
	//Private vars
	tcp::socket socket_;
	std::string input_buffer_;
	steady_timer input_deadline_;
	std::deque<std::string> output_queue_;
	steady_timer non_empty_output_queue_;
	steady_timer output_deadline_;

public:
	//Public methods
	Session(boost::asio::io_context& io_context);
	tcp::socket& socket();

	void init();

private:
	//Private methods

	void stop();
	bool stopped() const;
	void startRead();
	void handleRead(const boost::system::error_code& ec, std::size_t n);
	void awaitOutput();

	void startWrite();
	void handleWrite(const boost::system::error_code& ec);

	void checkDeadline(steady_timer* deadline);
};

class Server : public ConnectionHandler
{
};
