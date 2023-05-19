// processor.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "memory_tape.hpp"
#include <iostream>

class Processor {
private:
  DoubleSidedTape memory;
  std::string instructionBuffer;

public:
  Processor(std::string instructionBuffer);
  void execute();
  void showTape() const;
};