#pragma once

#include "DataPacket.h"
#include <vector>

class DataPacketHandler {
public:
	void MainProcess();
public:
	void Deserialize();
	void Trace();
public:
	std::vector<DataPacket> buffer;
};