#pragma once

#include "DataPacket.h"
#include <vector>

class DataPacketGenerator {
public:
	void MainProcess();
public:
	void GenerateRandomData();
	void Serialize();
	void Trace();
public:
	std::vector<DataPacket> buffer;
};