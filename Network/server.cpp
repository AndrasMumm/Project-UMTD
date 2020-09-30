#include "server.h"
#include <algorithm>
#include <boost/lexical_cast.hpp>

Server::Server(int port)
{
	_port = port;
	_newConnectionThread = std::thread([&](Server* server)
		{
			server->ConnectionHandlerFunction();
		}, this);
}

Server::~Server()
{
	Server::CleanupConnections();

	delete _ioService;
	delete _acceptor;
}

void Server::CleanupConnections()
{
	for (auto exParticipant : disconnectedParticipants)
	{

		exParticipant->connected = false;
		if (exParticipant->handlerThread->joinable())
		{
			exParticipant->handlerThread->join();
		}

		delete exParticipant;
	}
}

void Server::ConnectionHandlerFunction()
{
	_ioService = new io_service();
	auto ip = ip::address_v4::from_string("127.0.0.1");
	auto endpoint = ip::tcp::endpoint(ip, _port);
	_acceptor = new tcp::acceptor(*_ioService, endpoint);
	std::cout << "Listenting to port " << _port << " on IP " << boost::lexical_cast<std::string>(ip) << std::endl;

	_idCounter = 0;
	while (true)
	{
		tcp::socket* socket = new tcp::socket(*_ioService);
		_acceptor->accept(*socket);

		int pID = _idCounter++;
		Participant* participant = new Participant(socket, pID);
		std::cout << "New Participant with ID " << pID << " and IP " << boost::lexical_cast<std::string>(socket->remote_endpoint()) << std::endl;
		std::thread* t = new std::thread([&](Server* server) {
			server->HandleParticipant(participant);
			}, this);
		participant->handlerThread = t;
		participants.push_back(participant);
	}
}

//#define PACKET_DELIMTER 29
#define PACKET_DELIMTER 'A'
const char* ReadFromSocket(tcp::socket* socket, int* dataSize)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(*socket, buf, char(PACKET_DELIMTER));
	*dataSize = buf.size();
	char* data = new char[*dataSize];
	memcpy(data, buf.data().data(), *dataSize);

	return data;
}

void SentOverSocket(tcp::socket* socket, const char* data, int dataSize)
{
	boost::asio::write(*socket, boost::asio::buffer(data, dataSize));
	//Delimiter
	char delimiter = PACKET_DELIMTER;
	boost::asio::write(*socket, boost::asio::buffer(&delimiter, 1));
}

void Server::HandleParticipant(Participant* participant)
{
	while (participant->connected)
	{
		int dataSize = 0;
		const char* data = ReadFromSocket(participant->socket, &dataSize);
		std::cout << "Received packet from Participant " << participant->id << ": " << std::string(data, dataSize) << std::endl;
		std::string answer = std::string("Please work");
		SentOverSocket(participant->socket, answer.c_str(), answer.size());
		delete[] data;
	}

	//Marks for cleanup
	disconnectedParticipants.push_back(participant);
	auto entry = std::find(participants.begin(), participants.end(), participant);
	if (entry != participants.end())
	{
		participants.erase(entry);
	}
}
