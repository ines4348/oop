#include "pch.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: copyFile.exe <input file> <output file>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

void CopyStream(std::istream& inFile, std::ostream& outFile)
{
	char ch;
	while (inFile.get(ch))
	{
		if (!outFile.put(ch))
		{
			break;
		}
	}
}

bool CopyFile(const std::string& inputFileName, const std::string &outputFileName)
{
	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(inputFileName);
	if (!inFile.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	outFile.open(outputFileName);
	if (!outFile.is_open())
	{
		std::cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}

	CopyStream(inFile, outFile);

	if (inFile.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	if (!outFile.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!CopyFile(args->inputFileName, args->outputFileName))
	{
		return 1;
	}

	return 0;
}
