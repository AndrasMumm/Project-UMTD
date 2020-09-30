#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
using namespace boost::asio;
using ip::tcp;

#define DEFAULT_GAME_PORT 1234

class Participant
{
public:
	tcp::socket* socket;
	int id;
	std::thread* handlerThread;
	bool connected;
	Participant(tcp::socket* s, int i) : socket(s) {
		id = id;
		connected = true;
	};
	~Participant()
	{
		delete socket;
		delete handlerThread;
	}
};

class Server {
private:
	//TCP server
	io_service* _ioService;
	tcp::acceptor* _acceptor;
	int _port;
	int _idCounter;

	//Handling new connections and killing old ones
	std::thread _newConnectionThread;
	void ConnectionHandlerFunction();
	void CleanupConnections();

	//Participants
	std::vector<Participant> _participants;
	std::vector<Participant*> _disconnectedParticipants;

	void HandleParticipant(Participant* participant);
public:
	Server(int port = DEFAULT_GAME_PORT);
	~Server();
};
