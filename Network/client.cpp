#include "client.h"

Client::Client(boost::asio::io_context& io_context) :
	running_(true),
	socket_(io_context),
	deadline_(io_context),
	heartbeat_timer_(io_context)
{
}

void Client::connect(tcp::resolver::results_type endpoints)
{
	endpoints_ = endpoints;
	startConnect(endpoints.begin());

	// Start the deadline actor. You will note that we're not setting any
	// particular deadline here. Instead, the connect and input actors will
	// update the deadline prior to each asynchronous operation.
	deadline_.async_wait(boost::bind(&Client::checkDeadline, this));
}

void Client::disconnect()
{
	running_ = false;
	boost::system::error_code ignored_ec;
	socket_.close(ignored_ec);
	deadline_.cancel();
	heartbeat_timer_.cancel();
}

void Client::startConnect(tcp::resolver::results_type::iterator endpoint_iter)
{
	if (endpoint_iter != endpoints_.end())
	{
		std::cout << "Trying " << endpoint_iter->endpoint() << "...\n";

		// Set a deadline for the connect operation.
		deadline_.expires_after(boost::asio::chrono::seconds(60));

		// Start the asynchronous connect operation.
		socket_.async_connect(endpoint_iter->endpoint(),
			boost::bind(&Client::handleConnect,
				this, _1, endpoint_iter));
	}
	else
	{
		//There are no more endpoints to try. Shutting down the client.
		disconnect();
	}
}

void Client::handleConnect(const boost::system::error_code& ec, tcp::resolver::results_type::iterator endpoint_iter)
{
	if (!running_)
		return;

	// The async_connect() function automatically opens the socket at the start
	// of the asynchronous operation. If the socket is closed at this time then
	// the timeout handler must have run first.
	//

	if (!socket_.is_open())
	{
		std::cout << "Connect timed out\n";

		//Trying to reconnect
		startConnect(endpoint_iter);
	}
	// Check if the connect operation failed before the deadline expired.
	else if (ec)
	{
		std::cout << "Connect error: " << ec.message() << "\n";
		// We need to close the socket used in the previous connection attempt
		// before starting a new one.
		socket_.close();

		// Try to reconnect
		startConnect(endpoint_iter);
	}
	// Otherwise we have successfully established a connection.
	else
	{
		std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";

		// Start the input actor.
		startRead();

		// Start the heartbeat actor.
		startWrite();
	}
}

void Client::startRead()
{
	// Set a deadline for the read operation.
	deadline_.expires_after(boost::asio::chrono::seconds(30));

	// Start an asynchronous operation to read a newline-delimited message.
	boost::asio::async_read_until(socket_,
		boost::asio::dynamic_buffer(input_buffer_), '\n',
		boost::bind(&Client::handleRead, this, _1, _2));
}

void Client::handleRead(const boost::system::error_code& ec, std::size_t n)
{
	if (!running_)
		return;

	if (!ec)
	{
		// Extract the newline-delimited message from the buffer.
		std::string line(input_buffer_.substr(0, n - 1));
		input_buffer_.erase(0, n);

		// Empty messages are heartbeats and so ignored.
		if (!line.empty())
		{
			std::cout << "Received: " << line << "\n";
		}

		startRead();
	}
	else
	{
		std::cout << "Error on receive: " << ec.message() << "\n";

		disconnect();
	}
}

void Client::startWrite()
{
	if (!running_)
		return;

	// Start an asynchronous operation to send a heartbeat message.
	boost::asio::async_write(socket_, boost::asio::buffer("\n", 1),
		boost::bind(&Client::handleWrite, this, _1));
}

void Client::handleWrite(const boost::system::error_code& ec)
{
	if (!running_)
		return;

	if (!ec)
	{
		// Wait 10 seconds before sending the next heartbeat.
		heartbeat_timer_.expires_after(boost::asio::chrono::seconds(10));
		heartbeat_timer_.async_wait(boost::bind(&Client::startWrite, this));
	}
	else
	{
		std::cout << "Error on heartbeat: " << ec.message() << "\n";

		disconnect();
	}
}

void Client::checkDeadline()
{
	if (!running_)
		return;

	// Check whether the deadline has passed. We compare the deadline against
	// the current time since a new asynchronous operation may have moved the
	// deadline before this actor had a chance to run.
	if (deadline_.expiry() <= steady_timer::clock_type::now())
	{
		// The deadline has passed. The socket is closed so that any outstanding
		// asynchronous operations are cancelled.
		socket_.close();

		// There is no longer an active deadline. The expiry is set to the
		// maximum time point so that the actor takes no action until a new
		// deadline is set.
		deadline_.expires_at(steady_timer::time_point::max());
	}

	// Put the actor back to sleep.
	deadline_.async_wait(boost::bind(&Client::checkDeadline, this));
}