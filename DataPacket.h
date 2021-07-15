#pragma once
#include <vector>

class DataPackeHeadConst {
public:
	static const unsigned short START_MARKER = 0xFFFF;
};

#pragma pack(push, 1)
struct DataPacketHead {
	unsigned short start_marker;
	unsigned char size;
};

struct DataPacket : DataPacketHead {
	std::vector<unsigned char> data;
};

#pragma pack(pop)