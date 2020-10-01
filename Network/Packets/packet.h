#pragma once
#include <vector>
class Packet
{
	short _opcode;
public:
	std::vector<char> data;
	short GetOpcode() {
		return _opcode;
	}

	void SetOpcode(short opcode)
	{
		_opcode = opcode;
	}

	virtual char* GetRaw(int* dataSize)
	{
		*dataSize = data.size() + 2;
		char* d = new char[*dataSize];
		*((short*)d) = _opcode;
		memcpy(d + 2, data.data(), data.size());
		return d;
	}

	//Should be overwritten
	Packet() = default;

	Packet(int opc) :_opcode(opc) {};
	Packet(const char* d, int dSize)
	{
		SetOpcode(*((short*)d));
		int actualDataSize = dSize - 2;
		data.resize(actualDataSize);
		memcpy(data.data(), d, actualDataSize);
	};
	~Packet() {}
};
