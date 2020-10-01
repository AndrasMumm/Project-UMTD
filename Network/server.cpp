#include "server.h"
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include "Packets/packet.h"
#include "Packets/PacketMgr.h"
#include "Packets/Testing/Ping.h"
#include "Packets/Testing/Pong.h"

Server::Server()
{
	PacketHandlerFunction pingPacketHandler = &Server::PingPacketHandler;
	PacketMgr::GetInstance().RegisterCallback(PING_OPCODE, pingPacketHandler);
}

Server::~Server()
{
	Server::CleanupConnections();

	delete _ioService;
	delete _acceptor;
}

bool Server::IsStarted()
{
	return _started;
}

void Server::Start(int port)
{
	_port = port;
	_newConnectionThread = std::thread([&](Server* server)
		{
			server->ConnectionHandlerFunction();
		}, this);

	_started = true;
}

void Server::Stop()
{
	//TODO:
	_started = false;
}


Participant* Server::GetParticipant(int id)
{
	auto it = participants.find(id);
	if (participants.end() == it)
	{
		std::cout << "ERROR: There is no participant with id " << id << std::endl;
		return nullptr;
	}

	return participants.at(id);
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

	participants = std::unordered_map<int, Participant*>();

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
		participants.insert({ pID, participant });
	}
}

const char* Server::ReadFromSocket(tcp::socket* socket, int* dataSize, boost::system::error_code& ec)
{
	boost::asio::streambuf buf;
	boost::asio::read_until(*socket, buf, char(PACKET_DELIMTER), ec);
	if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec))
	{
		return nullptr;
	}
	*dataSize = buf.size() - 1; //-1 because of delimiter
	char* data = new char[*dataSize];
	memcpy(data, buf.data().data(), *dataSize);

	return data;
}

void Server::SendOverSocket(tcp::socket* socket, const char* data, int dataSize)
{
	boost::asio::write(*socket, boost::asio::buffer(data, dataSize));
	//Delimiter
	char delimiter = PACKET_DELIMTER;
	boost::asio::write(*socket, boost::asio::buffer(&delimiter, 1));
}

void Server::Send(int participantID, Packet* p)
{
	int dSize = 0;
	char* data = p->GetRaw(&dSize);
	SendOverSocket(GetParticipant(participantID)->socket, data, dSize);
	delete[] data;
}

void Server::HandleParticipant(Participant* participant)
{
	while (participant->connected)
	{
		int dataSize = 0;
		boost::system::error_code ec;
		const char* data = ReadFromSocket(participant->socket, &dataSize, ec);
		if ((boost::asio::error::eof == ec) || (boost::asio::error::connection_reset == ec))
		{
			std::cout << "Participant " << participant->id << " disconnected!" << std::endl;
			break;
		}
		//Received packet, forwarding it to packet handler
		Packet* p = new Packet(data, dataSize);
		PacketMgr::GetInstance().Handle(p, participant->id);
		//Cleanup
		delete p;
		delete[] data;
	}

	//Marks for cleanup
	disconnectedParticipants.push_back(participant);
	//removing participant
	auto entry = participants.erase(participant->id);
}


void Server::PingPacketHandler(Packet* p, int sender)
{

	Ping ping = Ping(p);
	Pong pong = Pong(ping.GetMsg());
	Server::GetInstance().Send(sender, &pong);
}
