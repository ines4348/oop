#include "pch.h"
#include <iostream>
#include <optional>
#include <string>

struct Args {
  std::string operand;
};

std::optional<Args> ParseArguments(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Invalid argument count\n ";
    std::cout << "Usage: flipbyte.exe <integer 0..255>\n";
    return std::nullopt;
  }

  Args arg;
  arg.operand = argv[1];
  return arg;
}

void FlipByte(int &x);

int main(int argc, char *argv[]) {
  auto args = ParseArguments(argc, argv);

  if (!args) {
    return 1;
  }

  int x;
  x = std::stoi(args->operand);
  FlipByte(x);

  std::cout << "x = " << x;

  return 0;
}

void FlipByte(int &x) {
  // Четные и нечетные биты поменялись местами.
  x = ((x & 0x55) << 1) | ((x >> 1) & 0x55);
  // Биты "перетасовываются" группами по два.
  x = ((x & 0x33) << 2) | ((x >> 2) & 0x33);
  // Биты "перетасовываются" группами по четыре.
  x = ((x & 0x0F) << 4) | ((x >> 4) & 0x0F);
}
