#include "pch.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <limits>

typedef double Matrix3x3[3][3];

struct Args
{
	std::string nameOfInputDataFile;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: invert.exe <matrix file1>\n";
		return std::nullopt;
	}

	Args arg;
	arg.nameOfInputDataFile = argv[1];
	return arg;
}

bool copyDoubleFromFileToArray(std::istream& inFile, Matrix3x3 matrix)
{
	std::string str;
	const int matrixSize = 3;

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			if (inFile.eof())
			{
				return false;
			}
			else
			{
				inFile >> str;
				size_t notDigitPosition = str.find_first_not_of("0123456789-,.", 0);
				if (notDigitPosition == std::numeric_limits<size_t>::max())
				{
					matrix[i][j] = std::stof(str);
				}
			}
		}
	}

	return true;
}

bool copyMatrixFromFileToArray(const std::string& inputFileName)
{
	std::ifstream inputFile;

	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	Matrix3x3 matrix={};
	if (copyDoubleFromFileToArray(inputFile, matrix))
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{

				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}

	

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	return true;
}

bool getInvertMatrix(const std::string& inputFileName)
{
	//открыть файл и скопировать данные в массив
	copyMatrixFromFileToArray(inputFileName);

	//
	
	//найти определитель матрицы

	//если определитель не равен 0, найти обратную матрицу

	return true;
}

int main(int argc, char* argv[])
{
	auto arg = ParseArguments(argc, argv);

	if (!arg)
	{
		return 1;
	}

	getInvertMatrix(arg->nameOfInputDataFile);

	return 0;
}
