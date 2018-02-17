#include <RCSwitch.h>
#include <iostream>

#include "CRC.hpp"

#define RXPIN 2




typedef struct __attribute__ ((packed))
{
	char id;
	char key[2];
	float value;
	char crc;
} SensorMsg_t;



class RingInterpreter {
public:
	uint32_t buffer[2];
	SensorMsg_t* msg;

	CRC8Calc crc;

	RingInterpreter() { 
		crc.setPolynomial(CRC8Calc::SMBUS); 
		msg = (SensorMsg_t*) buffer;
	}

	void push(uint32_t value)
	{
		buffer[0] = buffer[1];
		buffer[1] = value;
	}

	bool valid() const
	{
		int a = crc.checksum((char*)buffer, 7);
		int b = msg->crc;
		//std::cout << "CRC: " << a << " vs " << b << std::endl;
		return a == b;
	}

	SensorMsg_t getMessage() {
		SensorMsg_t copy;
		memcpy(&copy, msg, sizeof(SensorMsg_t));
		return copy;
	}
};


int main(int argc, char** args)
{

	RingInterpreter parser;

	if (wiringPiSetup() == -1) return 1;
	pullUpDnControl(RXPIN, PUD_OFF);

	RCSwitch wireless;
	wireless.enableReceive(RXPIN);
	wireless.setRepeatTransmit(1);

	std::cout << "waiting for data..." << std::endl;
	
	while(true)
	{
		if (wireless.available())
		{
			//std::cout << "Got something! " << wireless.getReceivedBitlength() << " bits: " << std::flush;
			int value = wireless.getReceivedValue();
			//std::cout << value << std::endl;
			wireless.resetAvailable();

			// process
			parser.push(value);
			if (parser.valid())
			{
				SensorMsg_t msg = parser.getMessage();
				std::cout << (int)msg.id << " " << msg.key[0] << msg.key[1] << " " << msg.value << " " << std::endl;
			}
		}

	}
	
}
