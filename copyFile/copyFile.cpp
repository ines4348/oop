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

void copyStream(std::istream &inFile, std::ostream &outFile) {
  char ch;
  while (inFile.get(ch)) {
    if (!outFile.put(ch)) {
      break;
    }
  }
}

bool openInOutFiles(std::ifstream &inFile, std::ofstream &outFile,
                    std::string &inputFileName, std::string &outputFileName) {

  inFile.open(inputFileName);
  if (!inFile.is_open()) {
    std::cout << "Failed to open " << inputFileName << " for reading";
    return false;
  }

  outFile.open(outputFileName);
  if (!outFile.is_open()) {
    std::cout << "Failed to open " << outputFileName << " for writing";
    return false;
  }

  return true;
}

bool copyFile(std::string inputFileName, std::string outputFileName) {
  std::ifstream inFile;
  std::ofstream outFile;

  if (!openInOutFiles(inFile, outFile, inputFileName, outputFileName)) {
    return false;
  }

  copyStream(inFile, outFile);

  if (inFile.bad()) {
    std::cout << "Failed to read data from input file";
    return false;
  }

  if (!outFile.flush()) {
    std::cout << "Failed to write data to output file";
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  auto args = parseArguments(argc, argv);

  if (!args) {
    return 1;
  }

  if (!copyFile(args->inputFileName, args->outputFileName)) {
    return 1;
  }

  return 0;
}
