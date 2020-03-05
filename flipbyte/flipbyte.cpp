#include "pch.h"
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string operand;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: flipbyte.exe <integer 0..255>\n";
		return std::nullopt;
	}

	Args arg;
	arg.operand = argv[1];
	return arg;
}

void FlipByte(uint16_t& x)
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
	auto args = ParseArguments(argc, argv);

	if (!args)
	{
		return 1;
	}

	uint16_t x = 0;
	size_t found = args->operand.find_first_not_of("0123456789", 0);

	if (found == -1)
	{
		x = std::stoi(args->operand);
	}
	else
	{
		std::cout << "The argument contains characters other than numbers. Usage: flipbyte.exe <integer 0..255>\n";
		return 1;
	}

	if (x > 255)
	{
		std::cout << "Invalid argument value. Usage: flipbyte.exe <integer 0..255>\n";
		return 1;
	}

	FlipByte(x);
	std::cout << x;

	return 0;
}
