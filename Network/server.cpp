#include "server.h"

Session::Session(boost::asio::io_context& io_context) :
	socket_(io_context),
	input_deadline_(io_context),
	non_empty_output_queue_(io_context),
	output_deadline_(io_context)
{
	input_deadline_.expires_at(steady_timer::time_point::max());
	output_deadline_.expires_at(steady_timer::time_point::max());

	// The non_empty_output_queue_ steady_timer is set to the maximum time
	// point whenever the output queue is empty. This ensures that the output
	// actor stays asleep until a message is put into the queue.
	non_empty_output_queue_.expires_at(steady_timer::time_point::max());
}

tcp::socket& Session::socket()
{
	return socket_;
}

void Session::stop()
{
}

bool Session::stopped() const
{
}

void Session::startRead()
{
}

void Session::handleRead(const boost::system::error_code& ec, std::size_t n)
{
}

void Session::awaitOutput()
{
}

void Session::startWrite()
{
}

void Session::handleWrite(const boost::system::error_code& ec)
{
}

void Session::checkDeadline(steady_timer* deadline)
{
}