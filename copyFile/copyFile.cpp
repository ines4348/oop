#include "pch.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args {
  std::string inputFileName;
  std::string outputFileName;
};

std::optional<Args> parseArguments(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Invalid argument count\n ";
    std::cout << "Usage: lab1_CopyFile.exe <input file> <output file>\n ";
    return std::nullopt;
  }

  Args args;
  args.inputFileName = argv[1];
  args.outputFileName = argv[2];
  return args;
}

void copyFile(std::ifstream &inFile, std::ofstream &outFile) {
  char ch;
  while (inFile.get(ch)) {
    if (!outFile.put(ch)) {
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  auto args = parseArguments(argc, argv);

  if (!args) {
    return 1;
  }

  std::ifstream inFile;
  inFile.open(args->inputFileName);
  if (!inFile.is_open()) {
    std::cout << "Failed to open " << args->inputFileName << " for reading";
    return 1;
  }

  std::ofstream outFile;
  outFile.open(args->outputFileName);
  if (!outFile.is_open()) {
    std::cout << "Failed to open " << args->outputFileName << " for writing";
    return 1;
  }

  copyFile(inFile, outFile);

  if (inFile.bad()) {
    std::cout << "Failed to read data from input file";
    return 1;
  }

  if (!outFile.flush()) {
    std::cout << "Failed to write data to output file";
    return 1;
  }
  return 0;
}
