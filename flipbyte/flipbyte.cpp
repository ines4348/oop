#include "pch.h"
#include <iostream>
#include <limits>
#include <optional>
#include <string>

struct Args
{
	std::string argumentOfProgramm;
	uint8_t numberToFlipByte = 0;
	bool isParsingArgumentSuccessful = false;
};

void verifyArgument(Args &arg)
{
	int tempNumberToFlipByte;
	size_t found = arg.argumentOfProgramm.find_first_not_of("0123456789", 0);

	if (found == std::numeric_limits<size_t>::max())
	{
		tempNumberToFlipByte = std::stoi(arg.argumentOfProgramm);
	}
	else
	{
		std::cout << "The argument contains characters other than numbers. Usage: flipbyte.exe <integer 0..255>\n";
	}

	if (tempNumberToFlipByte < std::numeric_limits<uint8_t>::min() || tempNumberToFlipByte > std::numeric_limits<uint8_t>::max())
	{
		std::cout << "Invalid argument value. Usage: flipbyte.exe <integer 0..255>\n";
	}
	else
	{
		arg.numberToFlipByte = tempNumberToFlipByte;
		arg.isParsingArgumentSuccessful = true;
	}
}

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: flipbyte.exe <integer 0..255>\n";
		return std::nullopt;
	}

	Args arg;
	arg.argumentOfProgramm = argv[1];
	verifyArgument(arg);
	return arg;
}

void FlipByte(uint8_t& x)
{
	// Четные и нечетные биты поменялись местами.
	x = ((x & 0x55) << 1) | ((x >> 1) & 0x55);
	// Биты "перетасовываются" группами по два.
	x = ((x & 0x33) << 2) | ((x >> 2) & 0x33);
	// Биты "перетасовываются" группами по четыре.
	x = ((x & 0x0F) << 4) | ((x >> 4) & 0x0F);
}

int main(int argc, char* argv[])
{
	auto arg = ParseArguments(argc, argv);

	if (!arg->isParsingArgumentSuccessful)
	{
		return 1;
	}

	FlipByte(arg->numberToFlipByte);
	std::cout << static_cast<int>(arg->numberToFlipByte) << "\n";

	return 0;
}
