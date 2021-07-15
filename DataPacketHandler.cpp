//disable warning compiler 
#pragma warning(disable : 4996)

#include "DataPacketHandler.h"

extern const char* PATH;

void DataPacketHandler::MainProcess() {
	Deserialize();
	Trace();
}

void DataPacketHandler::Deserialize() {
	FILE* file = fopen(PATH, "rb");
	if (!file) {
		printf("Deserialize. Error! Can't open file!\n");
		return;
	}
	while (!feof(file)) {
		DataPacket data_packet;
		memset(&data_packet, 0, sizeof(DataPacketHead));
		if (!fread(&data_packet, sizeof(DataPacketHead), 1, file)) {
			break;
		}
		if (data_packet.start_marker != DataPackeHeadConst::START_MARKER) {
			break;
		}
		if (data_packet.size < 1) {
			break;
		}
		data_packet.data.resize(data_packet.size);
		if (!fread(&data_packet.data[0], data_packet.size, 1, file)) {
			break;
		}
		buffer.push_back(data_packet);
	}
	fclose(file);
}

void DataPacketHandler::Trace() {
	printf("Handle DataPacket:\n");
	for (DataPacket& data_packet : buffer) {
		unsigned char* head = (unsigned char*)&data_packet;
		for (unsigned int i = 0; i < sizeof(DataPacketHead); i++) {
			printf("%02x ", head[i]);
		}
		for (unsigned char data : data_packet.data) {
			printf("%02x ", data);
		}
		printf("\n");
	}
	printf("\n");
}