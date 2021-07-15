//disable warning compiler 
#pragma warning(disable : 4996)

#include "DataPacketGenerator.h"
#include <ctime>

extern const char* PATH;

void DataPacketGenerator::MainProcess() {
	srand((unsigned int)time(0));
	while (buffer.size() < 16) {
		GenerateRandomData();
	}
	Trace();
	Serialize();
}

void DataPacketGenerator::GenerateRandomData() {
	DataPacket data_packet;
	data_packet.start_marker = DataPackeHeadConst::START_MARKER;
	//random buffer size from 2 to 32 bit
	data_packet.size = rand() % 31 + 2;
	for (int i = 0; i < data_packet.size; i++) {
		unsigned char data = ((i > 0) && (data_packet.data[i - 1] == 0xFF)) ? rand() % 0x100 : rand() % 0xFF;
		data_packet.data.push_back(data);
	}
	buffer.push_back(data_packet);
}

void DataPacketGenerator::Serialize() {
	FILE* file = fopen(PATH, "wb");
	if (!file) {
		printf("Serialize. Error! Can't open file!\n");
		return;
	}
	for (DataPacket& data_packet : buffer) {
		unsigned char* head = (unsigned char*)&data_packet;
		fwrite(head, sizeof(DataPacketHead), 1, file);
		unsigned char* data = data_packet.data.data();
		fwrite(data, data_packet.data.size(), 1, file);
	}
	fclose(file);
}

void DataPacketGenerator::Trace() {
	printf("Generate DataPacket:\n");
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