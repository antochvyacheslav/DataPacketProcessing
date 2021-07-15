#include <cstdio>
#include "DataPacketGenerator.h"
#include "DataPacketHandler.h"

const char* PATH = "D:\\Projects\\Demo\\bin_file.bin";

DataPacketGenerator data_packet_generator;
DataPacketHandler data_packet_handler;

int main() {
	data_packet_generator.MainProcess();
	data_packet_handler.MainProcess();
	return 0;
}