#include "pch.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <iomanip>

struct Args
{
	std::string nameOfInputDataFile;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: invert.exe <matrix file>\n";
		return std::nullopt;
	}

	Args arg;
	arg.nameOfInputDataFile = argv[1];
	return arg;
}

bool CopyDoubleFromFileToArray(std::istream& inFile, double** matrix)
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
					matrix[i][j] = std::stod(str);
				}
			}
		}
	}

	return true;
}

bool CopyMatrixFromFileToArray(const std::string& inputFileName, double** matrix)
{
	std::ifstream inputFile;

	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	if (!CopyDoubleFromFileToArray(inputFile, matrix))
	{
		std::cout << "Failed to copy data from " << inputFileName << " to matrix. Wrong input data\n";
		return false;
	}

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	return true;
}

//Ќайдем минор
void GetMinor(double** matrix, double** tempMatrix, int indRow, int indCol)
{
	int ki = 0;
	for (int i = 0; i < 3; i++)
	{
		if (i != indRow)
		{
			for (int j = 0, kj = 0; j < 3; j++)
			{
				if (j != indCol)
				{
					tempMatrix[ki][kj] = matrix[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
}

double GetDet(double** matrix, int matrixSize)
{
	double detMatrix = 0;
	if (matrixSize == 1)
		detMatrix = matrix[0][0];
	else if (matrixSize == 2)
		detMatrix = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	else
	{
		detMatrix += matrix[0][0] * matrix[1][1] * matrix[2][2];
		detMatrix += matrix[0][1] * matrix[1][2] * matrix[2][0];
		detMatrix += matrix[0][2] * matrix[1][0] * matrix[2][1];
		detMatrix -= matrix[0][2] * matrix[1][1] * matrix[2][0];
		detMatrix -= matrix[0][0] * matrix[1][2] * matrix[2][1];
		detMatrix -= matrix[0][1] * matrix[1][0] * matrix[2][2];
	}

	return detMatrix;
}

void FreeMemory(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void InverseMatrix(double** matrix, double** inverseMatrix, double detMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int m = 3 - 1;
			double** tempMatrix = new double*[m];
			for (int k = 0; k < m; k++)
				tempMatrix[k] = new double[m];
			GetMinor(matrix, tempMatrix, i, j);
			inverseMatrix[i][j] = pow(-1.0, i + j + 2) * GetDet(tempMatrix, m) / detMatrix;
			FreeMemory(tempMatrix, m);
		}
	}
}

void TransponMatrix(double** matrix, double** transponMatrix)
{ 
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			transponMatrix[j][i] = matrix[i][j];
}

void PrintMatrix(double** matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool GetInvertMatrix(const std::string& inputFileName)
{
	double **matrix;
	double **inverseMatrix;
	double **tInverseMatrix;
	matrix = new double * [3];
	inverseMatrix = new double * [3];
	tInverseMatrix = new double * [3];
	for (int i = 0; i < 3; i++)
	{
		matrix[i] = new double[3];
		inverseMatrix[i] = new double[3];
		tInverseMatrix[i] = new double[3];
	}

	matrix[0][0] = 1.2;

	//ќткроем файл и скопируем данные в массив
	if (!CopyMatrixFromFileToArray(inputFileName, matrix))
	{
		return false;
	}

	//Ќайдем определитель матрицы
	double detMatrix = GetDet(matrix, 3);

	//если определитель не равен 0, найти обратную матрицу
	if (detMatrix == 0)
	{
		std::cout << "Since the determinant of the matrix = 0, \nthe matrix is degenerate and has no inverse\n";
		return false;
	}

	InverseMatrix(matrix, inverseMatrix, detMatrix);

	//Ќайдем транспонированную союзную матрицу алгебраических дополнений
	TransponMatrix(inverseMatrix, tInverseMatrix);

	//распечатать
	PrintMatrix(tInverseMatrix);

	return true;
}

int main(int argc, char* argv[])
{
	auto arg = ParseArguments(argc, argv);

	if (!arg)
	{
		return 1;
	}

	if (!GetInvertMatrix(arg->nameOfInputDataFile))
	{
		return 1;
	}

	return 0;
}
