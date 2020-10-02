#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <unordered_map>
#include "Packets/PacketMgr.h"

using namespace boost::asio;
using ip::tcp;

#define ALL_PARTICIPANTS_ID -1
#define SERVER_ID -2
#define NOBODY_ID -3


#define DEFAULT_GAME_PORT 1234


#define PACKET_DELIMTER 29 //'A'

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
public:
	static Server& GetInstance()
	{
		static Server server;
		return server;
	}

private:
	//TCP server
	io_service* _ioService;
	tcp::acceptor* _acceptor;
	int _port;
	int _idCounter;

	//Handling new connections
	std::thread _newConnectionThread;

	bool _started;

	Server();
	~Server();

public:
	//Participants
	std::unordered_map<int, Participant*> participants;
	std::vector<Participant*> disconnectedParticipants;

	Participant* GetParticipant(int id);
	void HandleParticipant(Participant* participant);
	void ConnectionHandlerFunction();
	void CleanupConnections();

	const char* ReadFromSocket(tcp::socket* socket, int* dataSize, boost::system::error_code& ec);
	void SendOverSocket(tcp::socket* socket, const char* data, int dataSize);
	void Send(int participantID, Packet* p);

	bool IsStarted();
	void Start(int port = DEFAULT_GAME_PORT);
	void Stop();

	static void PingPacketHandler(Packet* p, int sender);
};
