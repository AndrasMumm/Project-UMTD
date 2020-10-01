#pragma once
class Packet
{
	short opcode;
	char* data;
	int dataSize;

	Packet(int opc) :opcode(opc) {};
	~Packet() {
		delete[] data;
	}
};
