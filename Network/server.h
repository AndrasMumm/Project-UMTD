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
	Participant(tcp::socket* s, int i) {
		socket = s;
		id = i;
		connected = true;
	};
	~Participant()
	{
		delete socket;
		delete handlerThread;
	}

	bool operator==(const Participant& b)
	{
		return id == b.id;
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

public:
	//Participants
	std::vector<Participant*> participants;
	std::vector<Participant*> disconnectedParticipants;
	void HandleParticipant(Participant* participant);
	void ConnectionHandlerFunction();
	void CleanupConnections();

	Server(int port = DEFAULT_GAME_PORT);
	~Server();
};
