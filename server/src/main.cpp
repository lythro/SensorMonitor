#include <RCSwitch.h>
#include <iostream>

#define RXPIN 2


int main(int argc, char** args)
{
	if (wiringPiSetup() == -1) return 1;
	pullUpDnControl(RXPIN, PUD_OFF);

	RCSwitch wireless;
	wireless.enableReceive(RXPIN);

	std::cout << "waiting for data..." << std::endl;
	
	while(true)
	{
		if (wireless.available())
		{
			std::cout << "Got something! " << std::flush;
			int value = wireless.getReceivedValue();
			std::cout << value << std::endl;

			wireless.resetAvailable();
		}

		delay(100);
	}
	
}
